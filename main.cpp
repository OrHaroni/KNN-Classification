#include <iostream>
#include <vector>
#include "distance.h"

using namespace std;
#define FOUR 4
template <typename T>
void printVector(vector<T>);
/*The main function that will
send the verctors to calculate.*/

int main()
{

    double input;
    vector<double> v1;
        try {
            // getting v1
            do
            {
                if (std::cin >> input)
                {
                    v1.push_back(input);
                }
            } while (std::cin && std::cin.peek() != '\n');

            if (cin.peek() != '\n') {
                throw invalid_argument("Received invalid input.");
            }
            if (v1.size() != FOUR) {
                throw invalid_argument("Invalid length of the vector.");
            }
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return (1);
        }

        printVector(v1);


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
