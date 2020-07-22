#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SettingsCom = new SettingComDialog;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_action_SettingsComPort_triggered()
{
    m_SettingsCom->show();
}
