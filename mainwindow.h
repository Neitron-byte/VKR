#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingcomdialog.h"
#include "devicedialog.h"
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SettingComDialog* m_SettingsCom;
    DeviceDialog* m_DeviceDialog;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_Exit_triggered();

    void on_action_Configure_triggered();

    void on_action_Devices_triggered();


private:
    Ui::MainWindow *ui;

public slots:

};
#endif // MAINWINDOW_H
