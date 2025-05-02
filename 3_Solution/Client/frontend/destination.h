#ifndef DESTINATION_H
#define DESTINATION_H

#include <QString>

class Destination
{
private:
    int _id;
    QString _name,
        _country,
        _city,
        _description,
        _climate;
    bool _isActive;

public:
    Destination(int _id,QString _name,QString _country,QString _city,
                QString _description,QString _climate,bool _isActive
                );

    int getid() const { return _id; }
    QString getname() const { return _name; }
    QString getcountry() const { return _country; }
    QString getcity() const { return _city; }
    QString getdescription() const { return _description; }
    QString getclimate() const { return _climate; }
    bool getisActive() const { return _isActive; }
};

#endif // DESTINATION_H
