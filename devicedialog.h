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


    QString m_ModelCal;//хранить модель калибратора
    QString m_ModelVol;// хранить модель вольтметра
    QString m_NamePortCal;
    QString m_NamePortVol;


    QSerialPort* m_ComPortCal = nullptr;//Com порт калибратора
    QSerialPort* m_ComPortVol = nullptr;//Com порт вольтметр

public:
    explicit DeviceDialog(QWidget *parent = nullptr);
    ~DeviceDialog();

private:
    Ui::DeviceDialog *ui;
    void AddModelCal();//добавляем модели калибратора в представление
    void AddModelVol();//аналогично для вольтметра
    //bool CheckComPorts();

    // QWidget interface
public slots:

    void SetNameComPort(QString,QString);

private slots:


    void on_pushButton_Apply_Cal_clicked();
};


#endif // DEVICEDIALOG_H
