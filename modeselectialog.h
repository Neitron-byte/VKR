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

signals:
    void signalOperation(const uint);
    void signalEnterNum();

private slots:


    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::ModeSelectialog *ui;


};

#endif // MODESELECTIALOG_H
