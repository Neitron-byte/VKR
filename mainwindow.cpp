#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_data(new PresentDate),
      m_SettingsCom (new SettingComDialog),
      m_DeviceDialog (new DeviceDialog)
{
    ui->setupUi(this);



    //Statusbar
    m_status1 = new QLabel;
    ui->statusbar->addWidget(m_status1);
    m_status2 = new QLabel;
    ui->statusbar->addWidget(m_status2);

    //поток для калибратора
    m_ThreadCal = new QThread(this);
    m_ComPortCal = new ComPort;
    m_ComPortCal->moveToThread(m_ThreadCal);
    connect(m_ThreadCal, SIGNAL(finished()), m_ComPortCal, SLOT(deleteLater()));
    m_ThreadCal->start();
    qDebug() << m_ThreadCal->currentThreadId();

    //поток для вольтметра
    m_ThreadVol = new QThread(this);
    m_ComPortVol = new ComPort;
    m_ComPortVol->moveToThread(m_ThreadVol);
    connect(m_ThreadVol, SIGNAL(finished()),m_ComPortVol,SLOT(deleteLater()));
    m_ThreadVol->start();
    qDebug() << m_ThreadVol->currentThreadId();

    connect (m_SettingsCom,SIGNAL(TransmitNameCom(QString,QString)),m_DeviceDialog,SLOT(SetNameComPort(QString,QString)));
    connect(m_SettingsCom, SIGNAL(SignalSetSettingsCal(QString,qint32,qint32,qint32,qint32,qint32)),
            m_ComPortCal,SLOT(SetSettingCom(QString,qint32,qint32,qint32,qint32,qint32)));
    connect(m_SettingsCom, SIGNAL(SignalSetSettingsVol(QString,qint32,qint32,qint32,qint32,qint32)),
            m_ComPortVol,SLOT(SetSettingCom(QString,qint32,qint32,qint32,qint32,qint32)));


    connect(this,SIGNAL(CheckCom()),m_SettingsCom,SLOT(SlotCheckCom()));

    connect(m_ComPortCal,SIGNAL(SignalStatusMessage(QString)),this, SLOT(StatusMessage1(QString)));
    connect(m_ComPortVol,SIGNAL(SignalStatusMessage(QString)),this, SLOT(StatusMessage2(QString)));

    //OpenSerial
    connect(m_DeviceDialog,SIGNAL(SignalOpenCal()),m_ComPortCal,SLOT(OpenSerial1()));
    connect(m_DeviceDialog,SIGNAL(SignalOpenVol()),m_ComPortVol,SLOT(OpenSerial1()));

    //CloseSerial
    connect(m_DeviceDialog,SIGNAL(SignalCloseCal()),m_ComPortCal,SLOT(CloseSerial()));
    connect(m_DeviceDialog,SIGNAL(SignalCloseVol()),m_ComPortVol,SLOT(CloseSerial()));

    //TimeDate
    m_timerinterval = 1000;
    m_idTimer = startTimer(m_timerinterval);
    time = QTime::currentTime();
    date = QDate::currentDate();
    slot_set_Time(time.toString(Qt::SystemLocaleLongDate));
    slot_set_Date(date.toString(Qt::SystemLocaleLongDate));

    //данные о поверяемом устр-ве
    ui->comboBox_typeverdev->addItem(QStringLiteral("With squa func"));
    ui->comboBox_typeverdev->addItem(QStringLiteral("With line func"));

    ui->comboBox_typerefdev->addItem(QStringLiteral("With squa func"));
    ui->comboBox_typerefdev->addItem(QStringLiteral("With line func"));

    QIntValidator IntVal(0,100,ui->lineEdit_Temp);
    ui->lineEdit_Temp->setValidator(&IntVal);

    QIntValidator IntVal2(0,100,ui->lineEdit_Volt);
    ui->lineEdit_Volt->setValidator(&IntVal2);


    connect(ui->pushButton_start,SIGNAL(clicked(bool)),this,SLOT(slotSetData(bool)));


}

MainWindow::~MainWindow()
{
    delete m_ComPortCal;
    delete m_ComPortVol;
    delete m_SettingsCom;
    delete m_DeviceDialog;

    m_ThreadCal->quit();
    m_ThreadCal->wait();

    m_ThreadVol->quit();
    m_ThreadVol->wait();
    delete ui;
}


void MainWindow::on_action_Exit_triggered()
{
    this->close();
}


void MainWindow::on_action_Configure_triggered()
{
    this->CheckCom();
    m_SettingsCom->show();
}

void MainWindow::on_action_Devices_triggered()
{
    if(m_DeviceDialog->CheckComPorts()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Information");
        msgBox.setInformativeText("COM is not configured.\nPlease configure COM in the Tab Settings -> Configure.");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
    m_DeviceDialog->show();
    }
}

void MainWindow::slot_set_Time(const QString str)
{
    ui->label_Time->setText(str);
}

void MainWindow::slot_set_Date(const QString str)
{
    ui->label_Date->setText(str);
}

void MainWindow::slotSetData(bool)
{
    quint32 Temp = ui->lineEdit_Temp->text().toInt();
    QString Name = ui->lineEdit_fullname->text();
    QString Model = ui->lineEdit_ver_dev->text();
    QString Num = ui->lineEdit_Num->text();
    bool TypeDev, TypeRefDev;
    if(ui->comboBox_typeverdev == "With squa func"){
        TypeDev = true;
    } else{
        TypeDev = false;
    }
    if(ui->comboBox_typerefdev == "With squa func"){
        TypeRefDev = true;
    } else{
        TypeRefDev = false;
    }
    quint32 Volt = ui->lineEdit_Volt->text().toInt();
    emit signalSendData(Temp,Name,Model,Num,TypeDev,TypeRefDev,Volt);

}

void MainWindow::StatusMessage1(const QString &message)
{
    m_status1->setText(m_DeviceDialog->getNameCal()+" : "+message);
}

void MainWindow::StatusMessage2(const QString &message)
{
    m_status2->setText(m_DeviceDialog->getNameVol()+" : "+message);
}


void MainWindow::timerEvent(QTimerEvent *event)
{

    time = QTime::currentTime();
    date = QDate::currentDate();
    slot_set_Time(time.toString(Qt::SystemLocaleLongDate));
    slot_set_Date(date.toString(Qt::SystemLocaleLongDate));

}
