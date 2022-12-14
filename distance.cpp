
#include "distance.h"


/*Calculating 3 different distances. the Euclidean and Minkowski use the same
formula when p = 2, so it's the same in this excersice.
for p = 1 we have special condition, but it's almost the same.*/
double distanceByP(vector<double> v1, vector<double> v2, double p)
{
    double distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        //for Manhattan distance that requires absolute value.
        if (p == 1)
        {
            distance += abs(v1.at(i) - v2.at(i));
        }
        else{
            distance += pow((v1.at(i) - v2.at(i)), p);
        }
    }
    distance = pow(distance, 1 / p);
    return distance;
}
/*Calculating the distance by canbrra formula. then print the result*/
double canberraDistance(vector<double> v1, vector<double> v2)
{
    double distance = 0;
    //Summing up according to the formula at Wikipedia.
    for (int i = 0; i < v1.size(); i++)
    {
        distance += (abs(v1.at(i) - v2.at(i))) / (abs(v1.at(i)) + abs(v2.at(i)));
    }
    return distance;
}
/*Calculating the distance by chebyshkev formula. then print the result*/
double chebyshevDistance(vector<double> v1, vector<double> v2)
{
    double distance = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        //Looking for the largest difference between 2 values in the vectors.
        if (distance <= abs(v1.at(i) - v2.at(i)))
        {
            distance = abs(v1.at(i) - v2.at(i));
        }
    }
    return distance;
}
