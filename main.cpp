#include <iostream>
#include <vector>
#include <cmath>
#include "distance.h"
using namespace std;

template <typename T>
void printVector(vector<T>);
/*The main function that will
sent the verctors to calculate.*/
int main()
{
    vector<double> v1;
    vector<double> v2;
    // adding 5 digits after the floating point
    cout.precision(17);
    try
    {
        // geting v1
        do
        {
            double input;
            if (std::cin >> input)
            {
                v1.push_back(input);
            }
        } while (std::cin && std::cin.peek() != '\n');
        // If we are out of the loop but cin is not empty, we had problem
        // that means we have char or invalid input in cin
        if (cin.peek() != '\n')
        {
            throw invalid_argument("Received invalid input");
        }
        // geting v2
        do
        {
            double input;
            if (std::cin >> input)
            {
                v2.push_back(input);
            }
        } while (std::cin && std::cin.peek() != '\n');
        // If we are out of the loop but cin is not empty, we had problem
        // that means we have char or invalid input in cin
        if (cin.peek() != '\n')
        {
            throw invalid_argument("Received invalid input");
        }
        // Exit the program if the lengthes are not equal
        if (v1.size() != v2.size())
        {
            cout << "Invalid length of the vectors. not the same length" << endl;
            return 0;
        }
    }
    catch (invalid_argument e)
    {
        cout << e.what() << endl;
        return (1);
    }
    // Euclidean distance
    distanceByP(v1, v2, 2);

    // Manhattan distance
    distanceByP(v1, v2, 1);

    // Chebyshev distance
    chebyshevDistance(v1, v2);

    // Canberra distance
    canberraDistance(v1, v2);

    // Minkowski distance
    distanceByP(v1, v2, 2);

    return 0;
}

// Func for testing
template <typename T>
void printVector(vector<T> v1)
{
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1.at(i) << " ";
    }
    cout << endl;
}
