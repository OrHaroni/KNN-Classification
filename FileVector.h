#ifndef CLIONPROJECTS_FILEVECTOR_H
#define CLIONPROJECTS_FILEVECTOR_H
#include "tableVec.h"
#include "Server.h"

class FileVector {
private:
    vector<tableVec> vectors;

public:
    //C'tor
    FileVector();
    //Copy C'tor
    FileVector(const vector<tableVec> *cpy);
    void Add(tableVec tableVector);
    string CalcTypeName(int k, vector<double> vec, distanceType disType);
    vector<tableVec> getVectors();
    int SizeOfVectors();

};


#endif //CLIONPROJECTS_FILEVECTOR_H
