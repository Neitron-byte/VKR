#include "data.h"
#include <QDebug>


void Data::SetData(const float Temp, const QString name , const QString mod, const QString num)
{
    m_Temp = Temp;
    m_FullName = name;
    m_Model = mod;
    m_Number = num;
    qDebug()<<"Save data";
}
