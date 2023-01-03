#ifndef _ADVANCEDPROGPROJECT_TABLEVEC_H
#define _ADVANCEDPROGPROJECT_TABLEVEC_H
#include "distance.h"
#include <iostream>
#include <vector>

using namespace std;
enum distanceType{
    AUC = 1,
    MAN,
    CHB,
    CAN,
    MIN,
};
class tableVec {
private:
    vector <double>m_vector;
    double m_distance;
    distanceType m_type;
    void setDistance(double distance);
public:
    tableVec(vector<double> vector, distanceType type);
    void calcDis(vector<double> vector, distanceType distanceType);
    vector<double> getVector ();
    distanceType getType();
    double getDistance();
    string getTypeString() throw();
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
