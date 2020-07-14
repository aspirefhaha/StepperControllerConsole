#include "mainwindow.h"

#include <QSerialPortInfo>
#include <QSettings>
#include <QDebug>
#include <QDateTime>
#include <QtMath>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QTimer>
#include <QValueAxis>
#include <QGraphicsLayout>
#include "ui_mainwindow.h"

#define TIMESPAN 10.0
#define TIMERFREQ 30   // ms

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),stepPerCirclr(400),isPeerReboot(true)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/motorcon.png"));
    qDebug() << "Current Thread" << QThread::currentThread();
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

    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
//    v.setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRubberBand(QChartView::NoRubberBand);

    m_serie1 = new QLineSeries;
    m_serie2 = new QLineSeries;

    //QColor pointer1Color = QColor(250,151,150,255);            //指针1颜色
    QColor pointer2Color = QColor(100,181,180,200);            //指针2颜色
    //m_serie1->setColor(pointer1Color);
    //m_serie2->setColor(red);
    QBrush brush(ui->gaugeCar->getPointerColor());
    QPen sePen(brush,2);
    m_serie1->setPen(sePen);
    sePen.setColor(pointer2Color);
    m_serie2->setPen(sePen);
#if 0
    for(int i=0;i<5000;++i){
       m_serie1->append(i,0);
       m_serie2->append(i,1);
    }
#endif
    m_chart->addSeries(m_serie1);
    m_chart->addSeries(m_serie2);
    m_serie1->setUseOpenGL(true);//openGl 加速
    m_serie2->setUseOpenGL(true);
    QValueAxis *axisX = new QValueAxis;
    m_value1Points.clear();
    axisX->setRange(0,TIMESPAN);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("axisX");

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,400.0);
    axisY->setTitleText("axisY");

    m_chart->setAxisX(axisX,m_serie1);
    m_chart->setAxisY(axisY,m_serie1);
    m_chart->setAxisX(axisX,m_serie2);
    m_chart->setAxisY(axisY,m_serie2);
    m_chart->setMargins(QMargins(0,0,0,0));
    m_chart->layout()->setContentsMargins(0,0,0,0);
    //m_chart->setSpacings(10);
    m_chart->legend()->hide();
    //m_chart->setTitle("demo");
    //ui->frameLayout->addWidget(chartView);
    ui->frameLayout->insertWidget(0,chartView);


    ui->lbWarning->hide();
    //connect(&m_serialThread, &SlaveThread::request, this,&MainWindow::showRequest,Qt::QueuedConnection);

    connect(&m_serialThread, &SlaveThread::request, this,&MainWindow::showRequest);
    connect(&m_serialThread, &SlaveThread::information, this, &MainWindow::showInfo);
    connect(&m_serialThread, &SlaveThread::error, this, &MainWindow::processError);
    connect(&m_serialThread, &SlaveThread::timeout, this, &MainWindow::processTimeout);
    connect(&m_serialThread, &SlaveThread::opensuccess, this,&MainWindow::openComSuccess);
    connect(&m_serialThread, &SlaveThread::configPack, this , &MainWindow::parseConfig);
    connect(&m_serialThread, &SlaveThread::statusPack, this, &MainWindow::parseL6474Status);
    connect(&m_serialThread, &SlaveThread::hbPack, this, &MainWindow::parseHeartBeat);
    connect(ui->pbGetConfig, &QPushButton::clicked,&m_serialThread, &SlaveThread::sendGetConfigCMD);
    connect(ui->pbMoveFWD, &QPushButton::clicked , &m_serialThread, &SlaveThread::sendRunFWDCMD);
    connect(ui->pbSoftStop, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendSoftStop);
    connect(ui->pbMoveBWD, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendRunBWCMD);
    connect(ui->pbHardStop, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendHardStop);
    connect(ui->pbGetStatus, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendGetStatus);
    connect(ui->pbSetZero, &QPushButton::clicked, &m_serialThread, &SlaveThread::sendSetHome);
    connect(ui->pbMoveMark, &QPushButton::clicked, &m_serialThread, &SlaveThread::sltGoMark);
    connect(ui->pbEnable, &QPushButton::clicked, &m_serialThread, &SlaveThread::sltEnableController);
    connect(ui->pbDisable, &QPushButton::clicked, &m_serialThread, &SlaveThread::sltDisableController);

    connect(ui->cbSerialPort,SIGNAL(currentTextChanged(QString)),this,SLOT(sltPortChanged(QString)));
    connect(ui->cbBaudRate,SIGNAL(currentTextChanged(QString)),this,SLOT(sltBaudrateChanged(QString)));
    ui->dockBottom->installEventFilter(this);
    QTimer::singleShot(10,this,SLOT(onRestoreCatalogureView()));
    ReadSettings();
    timeId = startTimer(TIMERFREQ);
}

bool MainWindow::eventFilter(QObject * obj,QEvent * event)
{
    if(event->type() == QEvent::Resize && obj == ui->dockBottom){
        //QResizeEvent * resizeEvent = static_cast<QResizeEvent*>(event);
        //qDebug() << "new width:"  << resizeEvent->size().width() << " new height:" << resizeEvent->size().height();
        WriteSettings();
    }
    return QWidget::eventFilter(obj,event);
}

void MainWindow::ReadSettings()
{
    QSettings setting;
    setting.beginGroup(tr("Catalogue View"));
    QSize size = setting.value(tr("lastRuntimeSize"),QSize(1099,100)).toSize();
    setCatalogueViewSize(size);
    setting.endGroup();
    //qDebug() << "read size width:"  << size.width() << " height:" << size.height();
}

void MainWindow::WriteSettings()
{
    QSize size = ui->dockBottom->size();
    QSettings setting;
    setting.beginGroup(tr("Catalogue View"));
    setting.setValue(tr("lastRuntimeSize"),size);
    setting.setValue(tr("oldMaxSize"),QSize(16777215,16777215));
    setting.setValue(tr("oldMinSize"),QSize(1,1));
    //qDebug() << "last size width:"  << size.width() << " height:" << size.height();
    setting.endGroup();
}

void MainWindow::setCatalogueViewSize(QSize size)
{
    if(size.height() >= 0){
        //int nHeight = ui->dockBottom->height();
        //if(nHeight<size.height()){
        //    ui->dockBottom->setMinimumHeight(size.height());
        //}
        //else{
            ui->dockBottom->setMaximumHeight(size.height());
        //}
        //ui->dockBottom->sizeHint()
    }

}

void MainWindow::onRestoreCatalogureView()
{
    QSettings setting;
    QSize oldMaxSize = setting.value(tr("oldMaxSize"),QSize(16777215,16777215)).toSize();
    QSize oldMinSize = setting.value(tr("oldMinSize"),QSize(1,1)).toSize();
    //ui->dockBottom->setMaximumSize(oldMaxSize);
    ui->dockBottom->setMinimumSize(oldMinSize);

}

void MainWindow::sltFire()
{
    pointMutex.lock();
    m_value1Points.append(QPointF(1.0,2.5));
    pointMutex.unlock();
}

void MainWindow::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    if(event->timerId()==timeId){//定时器到时间,//模拟数据填充
        static bool hasStart = false;
        static int syncPeerTime = 0; //收到一个控制器数据的对端时间点，真实数据的的tick值
        //static int lastPeerTime = 0;    //收到的上次数据对端的时间点
        static long int syncTime = 0;    //收到第一个控制器数据的本地时间点
        static QTime dataTime(QTime::currentTime());
        long int eltime = dataTime.elapsed();
        static long int lasteltime = eltime; //pc端记录的上次时间

        if(isVisible()){
            QVector<QPointF> oldPoints = m_serie1->pointsVector();
            QVector<QPointF> points;
            if(isPeerReboot){
                hasStart = false;
                isPeerReboot = false;
                oldPoints.clear();
            }
            pointMutex.lock();
            int pointsize = m_value1Points.size();
            if(pointsize >0){ //有新鲜数据
                if(!hasStart){
                    syncPeerTime = m_value1Points.at(0).x();
                    syncTime = eltime;
                    hasStart = true;
                }

                long int pcpasstime = eltime - syncTime;  //PC端从收到第一个数据到现在为止经过的时间
                QVector<QPointF>::iterator iter = oldPoints.begin();
                while(iter!= oldPoints.end()){
                    qreal newtime = iter->x()  - (eltime - lasteltime) * 0.001;
                    if(newtime>0){
                        points.append(QPointF(newtime,iter->y()));
                    }

                    iter++;
                }
                for(int i = 0 ;i< m_value1Points.size();i++){
                    QPointF tpoint = m_value1Points.at(i);
                    long int peerDataRelativeTime = tpoint.x() - syncPeerTime; //本条数据距离第一条数据经过的时间
                    if(peerDataRelativeTime >= pcpasstime - (TIMESPAN * 1000)){
                        points.append(QPointF((tpoint.x() - syncPeerTime - pcpasstime) / 1000.0 + TIMESPAN,tpoint.y()));
                    }

                }
                m_value1Points.clear();
                lasteltime = eltime;
            }
            pointMutex.unlock();

            if(pointsize<=0){ //没有新鲜数据
                if(hasStart){ //已经开始计数了，但是上一个周期没有更新数据
                    //时间已经过去，更新原来的点的时间，并加上最后一个点
                    int oldlen = oldPoints.size();
                    qreal lastyvalue = 0;
                    for(int i = 0 ;i<oldlen;i++){
                        QPointF oldPoint = oldPoints.at(i);
                        qreal newtime = oldPoint.x() - (eltime - lasteltime) * 0.001;
                        lastyvalue = oldPoint.y();
                        if( newtime > 0 ){
                            points.append(QPointF(newtime,oldPoint.y()));
                        }
                    }
                    points.append(QPointF(TIMESPAN- 0.001,lastyvalue));
                    lasteltime = eltime;
                }
            }
            m_serie1->replace(points);

        }


    }
}

void MainWindow::sltSetMode()
{
    int stepidx = ui->cbStepMode->currentIndex();
    int stepvalue = 0;
    if(stepidx>=4){
        stepvalue = 0x4;
    }
    else
        stepvalue = stepidx;

    emit m_serialThread.setStepMode(stepvalue);
}

void MainWindow::sltMoveTo()
{
    int targetpos = ui->sbTargetPos->text().toInt();
    emit m_serialThread.goPos(targetpos);
}

void MainWindow::sltSetDec()
{
    int dec = ui->leDEC->text().toInt();
    dec = abs(dec);
    emit m_serialThread.setDec(dec);
}

void MainWindow::sltSetAcc()
{
    int acc = ui->leACC->text().toInt();
    acc = abs(acc);
    emit m_serialThread.setAcc(acc);
}

void MainWindow::sltSetMaxspeed()
{
    int maxspeed = ui->leMaxSpeed->text().toInt();
    maxspeed = abs(maxspeed);
    emit m_serialThread.setMaxSpeed(maxspeed);
    ui->gaugeCar->setMaxValue((double)maxspeed * 1.1);
}

void MainWindow::sltMoveStep()
{
    int dir = 0 ;
    int step = 0 ;
    if(ui->rbFWD->isChecked())
        dir = 1;
    else
        dir = 0;
    step = ui->sbStep->text().toInt();
    emit m_serialThread.moveStep(dir,step);
}

void MainWindow::parseL6474Status(const mavlink_l6474status_t & stpack)
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

void MainWindow::parseHeartBeat(const mavlink_heartbeat_t & hbpack)
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

    ui->lePosition->setText(QString::number(hbpack.position));
    double position = hbpack.position % this->stepPerCirclr;
    if(position < 0){
        position += this->stepPerCirclr;
    }
    ui->angleGauge->setValue1( position);
    ui->angleGauge->setValue2(hbpack.dynamic * this->stepPerCirclr);
    emit ui->angleGauge->valueChanged();

    ui->leAngleSpeed->setText(QString::number(hbpack.speed));
    ui->gaugeCar->setValue( (double)hbpack.speed);
    emit ui->gaugeCar->valueChanged();

    QPointF value1point((qreal)hbpack.tick,(qreal)hbpack.position);
    pointMutex.lock();
    m_value1Points.append(value1point);
    pointMutex.unlock();

}

void MainWindow::sltTValChanged(int newval)
{
    ui->lbTVal->setText(QString("%1mA").arg((newval+1) * 31.25));
}

void MainWindow::parseConfig(const mavlink_config_t &confpack)
{
    isPeerReboot = confpack.isRboot;
    ui->leACC->setText(QString::number(confpack.acc));
    ui->leDEC->setText(QString::number(confpack.dec));
    ui->leMaxSpeed->setText(QString::number(confpack.maxspeed));
    ui->leMinSpeed->setText(QString::number(confpack.minspeed));
    double maxspeed = (double) confpack.maxspeed;
    ui->gaugeCar->setMaxValue(maxspeed*1.1);
    ui->gaugeCar->setMinValue( 0 );
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

}

void MainWindow::sltSetTVal()
{
    unsigned char  newtval = (ui->sbTVal->value() & 0xff);
    emit this->m_serialThread.setTVal(newtval);
}

void MainWindow::sltProg1()
{
    emit this->m_serialThread.cmdProg(1);
}

void MainWindow::sltPortChanged(QString newvalue)
{
    QSettings * configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("/com/portname",newvalue);
    delete configIniWrite;
}

void MainWindow::sltBaudrateChanged(QString newvalue)
{
    QSettings * configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("/com/baudrate",newvalue);
    delete configIniWrite;
}

void MainWindow::sltSetMark()
{
    int32_t markvalue = 0;
    int setvalue = ui->leMark->text().toInt();
    markvalue = setvalue & 0x3fffff;
    emit m_serialThread.setMark(markvalue);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showInfo(const QString &s)
{
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Info: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
    ui->lwLog->insertItem(0,logitem);

}

void MainWindow::showRequest(const QString &s)
{
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Request: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
    ui->lwLog->insertItem(0,logitem);
}

void MainWindow::openComSuccess(const QString &s)
{
    Q_UNUSED(s);
    ui->cbBaudRate->setEnabled(false);
    ui->cbSerialPort->setEnabled(false);
    ui->pbConnect->setEnabled(false);
}

void MainWindow::processError(const QString &s)
{
    //activateRunButton();
    //qDebug() << tr("Error: %1").arg(s);
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1:Error!: %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
    ui->lwLog->insertItem(0,logitem);
    //m_trafficLabel->setText(tr("No traffic."));
}

void MainWindow::processTimeout(const QString &s)
{
    //qDebug() << tr("Status: Timeout, %1.").arg(s);
    QDateTime nowtime = QDateTime::currentDateTime();
    QString logitem = QString("%1 TimeOut : %2").arg(nowtime.toString("hh:mm:ss.zzz")).arg(s);
    ui->lwLog->insertItem(0,logitem);
    //m_trafficLabel->setText(tr("No traffic."));
}

void MainWindow::sltSerialConnect()
{
    ui->cbBaudRate->setEnabled(false);
    ui->cbSerialPort->setEnabled(false);
    ui->pbConnect->setEnabled(false);

    //qDebug()<<tr("Status: Running");
    m_serialThread.startSlave(ui->cbSerialPort->currentText(),
                        ui->cbBaudRate->currentText(),
                        2000);

}

void MainWindow::activateRunButton()
{
    ui->cbBaudRate->setEnabled(true);
    ui->cbSerialPort->setEnabled(true);
    ui->pbConnect->setEnabled(true);
}
