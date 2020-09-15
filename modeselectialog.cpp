#include "modeselectialog.h"
#include "ui_modeselectialog.h"

ModeSelectialog::ModeSelectialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelectialog)
{
    ui->setupUi(this);
    ui->comboBoxAction->addItem(QStringLiteral("inaccuracy DC -> AC, 1 kHz"),1);
    ui->comboBoxAction->addItem(QStringLiteral("frequency verification"),2);

}

ModeSelectialog::~ModeSelectialog()
{
    delete ui;
}



void ModeSelectialog::on_pushButton_OK_clicked()
{
    emit signalStartOperation(ui->comboBoxAction->currentIndex());
}
