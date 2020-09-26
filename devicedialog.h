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

    void on_pushButton_Con_Vol_clicked();

    void on_pushButton_Con_Cal_clicked();

    void on_pushButton_clicked();

signals:
    //сигнал на создание объекта
    void signalCreatDevice(const int);
    //сигналы на сохранение названий
    void signalSaveNameCal(const QString&);
    void signalSaveNameVol(const QString&);

    void signalUnLock();
    void signalConnectWriteLog(const QString);

    //сигнал на открытие com-порта для вольтметра
    void signalOpenVol();
    void signalOpenCal();

    //сигналы на закрытие COM
    void signalCloseComVol();
    void signalCloseComCal();

    //cигнал на создание алгоритма
    void CreatAlgorithm();

private:

    QString m_ModelCal;//хранить модель калибратора
    QString m_ModelVol;// хранить модель вольтметра
    QString m_NamePortCal;
    QString m_NamePortVol;

    bool isOpenComCal = false;
    bool isOpenComVol = false;

};


#endif // DEVICEDIALOG_H

