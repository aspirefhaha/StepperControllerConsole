/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "slavethread.h"
#include <QTime>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QDebug>
#include <QTextCodec>

SlaveThread::SlaveThread(QObject *parent) :
    QThread(parent),pserial(NULL)/*,eventLoop(this)*/
{
    qRegisterMetaType<mavlink_config_t>("mavlink_config_t");
    qRegisterMetaType<mavlink_config_t>("mavlink_config_t&");
    qRegisterMetaType<mavlink_heartbeat_t>("mavlink_heartbeat_t");
    qRegisterMetaType<mavlink_heartbeat_t>("mavlink_heartbeat_t&");
    qRegisterMetaType<mavlink_l6474status_t>("mavlink_l6474status_t");
    qRegisterMetaType<mavlink_l6474status_t>("mavlink_l6474status_t&");
    connect(this,&SlaveThread::moveStep,this,&SlaveThread::sltMoveStep);
    connect(this,&SlaveThread::setMark, this, &SlaveThread::sltSetMark);
    connect(this,&SlaveThread::setMaxSpeed, this, &SlaveThread::sltSetMaxSpeed);
    connect(this,&SlaveThread::setDec, this, &SlaveThread::sltSetDec);
    connect(this,&SlaveThread::setAcc, this, &SlaveThread::sltSetAcc);
    connect(this,&SlaveThread::goPos, this, &SlaveThread::sltGoPos);
    connect(this,&SlaveThread::cmdProg, this , &SlaveThread::sltCmdProg);
    connect(this,&SlaveThread::setTVal, this, &SlaveThread::sendSetTVal);
    connect(this, &SlaveThread::setStepMode, this ,&SlaveThread::sendStepMode);
}

void SlaveThread::sendStepMode(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETSTEPMODE;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set StepMode Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error(QString("Send Failed!"));
    }
}

void SlaveThread::sltCmdProg(int cmd)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_RUNPROG1;
    runcmd.distance = cmd;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Run Prog1 Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error(QString("Send Failed!"));
    }
}

void SlaveThread::sltGoPos(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_GOPOS;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send GoPos %2 Cmd size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendSetTVal(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETTVAL;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set TVal Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sltEnableController()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_ENABLE;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Enable size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sltDisableController()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_DISABLE;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Disable Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sltSetAcc(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETACC;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set Acc Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sltSetDec(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETDEC;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set Dec Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

SlaveThread::~SlaveThread()
{
    pserial = NULL;
    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();
}

void SlaveThread::sltSetMaxSpeed(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETMAXSPEED;
    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set Max Speed Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::startSlave(const QString &portName, const QString &baudrate,int waitTimeout)
{

    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_baudRate = baudrate;

    if (!isRunning())
        start();
}

void SlaveThread::sltGoMark()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_GOMARK;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send GoMark Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}


void SlaveThread::sltSetMark(int value)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETMARK;

    runcmd.distance = value;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set Mark Cmd %1 size %2").arg(value).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}


void SlaveThread::sltMoveStep(int dir, int step)
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_MOVESTEP;
    runcmd.dir = dir;
    runcmd.distance = step;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send MoveStep Cmd dir %1 step %2 size %1").arg(dir).arg(step).arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendRunBWCMD()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_MOVEBWD;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Run Backward Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendRunFWDCMD()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_MOVEFWD;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Run Forward Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendSetHome()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SETHOME;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send Set Home Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendHardStop()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_HARDSTOP;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send HardStop Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendSoftStop()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_SOFTSTOP;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send SoftStop Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }
}

void SlaveThread::sendGetConfigCMD()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_GETCONFIG;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send GetConfig Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Failed!");
    }

}

void SlaveThread::sendGetStatus()
{
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    mavlink_runcmd_t runcmd;
    memset(&runcmd,0,sizeof(runcmd));
    runcmd.cmd = SMCMD_GETSTATUS;
    mavlink_msg_runcmd_encode(1,1,&msg,&runcmd);
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)&buffer,&msg);
    if(!m_quit && pserial&& pserial->isOpen()){
        int sendlen = pserial->write((const char *)&buffer,len);
        emit this->information(tr("Send GetStatus Cmd size %1").arg(sendlen));
    }
    else{
        emit this->error("Send Get Status Cmd Failed!");
    }
}


void SlaveThread::run()
{
    bool currentPortNameChanged = false;

    m_mutex.lock();

    QString currentPortName;
    QString currentBaudRate;
    if (currentPortName != m_portName || currentBaudRate != m_baudRate) {
        currentPortName = m_portName;
        currentBaudRate = m_baudRate;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = m_waitTimeout;
    m_mutex.unlock();

    QSerialPort serial;
    QDir dir;
    QDateTime nowtime ;
    QString dirname;
    QSettings * configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    configIniRead->setIniCodec(QTextCodec::codecForName("UTF-8"));
    QString rootDir = QString::fromUtf8(configIniRead->value("/save/dir").toByteArray());
    delete configIniRead;


    dirname = rootDir;
    if(!dir.exists(dirname)){
        bool res = dir.mkpath(dirname);
        qDebug() << "Create Dir" << dirname << "res:" << res;
    }

    QFile statusFile;
    QFile hbFile;
    QTextStream * pStatusStream = nullptr;
    QTextStream * pHbStream = nullptr;

    mavlink_message_t message;
    while (!m_quit) {

        if (currentPortNameChanged) {
            serial.close();
            serial.setPortName(currentPortName);
            serial.setBaudRate(m_baudRate.toInt());
            if(statusFile.isOpen()){
                if(pStatusStream){
                    pStatusStream->flush();
                    delete pStatusStream;
                    pStatusStream = nullptr;
                }
                statusFile.flush();
                statusFile.close();

            }
            if(hbFile.isOpen()){
                if(pHbStream){
                    pHbStream->flush();
                    delete pHbStream;
                    pHbStream = nullptr;
                }
            }

            if (!serial.open(QIODevice::ReadWrite)) {
                emit error(tr("Can't open %1, error code %2")
                           .arg(m_portName).arg(serial.error()));
                return;
            }
            else{
                pserial = &serial;
                emit opensuccess(tr("Open Successfully"));
                nowtime = QDateTime::currentDateTime();
                if(!rootDir.isEmpty())
                {
                    dirname = QString("%1%2%3").arg(rootDir).arg(QDir::separator()).arg(nowtime.toString("yyyy_MM_dd_hh_mm_ss"));
                }else{
                    dirname = nowtime.toString("yyyy_MM_dd_hh_mm_ss");
                }
                if(!dir.exists(dirname)){
                    bool res = dir.mkpath(dirname);
                    qDebug() << "Create Dir" << dirname << "res:" << res;
                }
                QString statusfilename = QString("%1%2status.csv").arg(dirname).arg(QDir::separator());
                statusFile.setFileName(statusfilename);
                if(statusFile.open(QFile::WriteOnly | QFile::Truncate)){
                    qDebug() << "Create File Success!";
                    pStatusStream = new QTextStream(&statusFile);
                }
                else{
                    qDebug() << "Create File " << statusfilename << "failed for " << statusFile.error();
                }
                QString hbfilename = QString("%1%2hb.csv").arg(dirname).arg(QDir::separator());
                hbFile.setFileName(hbfilename);
                if(hbFile.open(QFile::WriteOnly | QFile::Truncate)){
                    qDebug() << "Create HBFile Success!";
                    pHbStream = new QTextStream(&hbFile);
                }
            }
        }

        if (serial.waitForReadyRead(currentWaitTimeout)) {
            // read request
            QByteArray requestData = serial.readAll();
            uint8_t msgReceived = false;
            requestData += serial.readAll();
            mavlink_status_t status;
            unsigned char  c = 0;
            for(int i = 0;i<requestData.size();i++){
                c=requestData.at(i);
                msgReceived = mavlink_parse_char(MAVLINK_COMM_0,c,&message,&status);
                if(msgReceived){

                    switch(message.msgid){
                    case MAVLINK_MSG_ID_HEARTBEAT:
                    {
                        mavlink_heartbeat_t hbt;
                        mavlink_msg_heartbeat_decode(&message,&hbt);
                        emit this->hbPack(hbt);
                        //QDateTime nowtime = QDateTime::currentDateTime();
                        (*pHbStream) << hbt.tick << ","  << hbt.position << "," << hbt.speed << endl;
                        //QString request = QString("speed %1 pos %2").arg(hbt.speed).arg(hbt.position);
                        //emit this->request(request);
                        break;
                    }
                    case MAVLINK_MSG_ID_CONFIG:
                    {
                        mavlink_config_t config;
                        mavlink_msg_config_decode(&message,&config);
                        //QApplication::postEvent();
                        emit this->configPack(config);
                        //QString information = QString("CONFIG %1 pos %2").arg(config.acc).arg(config.dec);
                        //emit this->information(information);
                        break;
                    }
                    case MAVLINK_MSG_ID_L6474STATUS:
                    {
                        mavlink_l6474status_t status;
                        mavlink_msg_l6474status_decode(&message,&status);
                        emit this->statusPack(status);
                        (*pStatusStream) << status.status << endl;
                    }
                    default:
                        break;
                    }
                }
            }


        } else {
            emit timeout(tr("Wait read request timeout %1")
                         .arg(QTime::currentTime().toString()));
        }
        //eventLoop.processEvents();
        m_mutex.lock();
        if (currentPortName != m_portName|| currentBaudRate != m_baudRate) {
            currentPortName = m_portName;
            currentBaudRate = m_baudRate;
            currentPortNameChanged = true;
        } else {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = m_waitTimeout;
        //currentRespone = m_response;
        m_mutex.unlock();
    }
    if(pStatusStream){
        pStatusStream->flush();
        delete pStatusStream;
        pStatusStream = nullptr;
    }
    if(statusFile.isOpen()){
        statusFile.flush();
        statusFile.close();
    }

    if(pHbStream){
        pHbStream->flush();
        delete pHbStream;
        pHbStream = nullptr;
    }
    if(hbFile.isOpen()){
        hbFile.flush();
        hbFile.close();
    }

}
