#include "devicedialog.h"
#include "ui_devicedialog.h"


DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);

    m_NamePortCal = "";
    m_NamePortVol = "";
    AddModelCal();
    AddModelVol();

    ui->pushButton_Con_Cal->setEnabled(false);
    ui->pushButton_Con_Vol->setEnabled(false);
}

DeviceDialog::~DeviceDialog()
{

    delete ui;
}

void DeviceDialog::AddModelCal()
{

    ui->comboBox_Device_Cal->addItem("H4-7", QVariant(100));
}

void DeviceDialog::AddModelVol()
{
    ui->comboBox_Device_Vol->addItem("Agilent 34420A", QVariant(200));
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
    if(ui->pushButton_Apply_Cal->text() == "Apply" ){
    m_ModelCal = ui->comboBox_Device_Cal->currentText();
    emit signalSaveNameCal(m_ModelCal);

    qDebug()<<ui->comboBox_Device_Cal->currentData().toInt();
    emit signalCreatDevice(ui->comboBox_Device_Cal->currentData().toInt());

    ui->comboBox_Com_Cal->setEnabled(false);
    ui->comboBox_Device_Cal->setEnabled(false);

    emit signalConnectWriteLog(m_ModelCal + " is creat");

    ui->pushButton_Apply_Cal->setText("Edit");
    ui->pushButton_Con_Cal->setEnabled(true);
    }
    else{
        ui->comboBox_Com_Cal->setEnabled(true);
        ui->comboBox_Device_Cal->setEnabled(true);
        ui->pushButton_Apply_Cal->setText("Apply");
        ui->pushButton_Con_Cal->setEnabled(false);

    }
}

void DeviceDialog::on_pushButton_Apply_Vol_clicked()
{
    if(ui->pushButton_Apply_Vol->text() == "Apply" ){
        m_ModelVol = ui->comboBox_Device_Vol->currentText();
        emit signalSaveNameVol(m_ModelVol);
        qDebug()<<ui->comboBox_Device_Vol->currentData().toInt();
        emit signalCreatDevice(ui->comboBox_Device_Vol->currentData().toInt());
        ui->comboBox_Com_Vol->setEnabled(false);
        ui->comboBox_Device_Vol->setEnabled(false);

        emit signalConnectWriteLog(m_ModelVol + " is creat");
         ui->pushButton_Apply_Vol->setText("Edit");
          ui->pushButton_Con_Vol->setEnabled(true);
    } else{
        ui->comboBox_Com_Vol->setEnabled(true);
        ui->comboBox_Device_Vol->setEnabled(true);
        ui->pushButton_Apply_Vol->setText("Apply");
        ui->pushButton_Con_Vol->setEnabled(false);
    }


}

void DeviceDialog::on_pushButton_Con_Vol_clicked()
{
    if(m_NamePortVol != ""){

    if(ui->pushButton_Con_Vol->text() == "Connect"){
        emit signalOpenVol();
        isOpenComVol = true;
        ui->pushButton_Con_Vol->setText("Disconnect");
    } else {
        emit signalCloseComVol();
        isOpenComVol = false;
        ui->pushButton_Con_Vol->setText("Connect");
    }
 } else{
        emit signalConnectWriteLog("Com for Voltmeter not assigned");
    }
}

void DeviceDialog::on_pushButton_Con_Cal_clicked()
{
    if(m_NamePortCal != ""){
    if(ui->pushButton_Con_Cal->text() == "Connect"){
        emit signalOpenCal();
        isOpenComCal = true;
        ui->pushButton_Con_Cal->setText("Disconnect");
    } else {
        emit signalCloseComCal();
        isOpenComCal = false;
        ui->pushButton_Con_Cal->setText("Connect");
    }
    } else{
        emit signalConnectWriteLog("Com for Cilabrator not assigned");
    }

}

void DeviceDialog::on_pushButton_clicked()
{
    if(isOpenComCal && isOpenComVol){

        emit CreatAlgorithm();
    }


    this->hide();
}
