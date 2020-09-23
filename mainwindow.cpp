#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

void MainWindow::SetLenght(int Num)
{
    ui->doubleSpinBox_temp->setMinimum(-10);
    ui->doubleSpinBox_temp->setMaximum(40);
    ui->doubleSpinBox_temp->setSingleStep(0.1);

    ui->doubleSpinBox_Volt->setMinimum(0);
    ui->doubleSpinBox_Volt->setMaximum(100);
    ui->doubleSpinBox_temp->setSingleStep(0.1);

    ui->lineEdit_fullname->setMaxLength(Num);
    ui->lineEdit_Num->setMaxLength(Num);
    ui->lineEdit_ver_dev->setMaxLength(Num);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_data(new PresentDate),
      m_SettingsCom (new SettingComDialog),
      m_DeviceDialog (new DeviceDialog),
      m_ModeSelectDialog(new ModeSelectialog),
      m_PresenterDevice(new PresenterDevice)


{
    ui->setupUi(this);

    //Statusbar
    m_status1 = new QLabel;
    ui->statusbar->addWidget(m_status1);
    m_status2 = new QLabel;
    ui->statusbar->addWidget(m_status2);

    //передача доступных портов из PresentDevice в Settings Dialog
    connect(this,SIGNAL(CheckCom()),m_PresenterDevice,SLOT(SearchComPorts()));
    connect(m_PresenterDevice,SIGNAL(signaListCom(const QList<QString>&)),m_SettingsCom,SLOT(InitialComPorts(const QList<QString>&)));

    //сохранение настроек СOM портов из SettingsDialog в PresenterDevice
    connect(m_SettingsCom,SIGNAL(SignalSetSettingsCal(QString,qint32,qint32,qint32,qint32,qint32)),
            m_PresenterDevice,SLOT(slotSettingsSaveCal(QString,quint32,quint32,quint32,quint32,quint32)));
    connect(m_SettingsCom,SIGNAL(SignalSetSettingsVol(QString,qint32,qint32,qint32,qint32,qint32)),
            m_PresenterDevice,SLOT(slotSettingsSaveVol(QString,quint32,quint32,quint32,quint32,quint32)));

    //передача Com портов из Setting в Dialog
    connect(m_SettingsCom,SIGNAL(TransmitNameCom(QString,QString)),m_DeviceDialog,SLOT(SetNameComPort(QString,QString)));

    //создание объектов устройств





    //поток для калибратора
//    m_ThreadCal = new QThread;
//    m_ComPortCal = new ComPort;
//    m_ComPortCal->moveToThread(m_ThreadCal);
//    connect(m_ThreadCal,SIGNAL(started()),m_ComPortCal,SLOT(CreateCom()));
//    connect(m_ThreadCal, SIGNAL(finished()), m_ComPortCal, SLOT(deleteLater()));
//    m_ThreadCal->start();


    //поток для вольтметра
//    m_ThreadVol = new QThread;
//    m_ComPortVol = new ComPort;
//    m_ComPortVol->moveToThread(m_ThreadVol);
//    connect(m_ThreadVol,SIGNAL(started()),m_ComPortVol,SLOT(CreateCom()));
//    connect(m_ThreadVol, SIGNAL(finished()),m_ComPortVol,SLOT(deleteLater()));
//    m_ThreadVol->start();

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

    //данные
    this->slotLockStart();
    ui->pushButton_2->setEnabled(false);
    connect(ui->pushButton_start,SIGNAL(clicked(bool)),this,SLOT(slotSetData(bool)));// сохранение данных в модели
    connect(this, SIGNAL(signalSendData(double,QString,QString,QString,bool,bool,double)),m_data,SLOT(setDate(double,QString,QString,QString,bool,bool,double)));
    connect(m_data,SIGNAL(signalInLog(QString)),this,SLOT(slotWriteLog(QString)));//запись в лог
    connect(m_data,SIGNAL(signalsLockStart()),this,SLOT(slotLockStart()));//блок виджетов
    //сигнал на появление диалогового окна выбора операции поверки
    connect(m_data,SIGNAL(signalNextAction()),this,SLOT(slotViewModeDialog()));

    //разблокировка главного виджета после подключения
    connect(m_DeviceDialog,SIGNAL(signalUnLock()),this,SLOT(slotUnLockStart()));

    //ограничение на количество cимволов в lineEdit
    this->SetLenght(5);
}

MainWindow::~MainWindow()
{

    delete m_SettingsCom;
    delete m_DeviceDialog;
    delete m_ModeSelectDialog;
    delete m_PresenterDevice;

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
    qDebug()<<"SlotSendData";
    double Temp = ui->doubleSpinBox_temp->value();
    QString Name = ui->lineEdit_fullname->text();
    QString Model = ui->lineEdit_ver_dev->text();
    QString Num = ui->lineEdit_Num->text();
    bool TypeDev, TypeRefDev;
    if(ui->comboBox_typeverdev->currentText() == "With squa func"){
        TypeDev = true;
    } else{
        TypeDev = false;
    }
    if(ui->comboBox_typerefdev->currentText() == "With squa func"){
        TypeRefDev = true;
    } else{
        TypeRefDev = false;
    }
    double Volt = ui->doubleSpinBox_Volt->value();
    qDebug()<<"SlotSendData2";
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

void MainWindow::slotWriteLog(const QString msg)
{
     qDebug()<< "slot Write";
    ui->textEditLog->append(ui->label_Time->text() + " : " + msg);
}

void MainWindow::slotLockStart()
{
    ui->lineEdit_fullname->setEnabled(false);
    ui->lineEdit_Num->setEnabled(false);
    ui->doubleSpinBox_temp->setEnabled(false);
    ui->lineEdit_ver_dev->setEnabled(false);
    ui->doubleSpinBox_Volt->setEnabled(false);
    ui->comboBox_typerefdev->setEnabled(false);
    ui->comboBox_typeverdev->setEnabled(false);
    ui->pushButton_start->setEnabled(false);
}

void MainWindow::slotUnLockStart()
{
    ui->lineEdit_fullname->setEnabled(true);
    ui->lineEdit_Num->setEnabled(true);
    ui->doubleSpinBox_temp->setEnabled(true);
    ui->lineEdit_ver_dev->setEnabled(true);
    ui->doubleSpinBox_Volt->setEnabled(true);
    ui->comboBox_typerefdev->setEnabled(true);
    ui->comboBox_typeverdev->setEnabled(true);
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}


void MainWindow::timerEvent(QTimerEvent *event)
{

    time = QTime::currentTime();
    date = QDate::currentDate();
    slot_set_Time(time.toString(Qt::SystemLocaleLongDate));
    slot_set_Date(date.toString(Qt::SystemLocaleLongDate));

}

void MainWindow::on_pushButton_2_clicked()
{

    this->slotUnLockStart();


}

void MainWindow::slotViewModeDialog()
{
    m_ModeSelectDialog->show();

}

void MainWindow::on_doubleSpinBox_temp_valueChanged(double arg1)
{

}
