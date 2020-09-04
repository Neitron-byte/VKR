#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingcomdialog.h"
#include "devicedialog.h"
#include <QToolBar>
#include <QThread>
#include <QDate>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SettingComDialog* m_SettingsCom = nullptr;
    DeviceDialog* m_DeviceDialog = nullptr;
    ComPort* m_ComPortCal= nullptr;
    ComPort* m_ComPortVol= nullptr;
    QThread* m_ThreadCal= nullptr;
    QThread* m_ThreadVol= nullptr;

    QLabel *m_status1 = nullptr;
    QLabel *m_status2 = nullptr;

    //Таймер для времени
    int m_timerinterval;
    int m_idTimer;
    QTime time;
    QDate date;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_Exit_triggered();

    void on_action_Configure_triggered();

    void on_action_Devices_triggered();

    void slot_set_Time(const QString);
    void slot_set_Date(const QString);

signals:

    void CheckCom();


private:
    Ui::MainWindow *ui;


public slots:
    void StatusMessage1(const QString &message);
    void StatusMessage2(const QString &message);


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
