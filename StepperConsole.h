#ifndef STEPPERCONSOLE_H
#define STEPPERCONSOLE_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QSplineSeries>
#include <QDateTime>
#include "slavethread.h"
#include "FreqStepDlg.h"
namespace Ui {
class stepperConsole;
}

QT_CHARTS_USE_NAMESPACE


class StepperConsole : public QMainWindow
{
    Q_OBJECT

public:
    explicit StepperConsole(QWidget *parent = 0);
    ~StepperConsole();

    int stepPerCirclr ;

protected slots:
    void sltSerialConnect();
    void sltBaudrateChanged(QString newvalue);
    void sltPortChanged(QString newvalue);
    void showRequest(const QString &s);
    void showInfo(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void openComSuccess(const QString &s);
    void parseConfig(const mavlink_config_t &);
    void parseHeartBeat(const mavlink_heartbeat_t &);
    void parseL6474Status(const mavlink_l6474status_t &);
    void parseCustStep(const mavlink_custstep_t &);
    void timerEvent(QTimerEvent *event);
    void sltSetMaxspeed();
    void sltSetAcc();
    void sltSetDec();
    void sltconfChart();
    void sltRunBWD();
    void sltSetTVal();
    void sltRunFWD();
    void sltSoftStop();
    void addLog(QString & logitem);
    void addLog(const char * logitem);
    void sltConfigFreqStep();
    void sltGetFreqStep();
    void sltStartEngine();
    void sltStopEngine();
    void sltHardStop();
    void sltMoveStep();
    void sltRunFreqChange(bool);
    void sltMoveFreqStepDir();
    void sltFreqSelected(bool selected);
    void sltTGChanged(bool);

private:
    Ui::stepperConsole *ui;

    SlaveThread m_serialThread;
    qreal m_x;
    qreal m_y;
    QChart *chart ;
    QChartView *chartView ;
    QLineSeries * m_baseSeries;
    QLineSeries * m_series;
    int timeId ;
    int checkerCmdTimerId ;
    QDateTime lastTime;
    bool isPeerReboot;
    uint32_t expectCmd;
    uint32_t lastAckCmd;
    FreqStepDlg freqStepDlg;

    void sendCustConfig();

};

#endif // STEPPERCONSOLE_H
