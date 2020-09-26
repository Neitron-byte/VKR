#ifndef PRESENTERDEVICE_H
#define PRESENTERDEVICE_H

#include <QObject>
#include "devicecom.h"
#include "calibratorcom.h"
#include "voltmetercom.h"
#include <QList>
#include <QString>
#include "algoritm.h"
#include "Data.h"

class algoritm;

class PresenterDevice : public QObject
{
    Q_OBJECT



public:
    explicit PresenterDevice(const Data* data = nullptr, const algoritm* algor= nullptr, QObject *parent = nullptr): QObject(parent)
    {
        m_data = data;
        m_algoritm = algor;
        m_name_calibrator = "";
        m_name_voltmeter = "";
        //this->SearchComPorts();

    }

public slots:
    //метод для поиска доступных COM-портов
    void SearchComPorts();
   // cлот для приема настроек Com от SettingsDialog
    void slotSettingsSaveCal(QString,uint,uint,uint,uint,uint);
    void slotSettingsSaveVol(QString,uint,uint,uint,uint,uint);
    //cлот для сохранения названия девайса
    void slotSaveNameCal(const QString&);
    void slotSaveNameVol(const QString&);

    //создание объекта по сигналу от DeviceDialog
    void slotCreatDevice(const int);

    //слот на создание девайса
    void creatDevice(const int);

    //cлоты на открытие портов
    void slotOpenComCal();
    void slotOpenComVol();

    //cлоты на закрытие портов
    void slotCloseComCal();
    void slotCloseComVol();

    //cлот на создание алгоритма после создания объектов
    void slotCreatAlgoritm();


signals:
    //передача перечня портов в Settings Dialog
    void signaListCom(const QList<QString>&);

    //передача сообщений о операциях и ошибках на главное окно
    void signalWriteStatusCal(const QString&);
    void signalWriteStatusVol(const QString&);
    void SetPointDevice(const DeviceCom*, const DeviceCom*);


private:
    struct SettingsCurrentComPort {
        QString m_name;
        uint m_baudRate;
        uint m_dataBits;
        uint m_parity;
        uint m_stopBits;
        uint m_flowControl;
    };
    //для хранения настроек COM из представления
    SettingsCurrentComPort m_SettingsComCal;
    SettingsCurrentComPort m_SettingsComVolt;

    //калибратор
    QString m_name_calibrator;
    CalibratorCom* m_Calibrator = nullptr;

    //вольтметр
    QString m_name_voltmeter;
    VoltmeterCom* m_Voltmeter = nullptr;

    //список доступных COM-портов
    QList<QString> m_ListComPorts;

    //алгоритмы поверки
    const algoritm* m_algoritm = nullptr;

    //хранение данных
    const Data* m_data = nullptr;
};

#endif // PRESENTERDEVICE_H
