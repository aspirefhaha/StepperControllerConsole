#include "FreqStepDlg.h"
#include "ui_FreqStepDlg.h"
#include <QSettings>

FreqStepDlg::FreqStepDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FreqStepDlg)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/motorcon.png"));
    sltReset();
}

FreqStepDlg::~FreqStepDlg()
{
    delete ui;
}

void FreqStepDlg::sltAccept()
{
     QSettings * configIniSave = new QSettings("config.ini",QSettings::IniFormat);


#define  SvSF(row,col)  do{ \
    configIniSave->setValue("Cust/Step" #col "_" #row , ui->leCustWait##col##_##row->text());\
    configIniSave->setValue("Cust/Freq" #col "_" #row , ui->leCustFreq##col##_##row->text());\
}while(0)
     SvSF(1,1);
     SvSF(1,2);
     SvSF(1,3);
     SvSF(1,4);
     SvSF(1,5);
     SvSF(1,6);
     SvSF(1,7);
     SvSF(2,1);
     SvSF(2,2);
     SvSF(2,3);
     SvSF(2,4);
     SvSF(2,5);
     SvSF(2,6);
     SvSF(2,7);
     SvSF(3,1);
     SvSF(3,2);
     SvSF(3,3);
     SvSF(3,4);
     SvSF(3,5);
     SvSF(3,6);
     SvSF(3,7);
     SvSF(4,1);
     SvSF(4,2);
     SvSF(4,3);
     SvSF(4,4);
     SvSF(4,5);
     SvSF(4,6);
     SvSF(4,7);
     SvSF(5,1);
     SvSF(5,2);
     SvSF(5,3);
     SvSF(5,4);
     SvSF(5,5);
     SvSF(5,6);
     SvSF(5,7);

    if(ui->rbSpec1->isChecked()){
        configIniSave->setValue("Cust/Choose",1);
    }
    else if(ui->rbSpec2->isChecked()){
        configIniSave->setValue("Cust/Choose",2);
    }
    else if(ui->rbSpec3->isChecked()){
        configIniSave->setValue("Cust/Choose",3);
    }
    else if(ui->rbSpec4->isChecked()){
        configIniSave->setValue("Cust/Choose",4);
    }
    else {
        configIniSave->setValue("Cust/Choose",5);
    }
     delete configIniSave;
    accept();

}
void FreqStepDlg::sltCancel()
{
    reject();
}
void FreqStepDlg::sltReset()
{
    QSettings * configIniLoad = new QSettings("config.ini",QSettings::IniFormat);

#define  LdSF(row,col)  do{ \
    int step = configIniLoad->value("Cust/Step" #col "_" #row ).toInt();\
    ui->leCustWait##col##_##row->setText(QString::number(step));\
    int freq = configIniLoad->value("Cust/Freq" #col "_" #row).toInt();\
    ui->leCustFreq##col##_##row->setText(QString::number(freq));\
}while(0)

    LdSF(1,1);
    LdSF(1,2);
    LdSF(1,3);
    LdSF(1,4);
    LdSF(1,5);
    LdSF(1,6);
    LdSF(1,7);
    LdSF(2,1);
    LdSF(2,2);
    LdSF(2,3);
    LdSF(2,4);
    LdSF(2,5);
    LdSF(2,6);
    LdSF(2,7);
    LdSF(3,1);
    LdSF(3,2);
    LdSF(3,3);
    LdSF(3,4);
    LdSF(3,5);
    LdSF(3,6);
    LdSF(3,7);
    LdSF(4,1);
    LdSF(4,2);
    LdSF(4,3);
    LdSF(4,4);
    LdSF(4,5);
    LdSF(4,6);
    LdSF(4,7);
    LdSF(5,1);
    LdSF(5,2);
    LdSF(5,3);
    LdSF(5,4);
    LdSF(5,5);
    LdSF(5,6);
    LdSF(5,7);

    int choose = configIniLoad->value("Cust/Choose").toInt();
    switch(choose){
    case 2:
        ui->rbSpec2->setChecked(true);
        break;
    case 3:
        ui->rbSpec3->setChecked(true);
        break;
    case 4:
        ui->rbSpec4->setChecked(true);
        break;
    case 5:
        ui->rbSpec5->setChecked(true);
        break;
    case 1:
    default:
        ui->rbSpec1->setChecked(true);
        break;
    }
    delete configIniLoad;
}
