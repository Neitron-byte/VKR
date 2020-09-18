#ifndef MODELDATE_H
#define MODELDATE_H
#include <QString>
#include <QDebug>

class ModelDate
{
public:
    ModelDate();

    void setTemp(double);
    void setName(QString);
    void setModel(QString);
    void setNumber(QString);
    void setTypeDev(bool);
    void setTypeRefDev(bool);
    void setVolt(double);

    double getTemp();
    QString getName();
    QString getModel();
    QString getNumber();
    bool getTypeDev();
    bool getTypeRefDev();
    double getVolt();


private:

    //Исходные данные
    double m_temp; //температура
    QString m_fullname;//ФИО поверитель
    QString m_model;//модель поверяемого преобразователя
    QString m_number;//заводской номер
    bool m_typedev;//тип поверяемого преобразователя false - c лин. функ. преобразования
    bool m_typerefdev;//тип эталонного преобразователя false - c лин. функ. преобразования
    double m_voltage;//номинальное напряжение

};

#endif // MODELDATE_H
