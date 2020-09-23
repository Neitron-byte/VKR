#ifndef SETTINGCOMDIALOG_H
#define SETTINGCOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <QMessageBox>
#include <QList>


namespace Ui {
class SettingComDialog;
}

class SettingComDialog : public QDialog
{
    Q_OBJECT


public:
    explicit SettingComDialog(QWidget *parent = nullptr);
    ~SettingComDialog();


    void InitialBoudrate();
    void InitialDataBits();
    void InitialParity();
    void InitialStopBits();
    void InitialFlowControl();
    void SetEnabledCal(bool);
    void SetEnabledVolt(bool);
    bool CheckApply();


private slots:
    void on_ApplyButton_Cal_clicked();
    void on_ApplyVoltButton_Volt_clicked();
    void on_pushButton_Edit_Cal_clicked();
    void on_pushButton_EditVol_clicked();
    void on_SetComBox_Cal_currentIndexChanged(const QString &arg1);
    //слот принимает список Com портов
    void InitialComPorts(const QList<QString>&);


private:
    Ui::SettingComDialog *ui;


signals:
    void TransmitNameCom(QString,QString);
    void SignalSetSettingsCal (QString,qint32,qint32,qint32,qint32,qint32);
    void SignalSetSettingsVol (QString,qint32,qint32,qint32,qint32,qint32);
    void signalCOMWriteLog(const QString);


private:

    QList<QString> m_List;
    bool m_ApplyCom;
    bool m_ApplyCal;
    bool m_ApplyVol;
};

#endif // SETTINGCOMDIALOG_H
