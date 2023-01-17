#ifndef CLIONPROJECTS_FILEVECTOR_H
#define CLIONPROJECTS_FILEVECTOR_H
#include "tableVec.h"
#include "Server.h"

class FileVector {
private:
    vector<tableVec> vectors;
    enum distanceType distanceType;
    int k;

public:
    //C'tor
    FileVector();
    //Copy C'tor
    FileVector(const vector<tableVec> *cpy);
    void Add(tableVec tableVector);
    string CalcTypeName(int k, vector<double> vec, enum distanceType disType);
    vector<tableVec> getVectors();
    int SizeOfVectors();
    void InitializeByReadingFile(string path);
    vector<double> manipulateMSG(char*) throw();
    enum distanceType getDistanceType();
    int getK();
};


#endif //CLIONPROJECTS_FILEVECTOR_H