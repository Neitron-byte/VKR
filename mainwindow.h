#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingcomdialog.h"
#include "devicedialog.h"
#include "presentdate.h"
#include "modeselectialog.h"
#include <QToolBar>
#include <QThread>
#include <QDate>
#include <QTime>
#include <QTimer>
#include "COM/presenterdevice.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void SetLenght(int);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action_Exit_triggered();
    void on_action_Configure_triggered();
    void on_action_Devices_triggered();
    void slot_set_Time(const QString);
    void slot_set_Date(const QString);
    void slotSetData(bool);
    void on_pushButton_2_clicked();
    void slotViewModeDialog();

    void on_doubleSpinBox_temp_valueChanged(double arg1);

signals:

    void CheckCom();
    void signalSendData(double,QString,QString,QString,bool,bool,double);//сигнал сохранения введенных данных


private:
    Ui::MainWindow *ui;

    SettingComDialog* m_SettingsCom = nullptr;//Окно настроек Com портов
    DeviceDialog* m_DeviceDialog = nullptr;//Окно подключения к приборам
    ModeSelectialog* m_ModeSelectDialog = nullptr;//окно выбора операции поверки

    ComPort* m_ComPortCal= nullptr;//настройки COM калибратора
    ComPort* m_ComPortVol= nullptr;//настройки COM вольтметра
    QThread* m_ThreadCal= nullptr;//Поток для калибратора
    QThread* m_ThreadVol= nullptr;//Поток для вольтметра

    QLabel *m_status1 = nullptr;//статус подключения QSatusBar
    QLabel *m_status2 = nullptr;//статус подключения QSatusBar

    //Таймер для времени
    int m_timerinterval;
    int m_idTimer;
    QTime time;
    QDate date;

    //данные
    PresentDate* m_data = nullptr;

    //презентер для работы с оборудованием
    PresenterDevice* m_PresenterDevice = nullptr;

public slots:
    void StatusMessage1(const QString &message);
    void StatusMessage2(const QString &message);
    void slotWriteLog(const QString);
    void slotLockStart();
    void slotUnLockStart();

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
