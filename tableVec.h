//
// Created by adar on 12/13/22.
//

#ifndef _ADVANCEDPROGPROJECT_TABLEVEC_H
#define _ADVANCEDPROGPROJECT_TABLEVEC_H

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
public:
    tableVec(::vector<double> vector, string type);
    void calcDis(::vector<double> vector, distanceType distanceType);
    vector<double> getVector ();
    string getType();
    double getDistance();
    void setDistance(double distance);
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
