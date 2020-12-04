#include "StepperConsole.h"
#include "ui_StepperConsole.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegendMarker>
#include <QSerialPortInfo>
#include <QSettings>
#include <QTimer>
#include <QDebug>

#define XSPAN 21
#define REDUCTIONRATIO 1

StepperConsole::StepperConsole(QWidget *parent) :
    QMainWindow(parent),
    stepPerCirclr(400),
    expectCmd(SMCMD_IDLE),
    ui(new Ui::stepperConsole)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/images/motorcon.png"));

    QStringList sts;
    sts << "FullStep" << "HalfStep" << "1/4Step" << "1/8Step" << "1/16Step";
    ui->cbStepMode->addItems(sts);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->cbSerialPort->addItem(info.portName());

    QList<qint32> baudrates =  QSerialPortInfo::standardBaudRates();
    for(const qint32 &baudrate : baudrates){
        ui->cbBaudRate->addItem(QString::number(baudrate));
    }

    QSettings * configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    QString portName = configIniRead->value("/com/portname").toString();
    QString baudRate = configIniRead->value("/com/baudrate").toString();
    delete configIniRead;

    for(int i = 0;i<ui->cbSerialPort->count();i++){
        if(ui->cbSerialPort->itemText(i) == portName){
            ui->cbSerialPort->setCurrentIndex(i);
            break;
        }

    }
    for(int i = 0;i< ui->cbBaudRate->count();i++){
        if(ui->cbBaudRate->itemText(i) == baudRate){
            ui->cbBaudRate->setCurrentIndex(i);
            break;
        }

    }


    lastTime = QDateTime::currentDateTime();


    connect(&m_serialThread, &SlaveThread::request, this,       &StepperConsole::showRequest);
    connect(&m_serialThread, &SlaveThread::information, this,   &StepperConsole::showInfo);
    connect(&m_serialThread, &SlaveThread::error, this,         &StepperConsole::processError);
    connect(&m_serialThread, &SlaveThread::timeout, this,       &StepperConsole::processTimeout);
    connect(&m_serialThread, &SlaveThread::opensuccess, this,   &StepperConsole::openComSuccess);
    connect(&m_serialThread, &SlaveThread::configPack, this ,   &StepperConsole::parseConfig);
    connect(&m_serialThread, &SlaveThread::statusPack, this,    &StepperConsole::parseL6474Status);
    connect(&m_serialThread, &SlaveThread::CustStepPack, this,  &StepperConsole::parseCustStep);
    connect(&m_serialThread, &SlaveThread::hbPack, this,        &StepperConsole::parseHeartBeat);

    connect(ui->pbEnable, &QPushButton::clicked, &m_serialThread, &SlaveThread::sltEnableController);
    connect(ui->pbDisable, &QPushButton::clicked, &m_serialThread, &SlaveThread::sltDisableController);
    connect(ui->pbGetStatus, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendGetStatus);


    connect(ui->cbSerialPort,SIGNAL(currentTextChanged(QString)),this,SLOT(sltPortChanged(QString)));
    connect(ui->cbBaudRate,SIGNAL(currentTextChanged(QString)),this,SLOT(sltBaudrateChanged(QString)));
    connect(ui->pbSetZero, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendSetHome);

    connect(ui->pbSoftStop, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendSoftStop);

    connect(ui->pbGetConfig, &QPushButton::clicked,&m_serialThread, &SlaveThread::sendGetConfigCMD);
    connect(ui->pbGetStatus, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendGetStatus);

    QTimer::singleShot(500,this, SLOT(sltconfChart()));
}

void StepperConsole::sltSetTVal()
{
    unsigned char  newtval = (ui->sbTVal->value() & 0xff);
    emit this->m_serialThread.setTVal(newtval);
}

void StepperConsole::sltTGChanged(bool selected)
{
    Q_UNUSED(selected);
    QRadioButton * selTGbtn = static_cast<QRadioButton*>(sender());
    QString strSelTG = selTGbtn->text();
    if(strSelTG.compare("0.5")==0){
        ui->sbTVal->setValue(16);
    }
    else if(strSelTG.compare("1.0")==0){
        ui->sbTVal->setValue(31);
    }
    else if(strSelTG.compare("1.2")==0){
        ui->sbTVal->setValue(37);
    }
    else if(strSelTG.compare("1.4")==0){
        ui->sbTVal->setValue(43);
    }
    else if(strSelTG.compare("1.5")==0){
        ui->sbTVal->setValue(47);
    }
    else if(strSelTG.compare("1.6")==0){
        ui->sbTVal->setValue(50);

    }
    else if(strSelTG.compare("1.8")==0){
        ui->sbTVal->setValue(56);

    }
    else if(strSelTG.compare("2.0")==0){
        ui->sbTVal->setValue(63);

    }
    else if(strSelTG.compare("2.2")==0){
        ui->sbTVal->setValue(69);

    }
    else if(strSelTG.compare("2.4")==0){
        ui->sbTVal->setValue(75);

    }
    else if(strSelTG.compare("2.5")==0){
        ui->sbTVal->setValue(78);

    }
    else if(strSelTG.compare("2.6")==0){
        ui->sbTVal->setValue(82);

    }
    else if(strSelTG.compare("2.8")==0){
        ui->sbTVal->setValue(88);

    }
    else if(strSelTG.compare("3.0")==0){
        ui->sbTVal->setValue(95);

    }

}

void StepperConsole::sltSetDec()
{
    int dec = ui->leDEC->text().toInt();
    dec = abs(dec);
    emit m_serialThread.setDec(dec);
}

void StepperConsole::sltSetAcc()
{
    int acc = ui->leACC->text().toInt();
    acc = abs(acc);
    emit m_serialThread.setAcc(acc);
}

void StepperConsole::sltconfChart()
{
    //chart = new QChart();

    chartView = new QChartView(); //把图标添加到图标显示控件上
    chart = chartView->chart();


    m_baseSeries = new QLineSeries;
    QPen basePen(Qt::blue);
    basePen.setWidth(1);
    m_baseSeries->setPen(basePen);
    //m_baseSeries->append(0,0);

    m_baseSeries->setUseOpenGL();
    chart->addSeries(m_baseSeries);

    m_series = new QLineSeries ;
    QPen dynPen(Qt::cyan);
    dynPen.setWidth(1);
    m_series->setPen(dynPen);
    m_series->setUseOpenGL();

    chart->addSeries(m_series);

    QValueAxis *axisX = new QValueAxis; //建议使用动态分配的方式
    axisX->setRange(0, XSPAN);           //设置坐标范围
    axisX->setLabelFormat("%d");        //设置坐标显示格式（比如整形%d %i，浮点型%f）
    axisX->setTickCount(XSPAN+1);             //设置网格数量，22根线，21个网格

    chart->setAxisX(axisX,m_baseSeries); //把坐标添加上
    chart->setAxisX(axisX,m_series);


    foreach(QLegendMarker * marker , chart->legend()->markers()){
        marker->setVisible(false);
    }


    QValueAxis * axisY = new QValueAxis;
    axisY->setRange(-50,450);
    axisY->setLabelFormat("%.1f");
    axisY->setTickCount(5);
    chart->setAxisY(axisY,m_baseSeries);
    chart->setAxisY(axisY, m_series);


    //chart->setContentsMargins(10, 10, 10, 15);  //设置外边界全部为0
    //chart->setMargins(QMargins(10, 10, 10, 15));//设置内边界全部为0
    //chart->legend()->setVisible(true);              //图例显示
    chart->legend()->hide();
    //chart->legend()->setAlignment(Qt::AlignBottom); //图例向下居中
    ui->hlContainer->addWidget(chartView);
    timeId = startTimer(20);
}

void StepperConsole::sltSetMaxspeed()
{
    int maxspeed = ui->leMaxSpeed->text().toInt();
    maxspeed = abs(maxspeed);
    emit m_serialThread.setMaxSpeed(maxspeed);
    expectCmd = SMCMD_SETMAXSPEED;
    checkerCmdTimerId = startTimer(250);
    //ui->gaugeCar->setMaxValue((double)maxspeed * 1.1);
}

StepperConsole::~StepperConsole()
{
    delete ui;
}


void StepperConsole::sltPortChanged(QString newvalue)
{
    QSettings * configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("/com/portname",newvalue);
    delete configIniWrite;
}

void StepperConsole::sltBaudrateChanged(QString newvalue)
{
    QSettings * configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("/com/baudrate",newvalue);
    delete configIniWrite;
}

void StepperConsole::parseCustStep(const mavlink_custstep_t & custstep)
{

    ui->lbStep1->setText(QString::number(custstep.wait1));
    ui->lbStep2->setText(QString::number(custstep.wait2));
    ui->lbStep3->setText(QString::number(custstep.wait3));
    ui->lbStep4->setText(QString::number(custstep.wait4));
    ui->lbStep5->setText(QString::number(custstep.wait5));
    ui->lbStep6->setText(QString::number(custstep.wait6));
    ui->lbStep7->setText(QString::number(custstep.wait7));
    ui->lbFreq1->setText(QString::number(custstep.step1));
    ui->lbFreq2->setText(QString::number(custstep.step2));
    ui->lbFreq3->setText(QString::number(custstep.step3));
    ui->lbFreq4->setText(QString::number(custstep.step4));
    ui->lbFreq5->setText(QString::number(custstep.step5));
    ui->lbFreq6->setText(QString::number(custstep.step6));
    ui->lbFreq7->setText(QString::number(custstep.step7));
}

void StepperConsole::addLog(QString & logitem)
{
    ui->lwLog->insertItem(0,logitem);
}

void StepperConsole::addLog(const char * plogitem)
{
    QString logitem = QString(plogitem);
    ui->lwLog->insertItem(0,logitem);
}

void StepperConsole::sltFreqSelected(bool selected)
{
    //qDebug() << "selected : " << selected << " sender:" << sender() << endl;
    QRadioButton * selfrqbtn = static_cast<QRadioButton*>(sender());
    //qDebug() << "cast button " << selfrqbtn << endl;
    if(selfrqbtn && selected){
        ui->leMaxSpeed->setText(selfrqbtn->text());
    }

}


void StepperConsole::timerEvent(QTimerEvent *event)
{
    if(isVisible() && event->timerId()  == timeId){
        QDateTime now = QDateTime::currentDateTime();
        qint64 timespan = lastTime.msecsTo(now);

        //m_x = timespan / 1000.0;
        //QValueAxis* axisX = (QValueAxis*)chart->axisX();

        //m_baseSeries->append(m_x,0);
        if(m_series->count()>=2000){
             m_series->removePoints(0, 500);
        }

        if(m_baseSeries->count()>=2000){
             m_baseSeries->removePoints(0, 500);
        }

        if (timespan > (XSPAN-1)  *1000) {
            static qint64 lastspan = timespan;
            qreal x = chart->plotArea().width() / (XSPAN) * (timespan - lastspan) / 1000;
            chart->scroll(x, 0);
            lastspan = timespan;
        }

   }
    else if(event->timerId() == checkerCmdTimerId){
        if(lastAckCmd != expectCmd){
            switch(expectCmd){
            case SMCMD_MOVEBWD:
                addLog("Send MoveBWD Again");
                m_serialThread.sendRunBWDCMD();
                break;
            case SMCMD_SOFTSTOP:
                addLog("Send SoftStop Again");
                m_serialThread.sendSoftStop();
                break;
            case SMCMD_MOVEFWD:
                addLog("Send MoveFWD Again");
                m_serialThread.sendRunFWDCMD();
                break;
            case SMCMD_STOPENGINE:
                addLog("Send StopEngine Again");
                m_serialThread.sltTurnOff();
                break;
            case SMCMD_STARTENGINE:
                addLog("Send StartEngine Again");
                m_serialThread.sltTurnOn();
                break;
            case SMCMD_HARDSTOP:
                addLog("Send HardStop Again");
                sltHardStop();
                break;
            case SMCMD_MOVESTEP:
                addLog("send Move Step Again");
                sltMoveStep();
                break;
            case SMCMD_SETMAXSPEED:
                addLog("Send SetMaxSpeed Again");
                sltSetMaxspeed();
                break;
            default:
                break;
            }
        }
        else{
            switch(expectCmd){
            case SMCMD_SETMAXSPEED:
                m_serialThread.sendGetConfigCMD();
                break;
            default:
                break;
            }
            QString log = QString("Cmd 0x%1 Confirmed").arg(QString::number(expectCmd,16));
            addLog(log);
            killTimer(checkerCmdTimerId);
        }
    }
}

void StepperConsole::sendCustConfig()
{
    QSettings * configIniLoad = new QSettings("config.ini",QSettings::IniFormat);
    int choose = configIniLoad->value("Cust/Choose").toInt();
    switch(choose){
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 1:
    default:
        choose = 1;
        break;
    }
    qint32 step[7] = {0};
    qint32 freq[7] = {0};
    for(int i = 0 ;i< 7;i++){

        step[i] = configIniLoad->value(QString("Cust/Step%1_%2").arg(i+1).arg(choose)).toInt();
        freq[i] = configIniLoad->value(QString("Cust/Freq%1_%2").arg(i+1).arg(choose)).toInt();

    }

    delete configIniLoad;
    m_serialThread.sendCust(step[0],step[1],step[2],step[3],step[4],step[5],step[6],
                            freq[0],freq[1],freq[2],freq[3],freq[4],freq[5],freq[6]);
}

void StepperConsole::sltConfigFreqStep()
{
    freqStepDlg.setModal(true);
    if(freqStepDlg.exec() == QDialog::Accepted){
        sendCustConfig();
    }
}

void StepperConsole::sltGetFreqStep()
{
    m_serialThread.sendGetConfigCMD();
}

void StepperConsole::parseL6474Status(const mavlink_l6474status_t & stpack)
{
    unsigned short status = stpack.status;

    if(((status & 0x180) != 0) || (status & 0x1e00)!=0x1e00){
        ui->lbWarning->show();
    }
    else{
        ui->lbWarning->hide();
    }

    ui->cbOCD->setChecked((status &0x1000)==0);
    ui->cbThermalSD->setChecked((status & 0x800)==0);
    ui->cbThermalWRN->setChecked((status & 0x400)==0);
    ui->cbUVLO->setChecked((status & 0x200)==0);
    ui->cbWrongCMD->setChecked(status & 0x100);
    ui->cbNotPerf->setChecked(status & 0x80);
    ui->lbDirection->setText(status & 0x10?"正向":"反向");
    if(status & 0x1){
        ui->cbHiZ->setChecked(true);
        ui->pbSetStepMode->setEnabled(true);
    }
    else{
        ui->cbHiZ->setChecked(false);
        ui->pbSetStepMode->setEnabled(false);
    }

    emit showInfo(QString("Get Status"));
}

void StepperConsole::parseHeartBeat(const mavlink_heartbeat_t & hbpack)
{


    QString strRunMode = "未知";

    switch(hbpack.runstatus){
    case EMS_ACCELERATING:
        strRunMode = tr("ACC");
        break;
    case EMS_DECELERATING:
        strRunMode = tr("DEC");
        break;
    case EMS_STEADY:
        strRunMode = tr("CONST");
        break;
    case EMS_INACTIVE:
        strRunMode = tr("STOP");
        break;
    }
    ui->lbRunStatus->setText(strRunMode);

    //ui->lePosition->setText(QString("%1 : %2 : %3").arg(QString::number(hbpack.position)).arg(hbpack.dynamic).arg(QString::number(hbpack.tick)));
    ui->lePosition->setText(QString("%1 : %2 ").arg(QString::number(hbpack.position)).arg(hbpack.dynamic));
    double position = hbpack.position % (this->stepPerCirclr*REDUCTIONRATIO);
    if(position < 0){
        position += (this->stepPerCirclr * REDUCTIONRATIO);
    }
//    position /= REDUCTIONRATIO;
    ui->angleGauge->setValue1( position);
    ui->angleGauge->setValue2(hbpack.dynamic * 1000);
    emit ui->angleGauge->valueChanged();

    QDateTime now = QDateTime::currentDateTime();
    qint64 timespan = lastTime.msecsTo(now);
    m_x = timespan / 1000.0;
    //QValueAxis* axisX = (QValueAxis*)chart->axisX();
    m_baseSeries->append(m_x,position);
    m_series->append(m_x,hbpack.dynamic * 1000);
    ui->lbLastCmd->setText(QString::number(hbpack.lastcmd,16) + " : " + QString::number(position));

    this->lastAckCmd = hbpack.lastcmd;

    ui->leAngleSpeed->setText(QString::number(hbpack.speed));
    ui->gaugeCar->setValue( (double)hbpack.speed);
    emit ui->gaugeCar->valueChanged();

    //qreal pos = (hbpack.position % 400);
//    if(hbpack.tick > lastTick){
//        QPointF value1point((qreal)hbpack.tick,(qreal)(hbpack.position % (stepPerCirclr * REDUCTIONRATIO) * 400.0 / (stepPerCirclr * REDUCTIONRATIO)));

//        qint32 dispvalue = calcvalue * 100000;
//        dispvalue %= 40000000;
//        calcvalue = dispvalue / 100000.0;

//        //TODO del below
//        calcvalue = (3.3-gd) * 4.0 / 3.3 * 100.0;

//        QPointF value2point((qreal)hbpack.tick,(qreal)calcvalue);
//        pointMutex.lock();
//        m_value1Points.append(value1point);
//        m_value2Points.append(value2point);
//        pointMutex.unlock();
//        lastTick = hbpack.tick;
//    }


    ui->cbUpLock->setChecked(hbpack.lockstate & 0x1);

    ui->pbUnlockUp->setEnabled(hbpack.lockstate & 0x1);

    ui->cbDownLock->setChecked(hbpack.lockstate & 0x2);

    ui->pbUnlockDown->setEnabled(hbpack.lockstate & 0x2);

//    int upPos = ui->leUpPos->text().toInt();
//    int downPos = ui->leDownPos->text().toInt();

//    if(upPos == 0){
//        upPos = 400;
//    }
//    if(upPos < downPos){
//        upPos = downPos + 1;
//    }
//    if(hbpack.position >= downPos && hbpack.position <= upPos){
//        ui->valueOpening->setValue( ((double)hbpack.position - downPos) * 100.0 / (upPos - downPos) );
//        emit ui->valueOpening->valueChanged();
//    }
}

void StepperConsole::parseConfig(const mavlink_config_t &confpack)
{
    isPeerReboot = confpack.isRboot;
    ui->leACC->setText(QString::number(confpack.acc));
    ui->leDEC->setText(QString::number(confpack.dec));
    ui->leMaxSpeed->setText(QString::number(confpack.maxspeed));
    ui->leMinSpeed->setText(QString::number(confpack.minspeed));
    double maxspeed = (double) confpack.maxspeed;
    //ui->gaugeCar->setMaxValue(maxspeed*1.1);
    //ui->gaugeCar->setMinValue( 0 );
    //emit ui->gaugeCar->valueChanged();
    ui->leMark->setText(QString::number(confpack.mark));
    ui->leOCth->setText(QString::number(confpack.ocdth));
    unsigned char step_mode = (confpack.stepmode )&0x7;
    if(step_mode >= 4)
        step_mode = 4;
    stepPerCirclr = pow(2,step_mode) * 200;


    //qDebug("step_mode %x pro %x" , confpack.stepmode , step_mode);

    ui->sbTVal->setValue(confpack.tval);

    QString tvalstr = QString("%1mA").arg((confpack.tval+1) * 31.25);

    ui->lbTVal->setText(tvalstr);

    ui->angleGauge->setMaxValue(stepPerCirclr);

    ui->cbStepMode->setCurrentIndex(step_mode);
    ui->gbFreq->setEnabled(true);
    ui->gbTorque->setEnabled(true);

//    ui->leUpPos->setText(QString::number(confpack.uppos));
//    ui->leDownPos->setText(QString::number(confpack.downpos));

}

void StepperConsole::showInfo(const QString &s)
{
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Info: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
//    ui->lwLog->insertItem(0,logitem);

}

void StepperConsole::showRequest(const QString &s)
{
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Request: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
//    ui->lwLog->insertItem(0,logitem);
}

void StepperConsole::openComSuccess(const QString &s)
{
    Q_UNUSED(s);
    ui->cbBaudRate->setEnabled(false);
    ui->cbSerialPort->setEnabled(false);
    ui->pbConnect->setEnabled(false);
    QTimer::singleShot(500,&m_serialThread, SLOT(sltGetCust()));
    QTimer::singleShot(700,&m_serialThread, SLOT(sendGetConfigCMD()));
    QTimer::singleShot(1000,&m_serialThread, SLOT(sendGetStatus()));
}

void StepperConsole::processError(const QString &s)
{
    //activateRunButton();
    //qDebug() << tr("Error: %1").arg(s);
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Error!: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
//    ui->lwLog->insertItem(0,logitem);
    //m_trafficLabel->setText(tr("No traffic."));
}

void StepperConsole::processTimeout(const QString &s)
{
    //qDebug() << tr("Status: Timeout, %1.").arg(s);
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1 TimeOut : %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
//    ui->lwLog->insertItem(0,logitem);
    //m_trafficLabel->setText(tr("No traffic."));
}

void StepperConsole::sltSerialConnect()
{
    ui->cbBaudRate->setEnabled(false);
    ui->cbSerialPort->setEnabled(false);
    ui->pbConnect->setEnabled(false);

    //qDebug()<<tr("Status: Running");
    m_serialThread.startSlave(ui->cbSerialPort->currentText(),
                        ui->cbBaudRate->currentText(),
                        2000);

}

void StepperConsole::sltRunFWD()
{
    if(lastAckCmd != SMCMD_MOVEFWD){
        m_serialThread.sendRunFWDCMD();
        expectCmd = SMCMD_MOVEFWD;
        checkerCmdTimerId = startTimer(250);
    }
}

void StepperConsole::sltSoftStop()
{
    if(lastAckCmd != SMCMD_SOFTSTOP){
        m_serialThread.sendSoftStop();
        expectCmd = SMCMD_SOFTSTOP;
        checkerCmdTimerId = startTimer(250);
    }
}

void StepperConsole::sltStartEngine()
{
    if(lastAckCmd != SMCMD_STARTENGINE){
        m_serialThread.sltTurnOn();
        expectCmd = SMCMD_STARTENGINE;
        checkerCmdTimerId = startTimer(250);
    }
}
void StepperConsole::sltStopEngine()
{
    if(lastAckCmd != SMCMD_STOPENGINE){
        m_serialThread.sltTurnOff();
        expectCmd = SMCMD_STOPENGINE;
        checkerCmdTimerId = startTimer(250);
    }
}

void StepperConsole::sltRunBWD()
{
    if(lastAckCmd != SMCMD_MOVEBWD){
        m_serialThread.sendRunBWDCMD();
        expectCmd = SMCMD_MOVEBWD;
        checkerCmdTimerId = startTimer(250);
    }
}



void StepperConsole::sltRunFreqChange(bool selected)
{
    //qDebug() << "selected : " << selected << " sender:" << sender() << endl;
    QRadioButton * selfrqbtn = static_cast<QRadioButton*>(sender());
    //qDebug() << "cast button " << selfrqbtn << endl;
    if(selfrqbtn && selected){
        ui->leMaxSpeed_2->setText(selfrqbtn->text());
    }

}

void StepperConsole::sltHardStop()
{
    if(lastAckCmd != SMCMD_HARDSTOP){
        m_serialThread.sendHardStop();
        expectCmd = SMCMD_HARDSTOP;
        checkerCmdTimerId = startTimer(150);
    }
}

void StepperConsole::sltMoveStep()
{
    int dir = 0 ;
    int step = 0 ;
    if(ui->rbFWD->isChecked())
        dir = 1;
    else
        dir = 0;
    step = ui->sbStep->text().toInt();
    if(step>5)
        step+=1;
    emit m_serialThread.moveStep(dir,step);
    expectCmd = SMCMD_MOVESTEP;
    checkerCmdTimerId = startTimer(550);
}


void StepperConsole::sltMoveFreqStepDir()
{
    int dir = 0 ;
    int step = 0 ;
    int freq = 300;
    if(ui->rbFWD_2->isChecked())
        dir = 1;
    else
        dir = 0;
    step = ui->sbStep_2->text().toInt();
    if(step>5)
        step+=1;
    freq = ui->leMaxSpeed_2->text().toInt();
    m_serialThread.MoveFreqStepDir(dir,step,freq);
    expectCmd = SMCMD_STEPFREQDIRMOVE;
    checkerCmdTimerId = startTimer(550);
}


//void StepperConsole::activateRunButton()
//{
//    ui->cbBaudRate->setEnabled(true);
//    ui->cbSerialPort->setEnabled(true);
//    ui->pbConnect->setEnabled(true);
//}
