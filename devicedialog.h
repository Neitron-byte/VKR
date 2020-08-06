#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "settingcomdialog.h"
#include <QString>

namespace Ui {
class DeviceDialog;
}

class DeviceDialog : public QDialog
{
    Q_OBJECT

    SettingComDialog* m_SettingComPorts = nullptr; // настройки Com-портов
    QString m_ModelCal;//хранить модель калибратора
    QString m_ModelVol;// хранить модель вольтметра
    QSerialPort* m_ComPortCal = nullptr;//Com порт калибратора
    QSerialPort* m_ComPortVol = nullptr;//Com порт вольтметр

public:
    explicit DeviceDialog(QWidget *parent = nullptr);
    ~DeviceDialog();

private:
    Ui::DeviceDialog *ui;
    void AddModelCal();//добавляем модели калибратора в представление
    void AddModelVol();//аналогично для вольтметра
    void AddComCal();//добавляем Com порт
    void AddComVol();
    void addComPorts();
    bool CheckComPorts();

    // QWidget interface
public slots:
    virtual void setVisible(bool visible);
};

#endif // DEVICEDIALOG_H
