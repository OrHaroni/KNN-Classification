#include "distance.h"


/*Calculating 3 different distances. the Euclidean and Minkowski use the same
formula when p = 2 so its the same in this excersice.
for p = 1 we have special condition but its almost the same.*/
void distanceByP(vector<double> v1, vector<double> v2, double p)
{
    double distance = 0;
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
    //If its a whole number, print with .0
    if(distance == (int)distance){
        cout << distance << ".0" <<endl;
        return;
    }
    cout << distance << endl;
}
/*Calculating the distance by canbrra furmula. then print the result*/
void canberraDistance(vector<double> v1, vector<double> v2)
{
    double distance = 0;
    //Summing up according to the formula at Wikipedia.
    for (int i = 0; i < v1.size(); i++)
    {
        distance += (abs(v1.at(i) - v2.at(i))) / (abs(v1.at(i)) + abs(v2.at(i)));
    }
    //If its a whole number, print with .0
    if(distance == (int)distance){
        cout << distance << ".0" <<endl;
        return;
    }
    cout << distance << endl;
}
/*Calculating the distance by canbrra furmula. then print the result*/
void chebyshevDistance(vector<double> v1, vector<double> v2)
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
    //If its a whole number, print with .0
    if(distance == (int)distance){
        cout << distance << ".0" <<endl;
        return;
    }
    cout << distance << endl;
}