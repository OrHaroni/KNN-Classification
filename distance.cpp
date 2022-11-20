#include "distance.h"
using namespace std;

void distanceByP(vector <float> v1, vector<float> v2, int p){
    float distance = 0;
for(int i = 0; i< v1.size();i++){
        distance += pow((v1.at(i) - v2.at(i)), p);
    }
    distance = pow(distance, 1/p);
    cout << "the Euclidean distance is: " << distance << endl;
}