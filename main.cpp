#include <iostream>
#include <vector>
#include<math.h>
using namespace std;


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

   


return 0;

}

namespace distance{




}