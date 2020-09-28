#include "presenterdevice.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "QDebug"
#include "QThread"
#include "COM/h4_7.h"
#include "COM/hp34420a.h"

void PresenterDevice::creatDevice(const int id)
{
    switch (id) {
    case 100:
        qDebug()<<"Cal creat";
        m_Calibrator = new H4_7(m_SettingsComCal.m_name,m_SettingsComCal.m_baudRate,m_SettingsComCal.m_dataBits,
                                         m_SettingsComCal.m_parity,m_SettingsComCal.m_stopBits,m_SettingsComCal.m_flowControl);

        connect(m_Calibrator,SIGNAL(Error_(QString)),SIGNAL(signalWriteStatusCal(QString)));
        break;

    case 200:
        qDebug()<<"Vol creat";
        m_Voltmeter = new HP34420A (m_SettingsComVolt.m_name,m_SettingsComVolt.m_baudRate,m_SettingsComVolt.m_dataBits,
                                       m_SettingsComVolt.m_parity,m_SettingsComVolt.m_stopBits,m_SettingsComVolt.m_flowControl);
        connect(m_Voltmeter,SIGNAL(Error_(QString)),SIGNAL(signalWriteStatusVol(QString)));
        break;

    default:
        break;

    }

}

void PresenterDevice::slotOpenComCal()
{

    if(m_Calibrator->OpenSerial()){
            emit signalWriteStatusCal(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                      .arg(m_SettingsComCal.m_name).arg(m_SettingsComCal.m_baudRate).arg(m_SettingsComCal.m_dataBits)
                                      .arg(m_SettingsComCal.m_parity).arg(m_SettingsComCal.m_stopBits).arg(m_SettingsComCal.m_flowControl));

        isOpenCOMCal = true;
        this->CheckConnect();


    } else{

        signalWriteStatusCal(tr("Open error"));


    }



}

void PresenterDevice::slotOpenComVol()
{

    if(m_Voltmeter->OpenSerial()){
        emit signalWriteStatusVol(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                  .arg(m_SettingsComVolt.m_name).arg(m_SettingsComVolt.m_baudRate).arg(m_SettingsComVolt.m_dataBits)
                                  .arg(m_SettingsComVolt.m_parity).arg(m_SettingsComVolt.m_stopBits).arg(m_SettingsComVolt.m_flowControl));
    isOpenCOMVol = true;


    this->CheckConnect();

    } else{
        signalWriteStatusVol(tr("Open error"));
    }
}

void PresenterDevice::slotCloseComCal()
{

    if(m_Calibrator->CloseSerial()){
        signalWriteStatusCal("Disconnect");
        isOpenCOMCal = false;
    }
    else{
        signalWriteStatusCal("Serial is close");
    }
}

void PresenterDevice::slotCloseComVol()
{
    if(m_Voltmeter->CloseSerial()){
        signalWriteStatusVol("Disconnect");
        isOpenCOMVol = false;
    }
    else{
        signalWriteStatusVol("Serial is close");
    }
}

void PresenterDevice::slotCreatAlgoritm()
{
    emit SetPointDevice(m_Calibrator,m_Voltmeter);

}



void PresenterDevice::CheckConnect()
{
    if ( isOpenCOMCal && isOpenCOMVol){
        emit signalUnLock();
    }
}

void PresenterDevice::SearchComPorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        m_ListComPorts .append(info.portName());
    }
    if (!m_ListComPorts.isEmpty()){
        emit signaListCom(m_ListComPorts);
        qDebug() << "SearchCom";
        for (const QString& com : m_ListComPorts) {
            qDebug() << com;
        }
    }
    else{
        qDebug()<<"List empty";
    }

}

void PresenterDevice::slotSettingsSaveCal(QString name,uint bR,uint dB, uint par, uint stop, uint Control)
{
    qDebug()<<"Save Cal";
    m_SettingsComCal.m_name = name;
    m_SettingsComCal.m_baudRate = bR;
    m_SettingsComCal.m_dataBits = dB;
    m_SettingsComCal.m_parity = par;
    m_SettingsComCal.m_stopBits = stop;
    m_SettingsComCal.m_flowControl = Control;
}

void PresenterDevice::slotSettingsSaveVol(QString name,uint bR,uint dB, uint par, uint stop, uint Control)
{
    qDebug()<<"Save Vol";
    m_SettingsComVolt.m_name = name;
    m_SettingsComVolt.m_baudRate = bR;
    m_SettingsComVolt.m_dataBits = dB;
    m_SettingsComVolt.m_parity = par;
    m_SettingsComVolt.m_stopBits = stop;
    m_SettingsComVolt.m_flowControl = Control;
}

void PresenterDevice::slotSaveNameCal(const QString & NameCal)
{
    m_name_calibrator = NameCal;
}

void PresenterDevice::slotSaveNameVol(const QString & NameVol)
{
    m_name_voltmeter = NameVol;
}

void PresenterDevice::slotCreatDevice(const int id)
{

    //cоздаем нужное нам устройство
    this->creatDevice(id);
    qDebug()<<"ThreadPresenter "<<this->thread();

}


