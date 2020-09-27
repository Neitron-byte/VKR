#include "algoritm.h"
#include "QThread"

void algoritm::SelectProcess()
{
    switch (m_OperationNumber) {
    //id - 301 - "inaccuracy DC -> AC, 1 kHz"
    // id - 302 - "frequency verification"
    case 301:
        this->inaccuracyDC_AC();
        break;
    case 302:
        this->freqVerification();
        break;

    default:
        break;
    }
}

void algoritm::inaccuracyDC_AC()
{
    qDebug()<<"inaccuracyDC_AC";
    //НА МОЕЙ СОВЕСТИ) НУЖНО ПРАВИЛЬНО ОРГАНИЗОВАТЬ НАСЛЕДОВАНИЕ
    CalibratorCom* Cal = reinterpret_cast<CalibratorCom*>(m_Calibrator);
    VoltmeterCom* Voltmeter = reinterpret_cast<VoltmeterCom*>(m_Voltmeter);

    if(m_Voltage > 0 && m_OperationNumber > 0 && m_NumberCycles > 0){

        for (int var = 0; var < m_NumberCycles; ++var) {
            qDebug() << "Thread algoritm" << this->thread();

            //Команда на подачу пер напр V частотой F-1кГц
            if(Cal->SendFreqSerial(m_Voltage,m_Frequency)){
                emit error_("Error Send AC");
            }



            this->thread()->msleep(50);


            //Получение показаний с вольтметра 1 канал
            Voltmeter->Measurement(1);

            this->thread()->msleep(50);

            //Получение показаний с вольтметра 2 канал
            Voltmeter->Measurement(2);

            this->thread()->msleep(50);

            //Команда на подачу пост напр номиналом V
            if (Cal->SendSerial(m_Voltage)){
                emit error_("Error Send DC");
            }

            this->thread()->msleep(50);


            //Получение показаний с вольтметра

            //Команда на подачу пост напр номиналом V  отр полярности
            if (Cal->SendSerial(-m_Voltage)){
                emit error_("Error Send Neg DC");
            }
            this->thread()->msleep(50);


            //Получение показаний с вольтметра


            //Команда на подачу пер напр V частотой F-1кГц
            if(Cal->SendFreqSerial(m_Voltage,m_Frequency)){
                emit error_("Error Send AC(2)");
            }


        }

        emit EndProcess();


    } else{
        emit error_("Error_ V or Num or F = 0");
    }


}







void algoritm::freqVerification()
{
    qDebug()<<"freqVerification";
}

void algoritm::setOperatioNumber(const uint Num)
{
    m_OperationNumber = Num;
    qDebug()<< "Operating: "<<m_OperationNumber;
    //this->SelectProcess();
}

void algoritm::setPoint(const DeviceCom * Cal, const DeviceCom * Voltmeter )
{
    m_Calibrator = const_cast<DeviceCom *>(Cal);
    m_Voltmeter = const_cast<DeviceCom *>(Voltmeter);
}

void algoritm::slotSaveDataDevice(bool typeDev, bool typeRefDev, float V)
{
    //TypeDev,TypeRefDev,Volt
    m_TypeDev = typeDev;
    m_TypeRefDev = typeRefDev;
    m_Voltage = V;

}

void algoritm::setNumberCycles(uint Num)
{
    m_NumberCycles = Num;
    qDebug()<< "Number: "<<m_NumberCycles;
}

void algoritm::StartWork()
{
    if(m_OperationNumber != 0){
    this->SelectProcess();
    }
}
