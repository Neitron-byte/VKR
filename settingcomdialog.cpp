#include "settingcomdialog.h"
#include "ui_settingcomdialog.h"

SettingComDialog::SettingComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingComDialog)
{
    ui->setupUi(this);
    m_ApplyCom = false;
    m_ApplyCal = false;
    m_ApplyVol = false;

    SearchComPorts(); //Обнаружение COM-портов
    //Add in view
    InitialComPorts();
    InitialBoudrate();
    InitialDataBits();
    InitialParity();
    InitialStopBits();
    InitialFlowControl();

    m_ComCal = new ComPort();
    m_ComVol = new ComPort();


  }

SettingComDialog::~SettingComDialog()
{
    delete ui;
    delete m_ComCal;
    delete m_ComVol;
}

void SettingComDialog::SearchComPorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        m_ListComPorts .append(info.portName());
    }
}

void SettingComDialog::InitialComPorts()
{

    if(!m_ListComPorts.isEmpty()){
        for (const auto& Com : m_ListComPorts) {
            ui->SetComBox_Cal->addItem(Com);

        }
        for (const auto& Com : m_ListComPorts) {
            if(Com != ui->SetComBox_Cal->currentText()){
            ui->SetComBox_Volt->addItem(Com);
            }
        }
        m_ApplyCom = true;

    } else{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
        msgBox.setInformativeText("WARNING!\nCOM-ports were not found.\nPlease check the hardware connection.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

}

void SettingComDialog::InitialBoudrate()
{
    ui->BoudrateBox_Cal->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->BoudrateBox_Cal->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->BoudrateBox_Cal->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->BoudrateBox_Cal->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);

    ui->BoudrateBox_Volt->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->BoudrateBox_Volt->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->BoudrateBox_Volt->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->BoudrateBox_Volt->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);

}

void SettingComDialog::InitialDataBits()
{
    ui->DataBitsBox_Cal->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->DataBitsBox_Cal->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->DataBitsBox_Cal->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->DataBitsBox_Cal->addItem(QStringLiteral("8"), QSerialPort::Data8);

    ui->DataBitsBox_Volt->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->DataBitsBox_Volt->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->DataBitsBox_Volt->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->DataBitsBox_Volt->addItem(QStringLiteral("8"), QSerialPort::Data8);
}

void SettingComDialog::InitialParity()
{
    ui->ParityBox_Cal->addItem(tr("None"), QSerialPort::NoParity);
    ui->ParityBox_Cal->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->ParityBox_Cal->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->ParityBox_Cal->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->ParityBox_Cal->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->ParityBox_Volt->addItem(tr("None"), QSerialPort::NoParity);
    ui->ParityBox_Volt->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->ParityBox_Volt->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->ParityBox_Volt->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->ParityBox_Volt->addItem(tr("Space"), QSerialPort::SpaceParity);
}

void SettingComDialog::InitialStopBits()
{
    ui->StopBitsBox_Cal->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->StopBitsBox_Cal->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
    ui->StopBitsBox_Cal->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->StopBitsBox_Volt->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->StopBitsBox_Volt->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
    ui->StopBitsBox_Volt->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

void SettingComDialog::InitialFlowControl()
{
    ui->FlowControlBox_Cal->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->FlowControlBox_Cal->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->FlowControlBox_Cal->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);

    ui->FlowControlBox_Volt->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->FlowControlBox_Volt->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->FlowControlBox_Volt->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SettingComDialog::SetEnabledCal(bool b)
{
    ui->SetComBox_Cal->setEnabled(b);
    ui->BoudrateBox_Cal->setEnabled(b);
    ui->DataBitsBox_Cal->setEnabled(b);
    ui->DataBitsBox_Cal->setEnabled(b);
    ui->ParityBox_Cal->setEnabled(b);
    ui->StopBitsBox_Cal->setEnabled(b);
    ui->FlowControlBox_Cal->setEnabled(b);
}

void SettingComDialog::SetEnabledVolt(bool b)
{
    ui->SetComBox_Volt->setEnabled(b);
    ui->BoudrateBox_Volt->setEnabled(b);
    ui->DataBitsBox_Volt->setEnabled(b);
    ui->DataBitsBox_Volt->setEnabled(b);
    ui->ParityBox_Volt->setEnabled(b);
    ui->StopBitsBox_Volt->setEnabled(b);
    ui->FlowControlBox_Volt->setEnabled(b);
}

bool SettingComDialog::CheckApply()
{
    if(m_ApplyCal && m_ApplyVol){
        return true;
    }
    return false;
}



//void SettingComDialog::showStatus(QString message)
//{
//    m_status->showMessage(message);
//}



void SettingComDialog::on_ApplyButton_Cal_clicked()
{
    m_ComCal->setName(ui->SetComBox_Cal->currentText());
    m_ComCal->setBoudRate(ui->BoudrateBox_Cal->currentText().toInt());
    m_ComCal->setDataBits(ui->DataBitsBox_Cal->currentText().toInt());
    m_ComCal->setParity(ui->ParityBox_Cal->itemData(ui->ParityBox_Cal->currentIndex()).toInt());
    m_ComCal->setStopBits(ui->StopBitsBox_Cal->currentText().toInt());
    m_ComCal->setFlowControl(ui->FlowControlBox_Cal->itemData(ui->FlowControlBox_Cal->currentIndex()).toInt());

    SetEnabledCal(false);

    m_ApplyCal = true;
    if(CheckApply()){
        hide();
    }

}



void SettingComDialog::on_ApplyVoltButton_Volt_clicked()
{
    m_ComVol->setName(ui->SetComBox_Volt->currentText());
    m_ComVol->setBoudRate(ui->BoudrateBox_Volt->currentText().toInt());
    m_ComVol->setDataBits(ui->DataBitsBox_Volt->currentText().toInt());
    m_ComVol->setParity(ui->ParityBox_Volt->itemData(ui->ParityBox_Cal->currentIndex()).toInt());
    m_ComVol->setStopBits(ui->StopBitsBox_Volt->currentText().toInt());
    m_ComVol->setFlowControl(ui->FlowControlBox_Volt->itemData(ui->FlowControlBox_Cal->currentIndex()).toInt());

    SetEnabledVolt(false);
    m_ApplyVol = true;
    if(CheckApply()){
        hide();
    }
}

void SettingComDialog::on_pushButton_Edit_Cal_clicked()
{
    SetEnabledCal(true);
    m_ApplyCal = false;
}

void SettingComDialog::on_pushButton_EditVol_clicked()
{
    SetEnabledVolt(true);
    m_ApplyVol = false;
}

void SettingComDialog::on_SetComBox_Cal_currentIndexChanged(const QString &arg1)
{
    if(m_ApplyCom){
    m_ApplyCom = false;
    qDebug()<< "Change Cal";
    if(ui->SetComBox_Volt->count() > 1){
     ui->SetComBox_Volt->clear();
    }
    if(!m_ListComPorts.isEmpty()){
        ui->SetComBox_Volt->clear();
        for (const auto& Com : m_ListComPorts) {
            if(Com != arg1){
                ui->SetComBox_Volt->addItem(Com);
            }
        }
    }
    m_ApplyCom = true;
    }
}




