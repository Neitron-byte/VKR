#include "modeldate.h"


ModelDate::ModelDate():
    m_temp(0),
    m_fullname(""),
    m_model(""),
    m_number(""),
    m_typedev(false),
    m_typerefdev(false),
    m_voltage(0)
{

}

void ModelDate::setTemp(qint32 temp)
{
    m_temp = temp;
    qDebug()<<m_temp;
}

void ModelDate::setName(QString name)
{
    m_fullname = name;
}

void ModelDate::setModel(QString model)
{
    m_model = model;
}

void ModelDate::setNumber(QString Num)
{
    m_number = Num;
}

void ModelDate::setTypeDev(bool type)
{
    m_typedev = type;
}

void ModelDate::setTypeRefDev(bool type)
{
    m_typerefdev = type;
}

void ModelDate::setVolt(quint32 Volt)
{
    m_voltage = Volt;
}
