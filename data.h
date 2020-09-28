#ifndef DATA_H
#define DATA_H

#include <QObject>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr): QObject(parent){
        m_Temp = 0;
        m_FullName = "";
        m_Model = "";
        m_Number = "";
    }

signals:

public slots:

    void SetData(const float, const QString , const QString ,const QString );


private:

    //данные введенные с GUI
    float m_Temp;
    QString m_FullName;
    QString m_Model;
    QString m_Number;

    //


};

#endif // DATA_H
