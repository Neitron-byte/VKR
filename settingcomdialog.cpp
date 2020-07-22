#include "settingcomdialog.h"
#include "ui_settingcomdialog.h"

SettingComDialog::SettingComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingComDialog)
{
    ui->setupUi(this);
}

SettingComDialog::~SettingComDialog()
{
    delete ui;
}
