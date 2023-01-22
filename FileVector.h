#ifndef CLIONPROJECTS_FILEVECTOR_H
#define CLIONPROJECTS_FILEVECTOR_H
#include "tableVec.h"
#include "Server.h"

class FileVector {
private:
    vector<tableVec> vectors;
    enum distanceType distanceType;
    int k;
    bool isEmpty;

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
    void InitializeByReadingFileNoType(string path);
    vector<double> manipulateMSG(char*) throw();
    enum distanceType getDistanceType();
    int getK();
    void setK(int k);
    void setDistanceType(enum distanceType);
    bool isFileEmpty();
    void upload_complete();

};


#endif //CLIONPROJECTS_FILEVECTOR_H
