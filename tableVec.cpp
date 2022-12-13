//
// Created by adar on 12/13/22.
//

#include "tableVec.h"
#include "distance.h"

tableVec::tableVec(::vector<double> vector , string type){
m_vector = vector;
m_distance = 0;
m_type = type;
}
void tableVec::calcDis(::vector<double> vector, distanceType distanceType){
    switch (distanceType) {
        case AUC:
            //
            break;
        case MAN:
            //
            break;
        case CHB:
            //
            break;
        case CAN:
            //
            break;
        case MIN:
            //
            break;
        default:
            break;
    }

}


