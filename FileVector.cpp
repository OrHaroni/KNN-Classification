#include "FileVector.h"


FileVector::FileVector() : distanceType(AUC), k(5), isEmpty(true) {}

FileVector::FileVector(const FileVector&  cpy) {
    for (int i = 0; i < cpy.vectors.size(); ++i) {
        this->vectors.push_back(cpy.vectors.at(i));
    }
}

void FileVector::Add(tableVec& tableVector) {
    this->vectors.push_back(tableVector);
    this->isEmpty = true;
}

string FileVector::CalcTypeName(int k, vector<double> vec, enum distanceType disType) {
    if (k < 1) {
        throw invalid_argument("k cannot be lower than 1");
    }
    //cant be with k greater than the number of the vectors.
    if (k > this->vectors.size()) {
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
    //It's the repeated type.
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
void FileVector::setName (string name, int i) {
    this->vectors[i].setStringTypeSign (name);
}

int FileVector::SizeOfVectors() {
    int size = this->vectors.at(0).getVector().size();
    for (int i = 1; i < this->vectors.size(); ++i) {
        if (size != this->vectors.at(0).getVector().size()) {//so the file is not valid
            throw invalid_argument("The file has vectors with different lengths");
        }
    }
    return size;
}

void FileVector::InitializeByReadingFile(string path) {
    fstream fin;
    string line, word, temp;
    vector<string> row;

    //open the file
    fin.open(path, ios_base::in);
    //Exiting if the file cant open.
    if (!fin.is_open()) {
        cout << "The program failed to open the file (invalid path)" << endl;
        throw invalid_argument("could not open the file");
    }
    //Reading the file.
    try {
        while (getline(fin, temp)) {
            //initialize empty vector
            row.clear();
            //separate the values in temp into row
            row = turnLineIntoVector(temp);
            vector<double> doubles;
            for (int i = 0; i < row.size() - 1; ++i) {
                doubles.push_back(stod(row.at(i)));
            }

            //Adding temp vector from row to fileVectors
            string typeOfVec;
            tableVec tempRow = tableVec(doubles, row.at(row.size() - 1));
            this->Add(tempRow);
        }
    }catch (invalid_argument e){
    throw invalid_argument("");}
    this->isEmpty = false;
}

vector<double> FileVector::manipulateMSG(char* msg) throw() {
    char temp[strlen(msg)];
    strcpy(temp, msg);
    vector<double> row;
    string word;
    stringstream s(temp);
    //keep on separating the line with Comma's
    //until its empty
    while (getline(s, word, ' ')) {
        if (s.eof()) {
            break;
        }
        try {
            // add all the column data
            // of a row to a vector
            row.push_back(stod(word));
        } catch (invalid_argument e) {
            //we got to letter
            return row; //might be invalid, will crash in numberOfCalculation.
        }
    }
    return row;
}

enum distanceType FileVector::getDistanceType() {
    return this->distanceType;
}

int FileVector::getK() {
    return this->k;
}
void FileVector::setK(int k){
    this->k = k;
}
void FileVector::setDistanceType(enum distanceType disType){
    this->distanceType = disType;
}
bool FileVector::isFileEmpty(){
    return this->isEmpty;
}

void FileVector::upload_complete(){
    this->isEmpty = false;
    cout << "Now we got data" << endl;
}

void FileVector::InitializeByReadingFileNoType(string path) {
    fstream fin;
    string line, word, temp;
    vector<string> row;

    //open the file
    fin.open(path, ios_base::in);
    //Exiting if the file cant open.
    if (!fin.is_open()) {
        cout << "The program failed to open the file (invalid path)" << endl;
        throw invalid_argument("could not open the file");
    }
    //Reading the file.
    try {
        while (getline(fin, temp)) {
            //initialize empty vector
            row.clear();
            //separate the values in temp into row
            row = turnLineIntoVector(temp);
            vector<double> doubles;
            for (int i = 0; i < row.size(); ++i) {
                doubles.push_back(stod(row.at(i)));
            }

            //Adding temp vector from row to fileVectors
            string typeOfVec;
            tableVec tempRow = tableVec(doubles, row.at(row.size() - 1));
            this->Add(tempRow);
        }
    }catch (invalid_argument e){
        throw invalid_argument("");}
    this->isEmpty = false;
}
