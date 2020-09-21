#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QString>
#include <QList>

class DeviceCom // абстрактный класс
{
public:
    DeviceCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0) :
        m_name(name), m_baudRate(bR), m_dataBits(dB), m_parity(par), m_stopBits(stB), m_flowControl(fC)
    {

    }
    virtual ~DeviceCom() = 0;

    //гетер имени COM
    QString getName() const { return m_name; }

    //метод для установки параметров COM
    void SetParamCom(QString name,quint32 bR,quint32 dB, quint32 par, quint32 stop, quint32 Control)
    {
        m_name = name;
        m_baudRate = bR,
        m_dataBits = dB;
        m_parity = par;
        m_stopBits = stop;
        m_flowControl = Control;
    }

    virtual void OpenSerial() = 0;
    virtual void CloseSerial() = 0;
    //

protected:
    //настройки COM
    QString m_name;
    quint32 m_baudRate;
    quint32 m_dataBits;
    quint32 m_parity;
    quint32 m_stopBits;
    quint32 m_flowControl;


};



#endif // DEVICECOM_H

