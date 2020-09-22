#ifndef PRESENTERDEVICE_H
#define PRESENTERDEVICE_H

#include <QObject>
#include "devicecom.h"
#include <QList>
#include <QString>

class PresenterDevice : public QObject
{
    Q_OBJECT


public:
    explicit PresenterDevice(QObject *parent = nullptr);

    //статический метод для поиска доступных COM-портов
    static void SearchComPorts();

signals:

private:
    struct SettingsCurrentComPort {
        QString m_name;
        quint32 m_baudRate;
        quint32 m_dataBits;
        quint32 m_parity;
        quint32 m_stopBits;
        quint32 m_flowControl;
    };
    //для временного хранения настроек COM
    SettingsCurrentComPort m_SettingsCom1;
    SettingsCurrentComPort m_SettingsCom2;

    //калибратор
    QString m_name_calibrator;
    DeviceCom* m_Calibrator = nullptr;

    //вольтметр
    QString m_name_voltmeter;
    DeviceCom* m_Voltmeter = nullptr;

    //список доступных COM-портов
    static QList<QString> m_ListComPorts;

};

#endif // PRESENTERDEVICE_H
