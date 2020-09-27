#include "calibratorcom.h"
#include "QMessageBox"


bool CalibratorCom::OpenSerial()
{
    qDebug()<<"Cal Com Open";
    qDebug()<<m_serial->thread();
    m_serial->setPortName(m_SettingsCom.m_name);
    m_serial->setBaudRate(m_SettingsCom.m_baudRate);
    m_serial->setDataBits(m_SettingsCom.m_dataBits);
    m_serial->setParity(m_SettingsCom.m_parity);
    m_serial->setStopBits(m_SettingsCom.m_stopBits);
    m_serial->setFlowControl(m_SettingsCom.m_flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {

        return true;
    } else {

        return false;

    }
}

bool CalibratorCom::CloseSerial()
{
    if (m_serial->isOpen()){
        m_serial->close();

        return true;
    }
    return false;
}

void CalibratorCom::CreatSerial()
{
    m_serial = new QSerialPort;
}

bool CalibratorCom::SendSerial(float V)
{
    QString SendData = "UD"+ QString::number(V) +"\r\n";
    m_serial->write(SendData.toLocal8Bit());
    qDebug()<<"DC"<< SendData.toLocal8Bit();
    if(m_serial->waitForBytesWritten(100)){
      return  true;
     } else{
        return false;
    }

}

bool CalibratorCom::SendFreqSerial(float V, uint F)
{
    QString SendData = "UA"+ QString::number(V)+"F"+QString::number(F)+"\r\n";
    m_serial->write(SendData.toLocal8Bit());
    qDebug()<<"Freq"<<SendData.toLocal8Bit();
    if(m_serial->waitForBytesWritten(100)){
      return  true;
     } else{
        return false;
    }
}




void CalibratorCom::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {

        emit Error_(m_serial->errorString());

        this->CloseSerial();
    }

}


