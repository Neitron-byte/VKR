#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingcomdialog.h"
#include "devicedialog.h"
#include "modeselectialog.h"
#include <QToolBar>
#include <QThread>
#include <QDate>
#include <QTime>
#include <QTimer>
#include "COM/presenterdevice.h"
#include "Data.h"
#include "algoritm.h"
#include "dialognumcycles.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void SetLenght(int);
    void AddItem();
    bool CheckInputData();
    void connects();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action_Exit_triggered();
    void on_action_Configure_triggered();
    void on_action_Devices_triggered();
    void slot_set_Time(const QString);
    void slot_set_Date(const QString);
    void slotViewModeDialog();

    void on_doubleSpinBox_temp_valueChanged(double arg1);




    void on_pushButton_save_clicked();

    void on_pushButton_start_clicked();

signals:

    void CheckCom();

    //cигнал на сохранение данных
    void signalSaveData(const float, const QString , const QString ,const QString );
    //cигнал на сохранение данных в алгоритм
    void signalSaveDataDevice(bool,bool,const float);






public slots:
    //в статусы
    void StatusMessage1(const QString &);
    void StatusMessage2(const QString &);
    //в поле
    void slotWriteLog(const QString&);

    void slotLockStart();
    void slotUnLockStart();
    void EnterNumberCycles();
    // QObject interface

private:
    Ui::MainWindow *ui;

    SettingComDialog* m_SettingsCom = nullptr;//Окно настроек Com портов
    DeviceDialog* m_DeviceDialog = nullptr;//Окно подключения к приборам
    ModeSelectialog* m_ModeSelectDialog = nullptr;//окно выбора операции поверки
    DialogNumCycles* m_DialogNumCycles = nullptr;//окно задания количества циклов измерений

    //отдельный поток для взаимодействия с приборами
    QThread* m_Thread = nullptr;

    QLabel *m_status1 = nullptr;//статус подключения QSatusBar
    QLabel *m_status2 = nullptr;//статус подключения QSatusBar

    //Таймер для времени
    int m_timerinterval;
    int m_idTimer;
    QTime time;
    QDate date;

   //презентер для работы с оборудованием

    PresenterDevice* m_PresenterDevice = nullptr;

    //данные
    Data * m_data = nullptr;

    //алгоритм поверки
    algoritm* m_algoritm = nullptr;



protected:
    virtual void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
