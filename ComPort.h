#ifndef COMPORT
#define COMPORT
#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

class ComPort: public QObject
{
     Q_OBJECT
    struct SettingsComPort {
        QString name;
        qint32 baudRate;
        //QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        //QString stringDataBits;
        QSerialPort::Parity parity;
        //QString stringParity;
        QSerialPort::StopBits stopBits;
        //QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        //QString stringFlowControl;
        //bool localEchoEnabled;
    };

    SettingsComPort m_SettingsCom;

    QSerialPort* m_serial;

public slots:
    void SetSettingCom(QString, qint32, qint32, qint32, qint32, qint32);
    void OpenSerial1();
    void CloseSerial();
    void CreateCom();

public:
    void setName(QString);
    void setBoudRate(qint32);
    void setDataBits(qint32);
    void setParity(qint32);
    void setStopBits(qint32);
    void setFlowControl(qint32);
    explicit ComPort(QObject *parent = 0);
    ~ComPort();
    QString getName();

    SettingsComPort setting();

signals:
    void SignalStatusMessage(const QString);
};

#endif // COMPORT
