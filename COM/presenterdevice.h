#ifndef PRESENTERDEVICE_H
#define PRESENTERDEVICE_H

#include <QObject>
#include "devicecom.h"
#include "calibratorcom.h"
#include "voltmetercom.h"
#include <QList>
#include <QString>

class PresenterDevice : public QObject
{
    Q_OBJECT
    //метод для переноса СOM в калиборатор
    void transferSettComToModelCal();
    //метод для переноса СOM в вольтметр
    void transferSettComToModelVol();

public:
    explicit PresenterDevice(QObject *parent = nullptr);

public slots:
    //метод для поиска доступных COM-портов
    void SearchComPorts();
   // cлот для приема настроек Com от SettingsDialog
    void slotSettingsSaveCal(QString,quint32,quint32,quint32,quint32,quint32);
    void slotSettingsSaveVol(QString,quint32,quint32,quint32,quint32,quint32);
    //создание объекта по сигналу от DeviceDialog
    void slotCreatDeviceCom(const QString&, const QString&);
    //слот на создание обертки
    void creatDevice(const QString&);
    //слот на создание Serial Port
    void creatSerial();
signals:
    //передача перечня портов в Settings Dialog
    void signaListCom(const QList<QString>&);

private:
    struct SettingsCurrentComPort {
        QString m_name;
        quint32 m_baudRate;
        quint32 m_dataBits;
        quint32 m_parity;
        quint32 m_stopBits;
        quint32 m_flowControl;
    };
    //для хранения настроек COM из представления
    SettingsCurrentComPort m_SettingsComCal;
    SettingsCurrentComPort m_SettingsComVolt;

    //калибратор
    QString m_name_calibrator;
    DeviceCom* m_Calibrator = nullptr;

    //вольтметр
    QString m_name_voltmeter;
    DeviceCom* m_Voltmeter = nullptr;

    //список доступных COM-портов
    QList<QString> m_ListComPorts;

    //поток
    QThread* m_Thread= nullptr;
    bool m_isCreatThread = false;

};

#endif // PRESENTERDEVICE_H
