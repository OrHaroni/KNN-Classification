This is a C++ program that calculates the distance between a given vector and the vectors in a provided file, and outputs the K smallest distances.

The program takes in 3 command line arguments:

1)k: an integer representing the number of smallest distances to output
2)filename: the path to the file containing the vectors to compare against
3)distance_type: a string indicating the type of distance calculation to perform (either "manhattan" or "euclidean")
The program expects the user to input a vector on standard input. The input should be a sequence of numbers separated by whitespace, with no leading or trailing whitespace.

The program includes several functions and templates to support its functionality:

printVector: a template function that takes in a vector of any type and outputs the elements in the vector, separated by whitespace
numberOfValues: a function that takes in a vector of tableVec objects and returns the number of values each tableVec object has
numberOfCalculation: a function that takes in a string and returns an enum value representing the type of distance calculation to perform
turnLineIntoVector: a function that takes in a string and returns a vector of strings, with each element of the vector being a substring of the input string separated by the comma (,) character
compareDistance: a function that takes in two tableVec objects and returns a boolean value indicating whether the distance of the first tableVec is less than the distance of the second tableVec. This function is used as a comparison function for the sort function.
main: the main function of the program, which reads in the vectors from the file, receives the vector from the user, calculates the distances between the two sets of vectors, sorts the vectors by distance, and outputs the smallest k distances.
