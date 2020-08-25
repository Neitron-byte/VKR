#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_SettingsCom = new SettingComDialog;
    m_DeviceDialog = new DeviceDialog;

    m_ComPortCal = new ComPort;
    m_ComPortVol = new ComPort;

    connect (m_SettingsCom,SIGNAL(TransmitNameCom(QString,QString)),m_DeviceDialog,SLOT(SetNameComPort(QString,QString)));
    connect(m_SettingsCom, SIGNAL(SignalSetSettingsCal(QString,qint32,qint32,qint32,qint32,qint32)),
            m_ComPortCal,SLOT(SetSettingCom(QString,qint32,qint32,qint32,qint32,qint32)));
    connect(m_SettingsCom, SIGNAL(SignalSetSettingsVol(QString,qint32,qint32,qint32,qint32,qint32)),
            m_ComPortVol,SLOT(SetSettingCom(QString,qint32,qint32,qint32,qint32,qint32)));
}

MainWindow::~MainWindow()
{
    delete m_ComPortCal;
    delete m_ComPortVol;
    delete m_SettingsCom;
    delete m_DeviceDialog;
    delete ui;
}


void MainWindow::on_action_Exit_triggered()
{
    this->close();
}


void MainWindow::on_action_Configure_triggered()
{
    m_SettingsCom->show();
}

void MainWindow::on_action_Devices_triggered()
{
    m_DeviceDialog->show();
}


