#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QStringList>
#include <QTextEdit>

void MainWindow::SetLenght(int Num)
{
    ui->doubleSpinBox_temp->setMinimum(0);
    ui->doubleSpinBox_temp->setMaximum(40);
    ui->doubleSpinBox_temp->setSingleStep(0.1);

    ui->doubleSpinBox_Volt->setMinimum(0);
    ui->doubleSpinBox_Volt->setMaximum(100);
    ui->doubleSpinBox_Volt->setSingleStep(0.1);

    ui->lineEdit_fullname->setMaxLength(Num);
    ui->lineEdit_Num->setMaxLength(Num);
    ui->lineEdit_ver_dev->setMaxLength(Num);
}

void MainWindow::AddItem()
{
    //данные о поверяемом устр-ве
    ui->comboBox_typeverdev->addItem(QStringLiteral("With squa func"),QVariant("squa"));
    ui->comboBox_typeverdev->addItem(QStringLiteral("With line func"),QVariant("line"));

    ui->comboBox_typerefdev->addItem(QStringLiteral("With squa func"),QVariant("squa"));
    ui->comboBox_typerefdev->addItem(QStringLiteral("With line func"),QVariant("line"));


}

bool MainWindow::CheckInputData()
{
    if(ui->doubleSpinBox_temp->value() <= 0){
        QMessageBox::information(this, tr("Info"),"Please input correct temp");
        return false;
    }

    if(ui->lineEdit_fullname->text() == ""){
        QMessageBox::information(this, tr("Info"),"Please input fullname");
        return false;
    }

    if(ui->lineEdit_ver_dev->text() == ""){
        QMessageBox::information(this, tr("Info"),"Please input model");
        return false;
    }

    if(ui->lineEdit_Num->text() == ""){
        QMessageBox::information(this, tr("Info"),"Please input serial number");
        return false;
    }

    if(ui->doubleSpinBox_Volt->value() <= 0){
        QMessageBox::information(this, tr("Info"),"Please input correct Volt");
        return false;
    }
    return true;

}

void MainWindow::connects()
{
    //передача доступных портов из PresentDevice в Settings Dialog
    connect(m_PresenterDevice,SIGNAL(signaListCom(const QList<QString>&)),m_SettingsCom,SLOT(InitialComPorts(const QList<QString>&)));
    connect(this,SIGNAL(CheckCom()),m_PresenterDevice,SLOT(SearchComPorts()),Qt::DirectConnection);


    //сохранение настроек СOM портов из SettingsDialog в PresenterDevice
    connect(m_SettingsCom,SIGNAL(SignalSetSettingsCal(QString,uint,uint,uint,uint,uint)),
            m_PresenterDevice,SLOT(slotSettingsSaveCal(QString,uint,uint,uint,uint,uint)));
    connect(m_SettingsCom,SIGNAL(SignalSetSettingsVol(QString,uint,uint,uint,uint,uint)),
            m_PresenterDevice,SLOT(slotSettingsSaveVol(QString,uint,uint,uint,uint,uint)));

    //передача Com портов из Setting в DialogDevice
    connect(m_SettingsCom,SIGNAL(TransmitNameCom(QString,QString)),m_DeviceDialog,SLOT(SetNameComPort(QString,QString)));

    //сохранение название приборов
    connect(m_DeviceDialog,SIGNAL(signalSaveNameCal(QString)),m_PresenterDevice,SLOT(slotSaveNameCal(QString)));
    connect(m_DeviceDialog,SIGNAL(signalSaveNameVol(QString)),m_PresenterDevice,SLOT(slotSaveNameVol(QString)));

    //создание объектов
    connect(m_DeviceDialog,SIGNAL(signalCreatDevice(int)),m_PresenterDevice,SLOT(slotCreatDevice(int)));
    connect(m_PresenterDevice,SIGNAL(SetPointDevice(const DeviceCom*,const DeviceCom*)),m_algoritm,SLOT(setPoint(const DeviceCom*,const DeviceCom*)));

    //for open Coms
    connect(m_DeviceDialog,SIGNAL(signalOpenCal()),m_PresenterDevice,SLOT(slotOpenComCal()));
    connect(m_DeviceDialog,SIGNAL(signalOpenVol()),m_PresenterDevice,SLOT(slotOpenComVol()));

    //for close Coms
    connect(m_DeviceDialog,SIGNAL(signalCloseComCal()),m_PresenterDevice,SLOT(slotCloseComCal()));
    connect(m_DeviceDialog,SIGNAL(signalCloseComVol()),m_PresenterDevice,SLOT(slotCloseComVol()));



    //передача сообщений в строку состояния
    connect(m_PresenterDevice,SIGNAL(signalWriteStatusCal(QString)),this,SLOT(StatusMessage1(QString)));
    connect(m_PresenterDevice,SIGNAL(signalWriteStatusVol(QString)),this,SLOT(StatusMessage2(QString)));

    //передача сообщений в RealLog
    connect(m_SettingsCom,SIGNAL(signalCOMWriteLog(QString)),this,SLOT(slotWriteLog(QString)));
    connect(m_algoritm,SIGNAL(error_(QString)),this, SLOT(slotWriteLog(QString)));
    connect(m_DeviceDialog,SIGNAL(signalConnectWriteLog(QString)),this,SLOT(slotWriteLog(QString)));

    //запуск алгоритма
    connect(m_DeviceDialog,SIGNAL(CreatAlgorithm()),m_PresenterDevice,SLOT(slotCreatAlgoritm()));

    //сохранение данных из gui
    connect(this,SIGNAL(signalSaveData(float,QString,QString,QString)),m_data,SLOT(SetData(float,QString,QString,QString)));
    connect(this,SIGNAL(signalSaveDataDevice(bool,bool,float)),m_algoritm,SLOT(slotSaveDataDevice(bool,bool,float)));

    //выбор процедуры поверки
    connect(m_ModeSelectDialog,SIGNAL(signalOperation(uint)),m_algoritm,SLOT(setOperatioNumber(uint)));

    //задание количество циклов поверки
    connect(m_ModeSelectDialog,SIGNAL(signalEnterNum()),this,SLOT(EnterNumberCycles()));
    connect(m_DialogNumCycles,SIGNAL(signalSetNum(uint)),m_algoritm,SLOT(setNumberCycles(uint)));

    //сигнал запуска поверки
    connect(m_DialogNumCycles,SIGNAL(signalStartWork()),m_algoritm,SLOT(StartWork()));
    //cигнал окончания проверки
    connect(m_algoritm,SIGNAL(EndProcess()),this,SLOT(slotViewModeDialog()));

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_SettingsCom (new SettingComDialog),
      m_DeviceDialog (new DeviceDialog),
      m_ModeSelectDialog(new ModeSelectialog),
      m_data(new Data),
      m_algoritm(new algoritm),
      m_DialogNumCycles (new DialogNumCycles)


{
    ui->setupUi(this);

    //Statusbar
    m_status1 = new QLabel;
    ui->statusbar->addWidget(m_status1);
    m_status2 = new QLabel;
    ui->statusbar->addWidget(m_status2);

    //отдельный поток для взаимодействия с приборами
    m_Thread = new QThread;
    m_PresenterDevice = new PresenterDevice(m_data,m_algoritm);
    m_PresenterDevice->moveToThread(m_Thread);
    m_algoritm->moveToThread(m_Thread);
    connect(m_Thread, SIGNAL(finished()), m_algoritm,SLOT(deleteLater()));
    connect(m_Thread, SIGNAL(finished()), m_PresenterDevice, SLOT(deleteLater()));

    m_Thread->start();
    qDebug()<<m_PresenterDevice->thread();

    this->connects();

    this->CheckCom();

    //TimeDate
    m_timerinterval = 1000;
    m_idTimer = startTimer(m_timerinterval);
    time = QTime::currentTime();
    date = QDate::currentDate();
    slot_set_Time(time.toString(Qt::SystemLocaleLongDate));
    slot_set_Date(date.toString(Qt::SystemLocaleLongDate));


    //данные
    this->slotLockStart();
    //блокируем кнопку старт
    ui->pushButton_start->setEnabled(false);

    ui->textEditLog->setReadOnly(true);

    //сигнал на появление диалогового окна выбора операции поверки
    //connect(m_data,SIGNAL(signalNextAction()),this,SLOT(slotViewModeDialog()));

    //разблокировка главного виджета после подключения
    connect(m_PresenterDevice,SIGNAL(signalUnLock()),this,SLOT(slotUnLockStart()));

    //ограничение на количество cимволов в lineEdit
    this->SetLenght(5);
    //добавление данных в комбобоксы
    this->AddItem();


}

MainWindow::~MainWindow()
{

    delete m_SettingsCom;
    delete m_DeviceDialog;
    delete m_ModeSelectDialog;
    //delete m_PresenterDevice;
    delete m_data;
    delete m_DialogNumCycles;


    m_Thread->quit();
    m_Thread->wait();

    delete ui;
}


void MainWindow::on_action_Exit_triggered()
{

    this->close();

}


void MainWindow::on_action_Configure_triggered()
{
    //this->CheckCom();
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


void MainWindow::StatusMessage1(const QString &message)
{
    m_status1->setText(m_DeviceDialog->getNameCal()+" : "+message);
}

void MainWindow::StatusMessage2(const QString &message)
{
    m_status2->setText(m_DeviceDialog->getNameVol()+" : "+message);
}

void MainWindow::slotWriteLog(const QString& msg)
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
    ui->pushButton_save->setEnabled(false);
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
    //ui->pushButton_start->setEnabled(true);
    ui->pushButton_save->setEnabled(true);
}

void MainWindow::EnterNumberCycles()
{
    m_DialogNumCycles->show();
}


void MainWindow::timerEvent(QTimerEvent *event)
{

    time = QTime::currentTime();
    date = QDate::currentDate();
    slot_set_Time(time.toString(Qt::SystemLocaleLongDate));
    slot_set_Date(date.toString(Qt::SystemLocaleLongDate));

}



void MainWindow::slotViewModeDialog()
{
    m_ModeSelectDialog->show();

}


void MainWindow::on_doubleSpinBox_temp_valueChanged(double arg1)
{

}


void MainWindow::on_pushButton_save_clicked()
{
    if (ui->pushButton_save->text() == "SAVE") {
         if(this->CheckInputData()){
             float Temp = ui->doubleSpinBox_temp->value();
             QString Name = ui->lineEdit_fullname->text();
             QString Model = ui->lineEdit_ver_dev->text();
             QString Num = ui->lineEdit_Num->text();
             bool TypeDev, TypeRefDev;
             qDebug()<< ui->comboBox_typeverdev->currentData();
             qDebug()<< ui->comboBox_typerefdev->currentData();
             if(ui->comboBox_typeverdev->currentData().toString() == "squa"){
                 TypeDev = true;
             } else{
                 TypeDev = false;
             }
             if(ui->comboBox_typerefdev->currentData().toString() == "squa"){
                 TypeRefDev = true;
             } else{
                 TypeRefDev = false;
             }
             float Volt = ui->doubleSpinBox_Volt->value();
             qDebug()<<"SlotSendData";
             qDebug()<<Temp;
             qDebug()<<Name;
             qDebug()<<Model;
             qDebug()<< Num;
             qDebug()<<TypeDev;
             qDebug()<<TypeRefDev;
             qDebug()<<Volt;
             emit signalSaveData(Temp,Name,Model,Num);
             emit signalSaveDataDevice(TypeDev,TypeRefDev,Volt);
             this->slotWriteLog("Data is successfully stored");

             this->slotLockStart();
             ui->pushButton_start->setEnabled(true);
             ui->pushButton_save->setEnabled(true);
             ui->pushButton_save->setText("EDIT");

         }

    } else {
        this->slotUnLockStart();
        ui->pushButton_save->setText("SAVE");
        ui->pushButton_start->setEnabled(false);
    }


}

void MainWindow::on_pushButton_start_clicked()
{
    m_ModeSelectDialog->show();

}
