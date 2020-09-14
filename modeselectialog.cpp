#include "modeselectialog.h"
#include "ui_modeselectialog.h"

ModeSelectialog::ModeSelectialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelectialog)
{
    ui->setupUi(this);
    ui->comboBoxAction->addItem(QStringLiteral("inaccuracy DC -> AC, 1 kHz"));
    ui->comboBoxAction->addItem(QStringLiteral("frequency verification"));

}

ModeSelectialog::~ModeSelectialog()
{
    delete ui;
}
