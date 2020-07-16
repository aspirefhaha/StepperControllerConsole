#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QPointF>
#include <QVector>
#include <QLineSeries>
#include "slavethread.h"

namespace Ui {
class MainWindow;
}
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    void setCatalogueViewSize(QSize size);
    void ReadSettings();
    void WriteSettings();
    bool eventFilter(QObject * obj,QEvent * event);

protected slots:
    void sltSerialConnect();
    void showRequest(const QString &s);
    void showInfo(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void openComSuccess(const QString &s);
    void parseConfig(const mavlink_config_t &);
    void parseHeartBeat(const mavlink_heartbeat_t &);
    void parseL6474Status(const mavlink_l6474status_t &);
    void onRestoreCatalogureView();
    void sltFreqSelected(bool);
    void sltTGChanged(bool);

private slots:
    void sltBaudrateChanged(QString newvalue);
    void sltPortChanged(QString newvalue);
    void sltMoveStep();
    void activateRunButton();
    void sltSetMark();
    void sltSetMaxspeed();
    void sltSetAcc();
    void sltSetDec();
    void sltMoveTo();
    void sltProg1();
    void sltTValChanged(int);
    void sltSetTVal();
    void sltSetMode();
    void sltFire();
    void sltSetUpPos();
    void sltSetDownPos();

private:
    Ui::MainWindow *ui;
    int stepPerCirclr ;
    SlaveThread m_serialThread;
    QChart *m_chart;
    QLineSeries * m_serie1;
    QLineSeries * m_serie2;
    QVector<QPointF> m_value1Points;
    QVector<QPointF> m_value2Points;
    QMutex pointMutex;
    bool isPeerReboot;
    int timeId;
};

#endif // MAINWINDOW_H
