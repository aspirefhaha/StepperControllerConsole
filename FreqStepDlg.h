#ifndef FREQSTEPDLG_H
#define FREQSTEPDLG_H

#include <QDialog>

namespace Ui {
class FreqStepDlg;
}

class FreqStepDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FreqStepDlg(QWidget *parent = 0);
    ~FreqStepDlg();

protected slots:
    void sltAccept();
    void sltCancel();
    void sltReset();

private:
    Ui::FreqStepDlg *ui;
};

#endif // FREQSTEPDLG_H
