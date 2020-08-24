#include "devicedialog.h"
#include "ui_devicedialog.h"

DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);

    m_ComPortCal = new QSerialPort(this);
    m_ComPortVol = new QSerialPort(this);
    AddModelCal();
    AddModelVol();
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


//bool DeviceDialog::CheckComPorts()
//{

//    if(m_NamePortCal != "" && m_NamePortVol != ""){
//        return true;
//    } else{
//        QMessageBox msgBox;
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setWindowTitle("Information");
//        msgBox.setInformativeText("COM is not configured.\nPlease configure COM in the Tab Settings -> Configure.");
//        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//        msgBox.setDefaultButton(QMessageBox::Ok);
//        msgBox.exec();
//    }
//}

void DeviceDialog::SetNameComPort(QString ComCal, QString ComVal)
{
    m_NamePortCal = ComCal;
    m_NamePortVol = ComVal;
    ui->comboBox_Com_Cal->addItem(m_NamePortCal);
    ui->comboBox_Com_Vol->addItem(m_NamePortVol);
}







void DeviceDialog::on_pushButton_Apply_Cal_clicked()
{

}
