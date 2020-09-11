#ifndef PRESENTDATE_H
#define PRESENTDATE_H

#include <modeldate.h>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class PresentDate : public QObject
{
    Q_OBJECT


public:
    PresentDate();
    ~PresentDate();

public slots:
    void setDate(quint32,QString,QString,QString,bool,bool,quint32);

private:
    ModelDate* m_model;

};

#endif // PRESENTDATE_H
