#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include<QString>

class Transportation
{
private:
    int _id;
    QString _type,
            _company,
            _description,
            _comfort_level;
    int    _capacity;
    double _averagePricePerTrip;
    QString base64photo;
public:
    Transportation(int id, QString type, QString company, QString description, QString comfort_level ,
                   int capacity, double averagePricePerTrip );
    int getId() const {return _id;}
    QString getType() const {return _type;}
    QString getCompany() const {return _company;}
    QString getDescription() const {return _description;}
    QString getComfortLevel() const {return _comfort_level;}
    int getCapacity() const {return _capacity;}
    double getAveragePricePerTrip() const {return _averagePricePerTrip;}
    QString base64Photo() const { return base64photo; }
    void setBase64Photo(QString data) { base64photo = data;}

};

#endif // TRANSPORTATION_H
