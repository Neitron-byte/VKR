#include "presentdate.h"
#include <QMessageBox>

bool PresentDate::CheckDate()
{
    if(m_model->getTemp()>0 && m_model->getTemp()<=100 && m_model->getName()!="" && m_model->getModel()!="" && m_model->getNumber() != "" && m_model->getVolt()>0 && m_model->getVolt()<=100){
        return true;
    } else{
        return false;
    }
}

PresentDate::PresentDate(QObject *parent) :
    QObject(parent),
    m_model(new ModelDate)
{

}

PresentDate::~PresentDate()
{
    delete m_model;
}

void PresentDate::setDate(quint32 temp, QString name, QString model, QString num, bool sqdev, bool srefdev, quint32 volt)
{
    if(temp <= 0 || temp>=100){
        QMessageBox::information (0, "Information", "Please enter the correct current temperature.");
        m_model->setTemp(0);
    }
    else{
        m_model->setTemp(temp);
    }

    if(name == "" ){
        QMessageBox::information (0, "Information", "Please enter the full name of the verifier.");
        m_model->setName("");
    }
    else{
    m_model->setName(name);
    }

    if(model == "" ){
        QMessageBox::information (0, "Information", "Please enter model devices.");
        m_model->setModel("");
    }
    else{
    m_model->setModel(model);
    }

    if(num == "" ){
        QMessageBox::information (0, "Information", "Please enter number devices.");
        m_model->setNumber("");
    }
    else{
    m_model->setNumber(num);
    }

    m_model->setTypeDev(sqdev);
    m_model->setTypeRefDev(srefdev);

    if(volt <= 0 || volt>=100){
        int n = QMessageBox::information (0, "Information", "Please enter the correct voltage.");
        m_model->setVolt(0);
    }
    else{
        m_model->setVolt(volt);
    }


    if(CheckDate()){
        emit signalInLog("The data was successfully stored");
        emit signalsLockStart();
        emit signalNextAction();

    }

}
