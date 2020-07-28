#include "settingcomdialog.h"
#include "ui_settingcomdialog.h"

SettingComDialog::SettingComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingComDialog)
{
    ui->setupUi(this);


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
            ui->SetComBox_Volt->addItem(Com);
        }
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



void SettingComDialog::on_ApplyButton_Cal_clicked()
{
    m_ComCal->setName(ui->SetComBox_Cal->currentText());
    m_ComCal->setBoudRate(ui->BoudrateBox_Cal->currentText().toInt());
    m_ComCal->setDataBits(ui->DataBitsBox_Cal->currentText().toInt());
    m_ComCal->setParity(ui->ParityBox_Cal->itemData(ui->ParityBox_Cal->currentIndex()).toInt());
    m_ComCal->setStopBits(ui->StopBitsBox_Cal->currentText().toInt());
    m_ComCal->setFlowControl(ui->FlowControlBox_Cal->itemData(ui->FlowControlBox_Cal->currentIndex()).toInt());

    if(ui->SetComBox_Volt->count() > 0){
        ui->SetComBox_Volt->clear();
    }

    if(!m_ListComPorts.isEmpty()){
        for (const auto& Com : m_ListComPorts) {
            if(Com != ui->SetComBox_Cal->currentText()){
                ui->SetComBox_Volt->addItem(Com);
            }
        }
    }

}


