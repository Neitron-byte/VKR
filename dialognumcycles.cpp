#include "dialognumcycles.h"
#include "ui_dialognumcycles.h"

DialogNumCycles::DialogNumCycles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNumCycles)
{
    ui->setupUi(this);
//    ui->doubleSpinBox_Volt->setMinimum(0);
//    ui->doubleSpinBox_Volt->setMaximum(100);
//    ui->doubleSpinBox_Volt->setSingleStep(0.1);
    ui->spinBox_NumCycles->setMinimum(3);
    ui->spinBox_NumCycles->setMaximum(100);
    ui->spinBox_NumCycles->setSingleStep(1);

}

DialogNumCycles::~DialogNumCycles()
{
    delete ui;
}

void DialogNumCycles::on_pushButton_Next_clicked()
{
    emit signalSetNum(ui->spinBox_NumCycles->value());
    emit signalStartWork();
    this->hide();
}

void DialogNumCycles::on_pushButton_STOP_clicked()
{
    this->close();
}
