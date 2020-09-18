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

void ModelDate::setTemp(double temp)
{
    m_temp = temp;
    qDebug()<<m_temp;
}

void ModelDate::setName(QString name)
{
    m_fullname = name;
    qDebug()<<m_fullname;
}

void ModelDate::setModel(QString model)
{
    m_model = model;
    qDebug()<<m_model;
}

void ModelDate::setNumber(QString Num)
{
    m_number = Num;
    qDebug()<<m_number;
}

void ModelDate::setTypeDev(bool type)
{
    m_typedev = type;
    qDebug()<<m_typedev;
}

void ModelDate::setTypeRefDev(bool type)
{
    m_typerefdev = type;
    qDebug()<<m_typerefdev;
}

void ModelDate::setVolt(double Volt)
{
    m_voltage = Volt;
    qDebug()<<m_voltage;
}

double ModelDate::getTemp()
{
    return m_temp;
}

QString ModelDate::getName()
{
    return m_fullname;
}

QString ModelDate::getModel()
{
    return m_model;
}

QString ModelDate::getNumber()
{
    return m_number;
}

bool ModelDate::getTypeDev()
{
    return m_typedev;
}

bool ModelDate::getTypeRefDev()
{
    return m_typerefdev;
}

double ModelDate::getVolt()
{
    return m_voltage;

}
