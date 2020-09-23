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

public slots:
    //метод для поиска доступных COM-портов
    void SearchComPorts();
   // cлот для приема настроек Com от SettingsDialog
    void slotSettingsSaveCal(QString,quint32,quint32,quint32,quint32,quint32);
    void slotSettingsSaveVol(QString,quint32,quint32,quint32,quint32,quint32);


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

};

#endif // PRESENTERDEVICE_H
