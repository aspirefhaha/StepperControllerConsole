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

#ifndef SLAVETHREAD_H
#define SLAVETHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSerialPort>
#include "serialproto/stepmotor/mavlink.h"
#include <QMetaType>
#include <QEventLoop>


Q_DECLARE_METATYPE(mavlink_config_t);
Q_DECLARE_METATYPE(mavlink_heartbeat_t);
Q_DECLARE_METATYPE(mavlink_l6474status_t);
Q_DECLARE_METATYPE(mavlink_custstep_t);

class SlaveThread : public QThread
{
    Q_OBJECT
public:
    explicit SlaveThread(QObject *parent = nullptr);
    ~SlaveThread();

    void startSlave(const QString &portName,  const QString &baudrate,int waitTimeout);


signals:
    void request(const QString &s);
    void error(const QString &s);
    void opensuccess(const QString &s);
    void information(const QString &s);
    void timeout(const QString &s);
    void configPack(const mavlink_config_t&);
    void statusPack(const mavlink_l6474status_t&);
    void hbPack(const mavlink_heartbeat_t&);
    void CustStepPack(const mavlink_custstep_t&);
    void moveStep(int dir, int step);
    void setMark(int value);
    void setMaxSpeed(int value);
    void setAcc(int acc);
    void setUpPos(int uppos);
    void setDownPos(int downpos);
    void setDec(int acc);
    void goPos(int value);
    void cmdProg(int cmd);
    void getStatus();
    void setTVal(int value);
    void setStepMode(int value);
    void sendCust(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

private:
    void run() override;

    QString m_portName;
    QString m_baudRate;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    bool m_quit = false;
    //QEventLoop eventLoop;
    QSerialPort * pserial = nullptr;
public slots:
    void sendGetConfigCMD();
    void sendRunFWDCMD();
    void sendSoftStop();
    void sendRunBWDCMD();
    void sendHardStop();
    void sendSetHome();
    void sendSetTVal(int value);
    void sendGetStatus();
    void sltMoveStep(int dir, int step);
    void sltSetMark(int value);
    void sltGoMark();
    void sltSetMaxSpeed(int value);
    void sltSetAcc(int value);
    void sltSetDec(int value);
    void sltGoPos(int value);
    void sltCmdProg(int cmd);
    void sltSetUpPos(int uppos);
    void sltSetDownPos(int downpos);
    void sltEnableController();
    void sltUnlockUp();
    void sltUnlockDown();
    void sltDisableController();
    void sendStepMode(int value);
    void sltScanUpDown();
    void sltTurnOn();
    void sltTurnOff();
    void sltGetCust();
    void MoveFreqStepDir(int dir,int step,int freq);
    void sltSendCust(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

};
//! [0]

#endif // SLAVETHREAD_H
