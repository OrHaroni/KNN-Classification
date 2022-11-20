#include <iostream>
#include <vector>
#include <cmath>
#include "distance.h"
using namespace std;
using namespace distance;

int main(){

    vector<float> v1;
    vector<float> v2;
    cout.precision(4);
    //geting v1
do
    {
        float input ;
        if ( std::cin >> input )
            v1.push_back(input) ;
    } while ( std::cin && std::cin.peek() != '\n' ) ;
    //geting v2
    do
    {
        float input ;
        if ( std::cin >> input )
            v2.push_back(input) ;
    } while ( std::cin && std::cin.peek() != '\n' );
   if(v1.size() != v2.size()){
    cout << "Invalid length of the vectors. not the same length" << endl;
    return 0;
   }
   distanceByP(v1,v2,2);
   distanceByP(v1,v2,1);
   //Chebishev disrtance
   //canbera distance
   distanceByP(v1,v2,2);

return 0;

}

