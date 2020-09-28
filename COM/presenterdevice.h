#ifndef PRESENTERDEVICE_H
#define PRESENTERDEVICE_H

#include <QObject>
//#include "devicecom.h"
//#include "calibratorcom.h"
//#include "voltmetercom.h"

#include "COM/calibrator.h"
#include "COM/voltmeter.h"



#include <QList>
#include <QString>
#include "algoritm.h"
#include "Data.h"



class PresenterDevice : public QObject
{
    Q_OBJECT

    void CheckConnect();

public:
    explicit PresenterDevice(QObject *parent = nullptr): QObject(parent)
    {

        m_name_calibrator = "";
        m_name_voltmeter = "";

        isOpenCOMCal = false;
        isOpenCOMVol = false;


    }
    ~PresenterDevice(){
        if(m_Calibrator!= nullptr){
            delete m_Calibrator;
        }
        if(m_Voltmeter != nullptr){
            delete m_Voltmeter;
        }
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
    void SetPointDevice(const Calibrator*, const Voltmeter*);

    //сигнал разбокировки окон после коннекта с девайсами
    void signalUnLock();

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
    Calibrator* m_Calibrator = nullptr;
    bool isOpenCOMCal;


    //вольтметр
    QString m_name_voltmeter;
    Voltmeter* m_Voltmeter = nullptr;
    bool isOpenCOMVol;

    //список доступных COM-портов
    QList<QString> m_ListComPorts;


};

#endif // PRESENTERDEVICE_H
