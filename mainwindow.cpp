#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SettingsCom = new SettingComDialog;
    m_DeviceDialog = new DeviceDialog;

}

MainWindow::~MainWindow()
{
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

