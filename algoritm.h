#ifndef ALGORITM_H
#define ALGORITM_H

#include <QObject>

#include "COM/presenterdevice.h"
//#include "COM/devicecom.h"
#include "COM/calibrator.h"
#include "COM/voltmeter.h"
#include "QDebug"
#include "data.h"


class algoritm : public QObject
{
    Q_OBJECT

    //запуск операции по номеру
    void SelectProcess();
    void inaccuracyDC_AC();
    void freqVerification();
    bool checkResponse(const QString&);
    float calculate();


public:
    explicit algoritm (Data* pData, QObject *parent = nullptr) : QObject(parent)
    {
        m_OperationNumber =0;
        m_TypeDev = true;
        m_TypeRefDev = true;
        m_Voltage = 0;
        m_NumberCycles = 0;
        m_Frequency = 1;
        m_CorrectRef = 0;
        m_data = pData;
        m_ArrayForCH1 = new float [4];
        m_ArrayForCH2 = new float [4];
    }

    ~algoritm(){
        if(m_ArrayForCH1 != nullptr){
            delete m_ArrayForCH1;
        }

        if(m_ArrayForCH2 != nullptr){
            delete m_ArrayForCH2;
        }
    }

signals:
     void error_(const QString);
     void EndProcess();
     void SaveData(const QString&);



public slots:
    void setOperatioNumber(const uint);
    void setPoint(const Calibrator*, const Voltmeter*);
    void slotSaveDataDevice(uint , uint , float );
    void setNumberCycles(uint);
    void StartWork();
    void setValueCorrect(float );

private:
    //указатели на созданные калибратор и вольтметр
    Calibrator* m_Calibrator = nullptr;
    Voltmeter* m_Voltmeter = nullptr;

    //выбор процедуры поверки
    //id - 300 - "inaccuracy DC -> AC, 1 kHz"
    // id - 301 - "frequency verification"
    uint m_OperationNumber;


    //тип поверяемого преобразователя
    uint m_TypeDev; //2 - squa ; 1 - line

    //тип эталонного преобразователя
    uint m_TypeRefDev;//2 - squa ; 1 - line

    //Номинальное напряжение, на которое рассчитан преобразователь
    float m_Voltage;

    //Количество циклов
    uint m_NumberCycles;

    //Частота
    uint m_Frequency;

    //поправка на эталон
    float m_CorrectRef;

    //хранение данных
    const Data* m_data = nullptr;

    //массив для хранения значений в цикле
    float* m_ArrayForCH1;
    float* m_ArrayForCH2;
};

#endif // ALGORITM_H
