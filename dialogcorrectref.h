#ifndef DIALOGCORRECTREF_H
#define DIALOGCORRECTREF_H

#include <QDialog>

namespace Ui {
class DialogCorrectRef;
}

class DialogCorrectRef : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCorrectRef(QWidget *parent = nullptr);
    ~DialogCorrectRef();

signals:
    void signalSetCor(float);
    void signalStartWork();

private slots:
    void on_pushButton_Next_clicked();

private:
    Ui::DialogCorrectRef *ui;
};

#endif // DIALOGCORRECTREF_H
