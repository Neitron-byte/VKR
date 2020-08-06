#include "devicedialog.h"
#include "ui_devicedialog.h"

DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);
    m_SettingComPorts = new SettingComDialog;
    m_ComPortCal = new QSerialPort(this);
    m_ComPortVol = new QSerialPort(this);


    addComPorts();

}

DeviceDialog::~DeviceDialog()
{
    delete m_SettingComPorts;
    delete ui;
}

void DeviceDialog::AddModelCal()
{
    ui->comboBox_Device_Cal->addItem("H4-7");
}

void DeviceDialog::AddModelVol()
{
    ui->comboBox_Device_Vol->addItem("Agilent 34420A");
}

void DeviceDialog::AddComCal()
{
    ui->comboBox_Com_Cal->addItem(m_SettingComPorts->getNameComCal());
}

void DeviceDialog::AddComVol()
{
    ui->comboBox_Com_Vol->addItem(m_SettingComPorts->getNameComVal());
}

void DeviceDialog::addComPorts()
{
//    if(!m_SettingComPorts->getNameComCal().isEmpty() && !m_SettingComPorts->getNameComVal().isEmpty()){
        AddComCal();
        AddComVol();
//    }
//    else{
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setWindowTitle("Information");
//        msgBox.setInformativeText("COM is not configured.\nPlease configure COM in the Tab Settings -> Configure.");
//        //msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        msgBox.exec();
//    }

}

bool DeviceDialog::CheckComPorts()
{
    qDebug()<<m_SettingComPorts->getNameComCal();
    qDebug()<<m_SettingComPorts->getNameComVal();
    if(m_SettingComPorts->getNameComCal() != "" && m_SettingComPorts->getNameComVal() != ""){
        return true;
    } else{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Information");
        msgBox.setInformativeText("COM is not configured.\nPlease configure COM in the Tab Settings -> Configure.");
        //msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void DeviceDialog::setVisible(bool visible)
{
    qDebug()<<visible;
    if(visible){

        if(CheckComPorts()){
        return;
        }

    }
}
