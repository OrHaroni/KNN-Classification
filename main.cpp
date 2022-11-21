#include <iostream>
#include <vector>
#include <cmath>
#include "distance.h"
using namespace std;

int main()
{

    vector<float> v1;
    vector<float> v2;
    cout.precision(6);
    // geting v1
    do
    {
        float input;
        if (std::cin >> input)
            v1.push_back(input);
    } while (std::cin && std::cin.peek() != '\n');
    // geting v2
    do
    {
        float input;
        if (std::cin >> input)
            v2.push_back(input);
    } while (std::cin && std::cin.peek() != '\n');
    //Exit the program if the lengthes are not equal
    if (v1.size() != v2.size())
    {
        cout << "Invalid length of the vectors. not the same length" << endl;
        return 0;
    }
    //Euclidean distance
    distanceByP(v1, v2, 2);

    //Manhattan distance
    distanceByP(v1, v2, 1);

    //Chebyshev distance
    chebyshevDistance(v1, v2);

    //Canberra distance
    canberraDistance(v1,v2);

    //Minkowski distance
    distanceByP(v1, v2, 2);

    return 0;
}
