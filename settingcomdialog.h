#ifndef SETTINGCOMDIALOG_H
#define SETTINGCOMDIALOG_H

#include <QDialog>
#include "ComPort.h"
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <QMessageBox>

namespace Ui {
class SettingComDialog;
}

class SettingComDialog : public QDialog
{
    Q_OBJECT



    bool m_ApplyCom;
    bool m_ApplyCal;
    bool m_ApplyVol;

public:
    explicit SettingComDialog(QWidget *parent = nullptr);
    ~SettingComDialog();

    void InitialComPorts();
    void InitialBoudrate();
    void InitialDataBits();
    void InitialParity();
    void InitialStopBits();
    void InitialFlowControl();
    void SetEnabledCal(bool);
    void SetEnabledVolt(bool);
    bool CheckApply();
    QString getNameComCal();
    QString getNameComVal();

private slots:
    void on_ApplyButton_Cal_clicked();
    void on_ApplyVoltButton_Volt_clicked();
    void on_pushButton_Edit_Cal_clicked();
    void on_pushButton_EditVol_clicked();
    void on_SetComBox_Cal_currentIndexChanged(const QString &arg1);
    void SlotCheckCom();


private:
    Ui::SettingComDialog *ui;


public slots:
    //virtual void setVisible(bool visible);

signals:
    void TransmitNameCom(QString,QString);
    void SignalSetSettingsCal (QString,qint32,qint32,qint32,qint32,qint32);
    void SignalSetSettingsVol (QString,qint32,qint32,qint32,qint32,qint32);
    void signalCOMWriteLog(const QString);
};

#endif // SETTINGCOMDIALOG_H
