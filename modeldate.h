#ifndef MODELDATE_H
#define MODELDATE_H
#include <QString>
#include <QDebug>

class ModelDate
{
public:
    ModelDate();

    void setTemp(qint32);
    void setName(QString);
    void setModel(QString);
    void setNumber(QString);
    void setTypeDev(bool);
    void setTypeRefDev(bool);
    void setVolt(quint32);

private:

    //Исходные данные
    quint32 m_temp; //температура
    QString m_fullname;//ФИО поверитель
    QString m_model;//модель поверяемого прибора
    QString m_number;//заводской номер
    bool m_typedev;//тип поверяемого прибора false - c лин. функ. преобразования
    bool m_typerefdev;//тип эталонного прибора false - c лин. функ. преобразования
    quint32 m_voltage;//номинальное напряжение


};

#endif // MODELDATE_H
