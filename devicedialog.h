#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "settingcomdialog.h"
#include <QString>
#include <QDebug>

namespace Ui {
class DeviceDialog;
}

class DeviceDialog : public QDialog
{
    Q_OBJECT

    void CheckApply();

public:
    explicit DeviceDialog(QWidget *parent = nullptr);
    ~DeviceDialog();
    bool CheckComPorts();
    QString getNameCal();
    QString getNameVol();

private:
    Ui::DeviceDialog *ui;
    void AddModelCal();//добавляем модели калибратора в представление
    void AddModelVol();//аналогично для вольтметра


    // QWidget interface
public slots:

    void SetNameComPort(QString,QString);

private slots:

    void on_pushButton_Apply_Cal_clicked();
    void on_pushButton_Apply_Vol_clicked();
    void on_pushButton_Discon_Cal_clicked();
    void on_pushButton_Discon_Vol_clicked();

signals:
    //сигнал на создание объекта
    void signalCreatCalibrator(const QString& ,const QString&);

    void signalUnLock();
    void signalConnectWriteLog(const QString);

private:

    QString m_ModelCal;//хранить модель калибратора
    QString m_ModelVol;// хранить модель вольтметра
    QString m_NamePortCal;
    QString m_NamePortVol;

    bool m_ApplyCol;
    bool m_ApplyVol;
};


#endif // DEVICEDIALOG_H

