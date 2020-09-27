#include "voltmetercom.h"
#include <QMessageBox>


bool VoltmeterCom::OpenSerial()
{
    qDebug()<<"Vol Com Open";
    qDebug()<<m_serial->thread();
    m_serial->setPortName(m_SettingsCom.m_name);
    m_serial->setBaudRate(m_SettingsCom.m_baudRate);
    m_serial->setDataBits(m_SettingsCom.m_dataBits);
    m_serial->setParity(m_SettingsCom.m_parity);
    m_serial->setStopBits(m_SettingsCom.m_stopBits);
    m_serial->setFlowControl(m_SettingsCom.m_flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {

        QString SetRemote = "SYST:REM\r\n";
        QString SetCount = "SAMP:COUN 1\r\n";

        m_serial->write(SetRemote.toLocal8Bit());
        qDebug()<<"SYST:REM"<< SetRemote.toLocal8Bit();

        if(m_serial->waitForBytesWritten(100)){
            m_serial->write(SetCount.toLocal8Bit());
            qDebug()<<"SAMP:COUN"<< SetCount.toLocal8Bit();
            if(m_serial->waitForBytesWritten(100)){
                return true;
            }
        }
    }

    return false;

}

bool VoltmeterCom::CloseSerial()
{
    if (m_serial->isOpen()){
        m_serial->close();
        return true;
    }
    return false;
}

void VoltmeterCom::CreatSerial()
{
    m_serial = new QSerialPort;
}

void VoltmeterCom::Measurement(uint ch)
{
    //Отправка команды на выбор первого канал измерения
    QString Reques = "ROUT:TERM FRON"+ch+"\r\n";
    m_serial->write(Reques.toLocal8Bit());
    if(m_serial->waitForBytesWritten(100)){
        Reques = "READ?\r\n";
        m_serial->write(Reques.toLocal8Bit());
        if(m_serial->waitForBytesWritten(100)){

            //Из примера!!!!!!!!!!!!!!!!!

//            // write request
//            const QByteArray requestData = currentRequest.toUtf8();
//            serial.write(requestData);
//            if (serial.waitForBytesWritten(m_waitTimeout)) {
//    //! [8] //! [10]
//                // read response
//                if (serial.waitForReadyRead(currentWaitTimeout)) {
//                    QByteArray responseData = serial.readAll();
//                    while (serial.waitForReadyRead(10))
//                        responseData += serial.readAll();

//                    const QString response = QString::fromUtf8(responseData);
//    //! [12]
//                    emit this->response(response);
//    //! [10] //! [11] //! [12]
//                } else {
//                    emit timeout(tr("Wait read response timeout %1")
//                                 .arg(QTime::currentTime().toString()));
//                }
//    //! [9] //! [11]
//            } else {
//                emit timeout(tr("Wait write request timeout %1")
//                             .arg(QTime::currentTime().toString()));
//            }
        }
    }

    //!!!!!!!!!!!!!!!!!!!


}

void VoltmeterCom::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {

        emit Error_(m_serial->errorString());

        this->CloseSerial();
    }
}
