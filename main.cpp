#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

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
    MainWindow w;
    w.show();

    return a.exec();
}
