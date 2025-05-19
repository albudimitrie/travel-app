#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QVector>
class Trip
{
private:
    int TripId;
    QString StartDate,EndDate;
    int duration;
    bool isConfirmed;
    double totalCost;
    QVector <int> idAcc;
    QVector <int> idAtt;
    QVector <int> idRou;
    bool isAdded = 0;

public:
    Trip(QVector<int>idAcc,QVector<int>idAtt,QVector<int>idRou,int TripId,QString StartDate,
         QString EndDate,int duration,bool isConfirmed,double totalCost);

    int getTripId() const { return TripId; }
    QString getStartDate() const { return StartDate; }
    QString getEndDate() const { return EndDate; }
    int getDuration() const { return duration; }
    bool getIsConfirmed() const { return isConfirmed; }
    double getTotalCost() const { return totalCost; }
    QVector<int> getIdAcc() const { return idAcc; }
    QVector<int> getIdAtt() const { return idAtt; }
    QVector<int> getIdRou() const { return idRou; }
    bool getIsAdded() const { return isAdded; }

    // Setters
    void setTripId(int tripId) { TripId = tripId; }
    void setStartDate(const QString& startDate) { StartDate = startDate; }
    void setEndDate(const QString& endDate) { EndDate = endDate; }
    void setDuration(int d) { duration = d; }
    void setIsConfirmed(bool confirmed) { isConfirmed = confirmed; }
    void setTotalCost(double cost) { totalCost = cost; }
    void setIdAcc(const QVector<int>& acc) { idAcc = acc; }
    void setIdAtt(const QVector<int>& att) { idAtt = att; }
    void setIdRou(const QVector<int>& rou) { idRou = rou; }
    void setIsAdded(bool added) { isAdded =added; }

    // Methods to add elements to vectors
    void addAcc(int id) { idAcc.push_back(id); }
    void addAtt(int id) { idAtt.push_back(id); }
    void addRou(int id) { idRou.push_back(id); }
};

#endif // TRIP_H
