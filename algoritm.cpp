#include "algoritm.h"
#include "QThread"
#include "QInputDialog"

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

        float Summ = 0;

        for (int var = 0; var < m_NumberCycles; ++var) {
            qDebug() << "Thread algoritm" << this->thread();
            uint Count = 0;
//Команда на подачу пер напр V частотой F-1кГц
            if(Cal->SendFreqSerial(m_Voltage,m_Frequency)){
                emit error_("Error Send AC");
            }

            //Получение показаний с вольтметра 1 канал
            QString Response = Voltmeter->Measurement(1);

            //проверка что пришло
            if(this->checkResponse(Response)){

                m_ArrayForCH1[Count] = Response.toFloat();
            }


           //Получение показаний с вольтметра 2 канал
            Response = Voltmeter->Measurement(2);

            //проверка
            if(this->checkResponse(Response)){

                m_ArrayForCH2[Count] = Response.toFloat();
            }

            Count++;
 //Команда на подачу пост напр номиналом V
            if (Cal->SendSerial(m_Voltage)){
                emit error_("Error Send DC");
            }

     //Получение показаний с вольтметра 1 канал
            Response = Voltmeter->Measurement(1);

         //проверка что пришло
            if(this->checkResponse(Response)){

                m_ArrayForCH1[Count] = Response.toFloat();
            }


    //Получение показаний с вольтметра 2 канал
            Response=Voltmeter->Measurement(2);

        //проверка
            if(this->checkResponse(Response)){

                m_ArrayForCH2[Count] = Response.toFloat();
            }

            Count++;


//Команда на подачу пост напр номиналом V  отр полярности
            if (Cal->SendSerial(-m_Voltage)){
                emit error_("Error Send Neg DC");
            }

            //Получение показаний с вольтметра 1 канал
            Response = Voltmeter->Measurement(1);

            //проверка что пришло
            if(this->checkResponse(Response)){

                m_ArrayForCH1[Count] = Response.toFloat();
            }


           //Получение показаний с вольтметра 2 канал
            Response=Voltmeter->Measurement(2);

            //проверка
            if(this->checkResponse(Response)){

                m_ArrayForCH2[Count] = Response.toFloat();
            }

            Count++;


//Команда на подачу пер напр V частотой F-1кГц
            if(Cal->SendFreqSerial(m_Voltage,m_Frequency)){
                emit error_("Error Send AC(2)");
            }

            //Получение показаний с вольтметра 1 канал
            Response = Voltmeter->Measurement(1);

            //проверка что пришло
            if(this->checkResponse(Response)){

                m_ArrayForCH1[Count] = Response.toFloat();
            }


           //Получение показаний с вольтметра 2 канал
            Response=Voltmeter->Measurement(2);

            //проверка
            if(this->checkResponse(Response)){

                m_ArrayForCH2[Count] = Response.toFloat();
            }

            Count++;

            auto Rez = this->calculate();

            Summ+=Rez;

        }

        //this->InputCorrect();

        auto Rezult = Summ/m_NumberCycles + m_CorrectRef;


        emit EndProcess();


    } else{
        emit error_("Error_ V or Num or F = 0");
    }


}







void algoritm::freqVerification()
{
    qDebug()<<"freqVerification";





    emit EndProcess();
}

bool algoritm::checkResponse(const QString & Resp)
{
    if(Resp != QString("error")){

        return true;

    } else {

        emit error_("Error receiving data from Voltmeter");
        return false;
    }
}

float algoritm::calculate()
{
    //рассчет погрешности для эталона
    float averageRefDC = (m_ArrayForCH1[2] + m_ArrayForCH1[3])/2;
    float averageRefAC = (m_ArrayForCH1[1] + m_ArrayForCH1[4])/2;
    float deltaRef = (averageRefAC - averageRefDC)/ (m_TypeRefDev * averageRefDC);

    //рассчет погрешности для поверяемого прибора

    float averageDC = (m_ArrayForCH2[2] + m_ArrayForCH2[3])/2;
    float averageAC = (m_ArrayForCH2[1] + m_ArrayForCH2[4])/2;
    float deltaVer = (averageAC - averageDC)/ (m_TypeDev * averageDC);

    //разность погрешностей

    emit InputCorrect();

    float RezultDelta = deltaVer - deltaRef;

    return RezultDelta;
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

void algoritm::slotSaveDataDevice(uint typeDev, uint typeRefDev, float V)
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
