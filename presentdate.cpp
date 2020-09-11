#include "presentdate.h"

PresentDate::PresentDate(QObject *parent):
     QObject(parent)//,
     //m_model(new ModelDate)
{

}

PresentDate::~PresentDate()
{
    delete m_model;
}

void PresentDate::setDate(quint32 temp, QString name, QString model, QString num, bool sqdev, bool srefdev, quint32 volt)
{
    m_model->setTemp(temp);
    m_model->setName(name);
    m_model->setModel(model);
    m_model->setNumber(num);
    m_model->setTypeDev(sqdev);
    m_model->setTypeRefDev(srefdev);
    m_model->setVolt(volt);
}
