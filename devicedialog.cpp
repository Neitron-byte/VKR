#include "devicedialog.h"
#include "ui_devicedialog.h"

void DeviceDialog::CheckApply()
{
    if(m_ApplyCol && m_ApplyVol){
        this->hide();
    }
}

DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);

    m_NamePortCal = "";
    m_NamePortVol = "";
    AddModelCal();
    AddModelVol();

    m_ApplyCol = false;
    m_ApplyVol = false;
 }

DeviceDialog::~DeviceDialog()
{

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


bool DeviceDialog::CheckComPorts()
{

    if(m_NamePortCal == "" && m_NamePortVol == ""){
        return true;
    } else{

    return false;
    }
}

QString DeviceDialog::getNameCal()
{
    return m_ModelCal;
}

QString DeviceDialog::getNameVol()
{
    return m_ModelVol;
}

void DeviceDialog::SetNameComPort(QString ComCal, QString ComVal)
{
    m_NamePortCal = ComCal;
    m_NamePortVol = ComVal;
    ui->comboBox_Com_Cal->addItem(m_NamePortCal);
    ui->comboBox_Com_Vol->addItem(m_NamePortVol);
}


void DeviceDialog::on_pushButton_Apply_Cal_clicked()
{
    emit SignalOpenCal();
    m_ModelCal = ui->comboBox_Device_Cal->currentText();
    ui->comboBox_Com_Cal->setEnabled(false);
    ui->comboBox_Device_Cal->setEnabled(false);
    m_ApplyCol = true;
    CheckApply();
}

void DeviceDialog::on_pushButton_Apply_Vol_clicked()
{
    emit SignalOpenVol();
    m_ModelVol = ui->comboBox_Device_Vol->currentText();
    ui->comboBox_Com_Vol->setEnabled(false);
    ui->comboBox_Device_Vol->setEnabled(false);
    m_ApplyVol = true;
    CheckApply();

}

void DeviceDialog::on_pushButton_Discon_Cal_clicked()
{
    ui->comboBox_Com_Cal->setEnabled(true);
    ui->comboBox_Device_Cal->setEnabled(true);
    this->SignalCloseCal();
    m_ApplyCol = false;
}

void DeviceDialog::on_pushButton_Discon_Vol_clicked()
{
    ui->comboBox_Com_Vol->setEnabled(true);
    ui->comboBox_Device_Vol->setEnabled(true);
    this->SignalCloseVol();
    m_ApplyVol = false;
}
