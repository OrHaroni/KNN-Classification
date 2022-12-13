//
// Created by adar on 12/13/22.
//

#ifndef ADVANCEDPROGPROJECT_TABLEVEC_H
#define ADVANCEDPROGPROJECT_TABLEVEC_H
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
    int m_distance;
    string m_type;
public:
    tableVec(::vector<double> vector, string type);
    void calcDis(::vector<double> vector, distanceType distanceType);
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
