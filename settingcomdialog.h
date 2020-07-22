#ifndef SETTINGCOMDIALOG_H
#define SETTINGCOMDIALOG_H

#include <QDialog>

namespace Ui {
class SettingComDialog;
}

class SettingComDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingComDialog(QWidget *parent = nullptr);
    ~SettingComDialog();

private:
    Ui::SettingComDialog *ui;
};

#endif // SETTINGCOMDIALOG_H
