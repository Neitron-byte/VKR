#ifndef PRESENTERDEVICE_H
#define PRESENTERDEVICE_H

#include <QObject>

class PresenterDevice : public QObject
{
    Q_OBJECT
public:
    explicit PresenterDevice(QObject *parent = nullptr);

signals:

};

#endif // PRESENTERDEVICE_H
