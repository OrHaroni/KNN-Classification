#ifndef _ADVANCEDPROGPROJECT_TABLEVEC_H
#define _ADVANCEDPROGPROJECT_TABLEVEC_H

#include "distance.h"
#include "Command.h"
#include "Commands.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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
    void setDistance(double distance);
    string m_type;
public:
    tableVec(vector<double> vector, string type);
    void calcDis(vector<double> vector, distanceType distanceType);
    vector<double> getVector ();
    string getType();
    double getDistance();
    string to_string();
    void setStringTypeSign(const std::string&);
};


#endif //ADVANCEDPROGPROJECT_TABLEVEC_H
