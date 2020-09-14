#ifndef MODESELECTIALOG_H
#define MODESELECTIALOG_H

#include <QDialog>

namespace Ui {
class ModeSelectialog;
}

class ModeSelectialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeSelectialog(QWidget *parent = nullptr);
    ~ModeSelectialog();

private:
    Ui::ModeSelectialog *ui;
};

#endif // MODESELECTIALOG_H
