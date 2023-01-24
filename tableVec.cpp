/*The tableVec is an object that represent a single vector from the data
 * from the exel file, it has the vector, its distance from the input and its type.
 */
#include <sstream>
#include "tableVec.h"

//Constructor to the tableVec
tableVec::tableVec(vector<double> vector, string type) : m_vector(vector), m_type(type), m_distance(0) {}


vector<double> tableVec::getVector() {
    return m_vector;
}

string tableVec::getType() {
    return m_type;
}

double tableVec::getDistance() {
    return m_distance;
}

void tableVec::setDistance(double distance) {
    m_distance = distance;
}

//Calculate the distance from a vector with a certain distance formula.
void tableVec::calcDis(vector<double> vector, distanceType distanceType) {
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

string tableVec::to_string() {
    //int size = m_vector.size();
    string name_of_vec;
    std::stringstream stream;
    for (int  j = 0; j < this->m_vector.size();j++) {
        stream << fixed << setprecision(2) << this->m_vector.at(j) << " ";
        //name_of_vec += " " + std::to_string(this->m_vector.at(j));
    }
    return stream.str();
}

void tableVec::setStringTypeSign(const std::string& name) {
    m_type = name;
}
