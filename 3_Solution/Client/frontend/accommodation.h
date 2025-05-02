#ifndef ACCOMMODATION_H
#define ACCOMMODATION_H

#include<QString>
class Destination;


class Accommodation
{
private:
    int _id;
    QString _name,
        _type,
        _address,
        _description,
        _facilities;
    int _pricePerNight;
    Destination* _destination;
    QString base64photo;
public:
    Accommodation(int _id,QString _name,QString _type,QString _address,QString _description,int _pricePerNight,QString _facilities,Destination*_destination);
    void setBase64Data(QString data);

    int id() const { return _id; }
    QString name() const { return _name; }
    QString type() const { return _type; }
    QString address() const { return _address; }
    QString description() const { return _description; }
    QString facilities() const { return _facilities; }
    int pricePerNight() const { return _pricePerNight; }
    Destination* destination() const { return _destination; }
    QString base64Photo() const { return base64photo; }
    void setBase64Photo(QString data) { base64photo = data;}
    ~Accommodation()
    {
        delete _destination;

    }
};

#endif // ACCOMMODATION_H
