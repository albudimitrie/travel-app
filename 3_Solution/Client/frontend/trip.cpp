#include "trip.h"

Trip::Trip(QVector<int>idAcc,QVector<int>idAtt,QVector<int>idRou,int TripId,QString StartDate,QString EndDate,int duration,bool isConfirmed,double totalCost)
{
    this->TripId=TripId;
    this->StartDate=StartDate;
    this->EndDate=EndDate;
    this->duration=duration;
    this->isConfirmed=isConfirmed;
    this->totalCost=totalCost;
    this->idAcc = idAcc;
    this->idAtt = idAtt;
    this->idRou = idRou;

}
