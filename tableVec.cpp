/*The tableVec is an object that represent a single vector from the data
 * from the exel file, it has the vector, its distance from the input and its type.
 */
#include "tableVec.h"
#include "distance.h"
//Constructor to the tableVec
tableVec::tableVec(vector<double> vector, string type):m_vector(vector),m_type(type),m_distance(0) {}

vector<double> tableVec:: getVector (){
    return m_vector;
}
string tableVec::getType(){
    return m_type;
}
double tableVec::getDistance(){
    return m_distance;
}
void tableVec::setDistance(double distance){
    m_distance = distance;
}
//Calculate the distance from a vector with a certain distance formula.
void tableVec::calcDis(vector<double> vector, distanceType distanceType){
    double distance = 0;
    switch (distanceType) {
        case AUC:
            distance = distanceByP(this->getVector(), vector, 2);
            break;
        case MAN:
            distance = distanceByP(this->getVector(), vector, 1);
            break;
        case CHB:
            distance = chebyshevDistance(this->getVector(), vector);
            break;
        case CAN:
            distance = canberraDistance(this->getVector(), vector);
            break;
        case MIN:
            distance = distanceByP(this->getVector(), vector, 2);
            break;
        default:
            break;
    }
    //Enter the distance to the vector's data.
    this->setDistance(distance);
}


