//
// Created by adar on 12/13/22.
//

#ifndef ADVANCEDPROGPROJECT_TABLEVEC_H
#define ADVANCEDPROGPROJECT_TABLEVEC_H
#include "distance.h"
#include <iostream>
#include <vector>
using namespace std;
class tableVec {
private:
    vector <double>m_vector;
    int m_distance;
    string m_type;
public:
    tableVec(::vector<double> vector, string type);
    void calcDis(::vector<double> vector, string distanceName);
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
