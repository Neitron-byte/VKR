#ifndef PRESENTDATE_H
#define PRESENTDATE_H

#include <modeldate.h>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>



class PresentDate : public QObject
{
    Q_OBJECT
    bool CheckDate();

public:
    PresentDate(QObject *parent = 0);
    ~PresentDate();
signals:
    void signalInLog(const QString);
    void signalsLockStart();
    void signalNextAction();

public slots:
    void setDate(double,QString,QString,QString,bool,bool,double);

private:
    ModelDate* m_model;//модель данных о поверяемом устройстве


};

#endif // PRESENTDATE_H
