#ifndef ALGORITM_H
#define ALGORITM_H

#include <QObject>

#include "COM/presenterdevice.h"
#include "COM/devicecom.h"
#include "COM/calibratorcom.h"
#include "COM/voltmetercom.h"
#include "QDebug"


class algoritm : public QObject
{
    Q_OBJECT

    //запуск операции по номеру
    void SelectProcess();
    void inaccuracyDC_AC();
    void freqVerification();

public:
    explicit algoritm (QObject *parent = nullptr) : QObject(parent)
    {
        m_OperationNumber =0;
        m_TypeDev = true;
        m_TypeRefDev = true;
        m_Voltage = 0;
        m_NumberCycles = 0;
        m_Frequency = 1;
    }

signals:
     void error_(const QString);

public slots:
    void setOperatioNumber(const uint);
    void setPoint(const DeviceCom*, const DeviceCom*);
    void slotSaveDataDevice(bool , bool , float );
    void setNumberCycles(uint);
    void StartWork();

private:
    //указатели на созданные калибратор и вольтметр
    DeviceCom* m_Calibrator = nullptr;
    DeviceCom* m_Voltmeter = nullptr;

    //выбор процедуры поверки
    //id - 300 - "inaccuracy DC -> AC, 1 kHz"
    // id - 301 - "frequency verification"
    uint m_OperationNumber;

    //параметры введенные пользователем
    //TypeDev,TypeRefDev,Volt

    //тип поверяемого преобразователя
    bool m_TypeDev; //true - squa ; false - line

    //тип эталонного преобразователя
    bool m_TypeRefDev;//true - squa ; false - line

    //Номинальное напряжение, на которое рассчитан преобразователь
    float m_Voltage;

    //Количество циклов
    uint m_NumberCycles;

    //Частота
    uint m_Frequency;
};

#endif // ALGORITM_H
