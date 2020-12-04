
#include <QApplication>
#include <QTranslator>

#include "StepperConsole.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator * translator = new QTranslator;
    if(translator->load(":/StepMotorConsole.qm")){
        a.installTranslator(translator);
    }
    QCoreApplication::setOrganizationName("FHAHA");
    QCoreApplication::setOrganizationDomain("fhaha.cn");
    QCoreApplication::setApplicationName("StepMotorConsole");
#if 0
    MainWindow w;
    w.show();
#else
    StepperConsole stepperConsole;
    stepperConsole.show();
#endif
    return a.exec();
}
