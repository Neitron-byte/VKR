#ifndef DIALOGNUMCYCLES_H
#define DIALOGNUMCYCLES_H

#include <QDialog>

namespace Ui {
class DialogNumCycles;
}

class DialogNumCycles : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNumCycles(QWidget *parent = nullptr);
    ~DialogNumCycles();
signals:
    void signalSetNum(uint);
    void signalStartWork();

private slots:
    void on_pushButton_Next_clicked();

    void on_pushButton_STOP_clicked();

private:
    Ui::DialogNumCycles *ui;
};

#endif // DIALOGNUMCYCLES_H
