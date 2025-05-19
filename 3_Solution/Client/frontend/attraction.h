#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <QString>

class Destination;

class Attraction
{
private:
    Destination* _destination;
    QString _name,
            _description,
            _category;
    double _ticketPrice;
    int _id;
    QString base64photo;
public:
    Attraction(Destination*dest, QString name, QString description, QString category, double ticketPrice, int id);

    int id() const { return _id; }
    QString name() const { return _name; }
    QString description() const { return _description; }
    double ticketPrice() const { return _ticketPrice; }
    QString category() const { return _category; }

    Destination* destination() const { return _destination; }
    QString base64Photo() const { return base64photo; }
    void setBase64Photo(QString data) { base64photo = data;}
    ~Attraction()
    {
        delete _destination;

    }
};

#endif // ATTRACTION_H
