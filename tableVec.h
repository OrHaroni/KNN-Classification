#ifndef _ADVANCEDPROGPROJECT_TABLEVEC_H
#define _ADVANCEDPROGPROJECT_TABLEVEC_H

#include "distance.h"
#include "Command.h"
#include "Commands.h"
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
    string m_type;
    void setDistance(double distance);
public:
    tableVec(vector<double> vector, string type);
    void calcDis(vector<double> vector, distanceType distanceType);
    vector<double> getVector ();
    string getType();
    double getDistance();
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
