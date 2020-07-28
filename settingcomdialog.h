#ifndef SETTINGCOMDIALOG_H
#define SETTINGCOMDIALOG_H

#include <QDialog>
#include "ComPort.h"

namespace Ui {
class SettingComDialog;
}

class SettingComDialog : public QDialog
{
    Q_OBJECT
    QList<QString> m_ListComPorts;

    ComPort* m_ComCal;
    ComPort* m_ComVol;

public:
    explicit SettingComDialog(QWidget *parent = nullptr);
    ~SettingComDialog();
    void SearchComPorts();
    void InitialComPorts();
    void InitialBoudrate();
    void InitialDataBits();
    void InitialParity();
    void InitialStopBits();
    void InitialFlowControl();



private slots:
    void on_ApplyButton_Cal_clicked();


private:
    Ui::SettingComDialog *ui;
};

#endif // SETTINGCOMDIALOG_H
