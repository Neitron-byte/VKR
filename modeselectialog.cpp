#include "modeselectialog.h"
#include "ui_modeselectialog.h"
#include <QDebug>

ModeSelectialog::ModeSelectialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelectialog)

{
    ui->setupUi(this);
    //id - 301 - "inaccuracy DC -> AC, 1 kHz"
    // id - 302 - "frequency verification"
    ui->comboBoxAction->addItem(QStringLiteral("inaccuracy DC -> AC, 1 kHz"),QVariant(301));
    ui->comboBoxAction->addItem(QStringLiteral("frequency verification"),QVariant(302));

}

ModeSelectialog::~ModeSelectialog()
{

}


void ModeSelectialog::on_pushButton_OK_clicked()
{
    qDebug()<<ui->comboBoxAction->currentData().toInt();
    emit signalOperation(ui->comboBoxAction->currentData().toUInt());
    emit signalEnterNum();
    this->hide();
}

void ModeSelectialog::on_pushButton_Cancel_clicked()
{
    this->close();
}
