#include "FileVector.h"


FileVector::FileVector() {}

FileVector::FileVector(const vector<tableVec> *cpy) {
    for (int i = 0; i < cpy->size(); ++i) {
        this->vectors.push_back(cpy->at(i));
    }
}

void FileVector::Add(tableVec tableVector) {
    this->vectors.push_back(tableVector);
}

string FileVector::CalcTypeName(int k, vector<double> vec, distanceType disType) {
    if(k < 1){
        throw invalid_argument("k cannot be lower than 1");
    }
    //cant be with k greater than the number of the vectors.
    if(k > this->vectors.size()){
        k = this->vectors.size();
    }
    FileVector *temp = this;
    //Calculating all the distances from v1 for all the vectors in fileVectors
    for (int i = 0; i < temp->vectors.size(); ++i) {
        temp->vectors.at(i).calcDis(vec, disType);
    }

    //sorting the vector
    sort(temp->vectors.begin(), temp->vectors.end(), compareDistance);

    map<string, int> neighbours;
    for (int i = 0; i < k; ++i) {
        addToMap(neighbours, temp->vectors.at(i));
    }

    //Checking the largest value of the map.
    //Its the repeated type.
    int maxType = 0;
    string maxTypeName = temp->vectors.at(0).getType();
    for (int i = 0; i < neighbours.size(); ++i) {
        if (maxType < neighbours.at(temp->vectors.at(i).getType())) {
            maxType = neighbours.at(temp->vectors.at(i).getType());
            maxTypeName = temp->vectors.at(i).getType();
        }
    }
    return maxTypeName;
}

vector<tableVec> FileVector::getVectors() {
    return this->vectors;
}

int FileVector::SizeOfVectors() {
    int size  = this->vectors.at(0).getVector().size();
    for (int i = 1; i < this->vectors.size(); ++i) {
        if(size != this->vectors.at(0).getVector().size())
        {//so the file is not valid
            throw invalid_argument("The file has vectors with different lengths");
        }
    }
    return size;
}