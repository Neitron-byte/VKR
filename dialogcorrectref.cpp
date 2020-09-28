#include "dialogcorrectref.h"
#include "ui_dialogcorrectref.h"

DialogCorrectRef::DialogCorrectRef(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCorrectRef)
{
    ui->setupUi(this);
    ui->doubleSpinBox_Val->setMinimum(0);
    ui->doubleSpinBox_Val->setMaximum(10);
    ui->doubleSpinBox_Val->setSingleStep(0.1);
}

DialogCorrectRef::~DialogCorrectRef()
{
    delete ui;
}

void DialogCorrectRef::on_pushButton_Next_clicked()
{
    float Temp = ui->doubleSpinBox_Val->value();
    emit signalSetCor(Temp);
    emit signalStartWork();
    this->hide();
}
