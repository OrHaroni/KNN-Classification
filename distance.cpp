#include "distance.h"

void distanceByP(vector<float> v1, vector<float> v2, float p)
{
    float distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        //for Manhattan distance that requires absoulute value.
        if (p == 1)
        {
            distance = abs(v1.at(i) - v2.at(i));
        }
        distance += pow((v1.at(i) - v2.at(i)), p);
    }
    distance = pow(distance, 1 / p);
    cout << distance << endl;
}

void canberraDistance(vector<float> v1, vector<float> v2)
{
    float distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        distance += (abs(v1.at(i) - v2.at(i))) / (abs(v1.at(i)) + abs(v2.at(i)));
    }
    cout << distance << endl;
}

void chebyshevDistance(vector<float> v1, vector<float> v2)
{
    float distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        if (distance <= abs(v1.at(i) - v2.at(i)))
        {
            distance = abs(v1.at(i) - v2.at(i));
        }
    }
    cout << distance << endl;
}