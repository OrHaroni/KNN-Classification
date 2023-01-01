# Advanced Program Project 

***WE HAVE ACCIDENTELY OVERWRITTEN THIS BRANCH WHILE WORKING ON EX3. WE ONLY ADDED CLASSES(SERVER AND CLIENT) AND DIDNT TOUCH THE PREVIUS CLASSES AND FILES.
AFTER MAILING YOAV, WE ARE ADDING LINK TO THE LAST COMMIT OF EX2: https://github.com/OrHaroni/AdvancedProgProject/tree/c58898bf8e87ee46adc9995c00df9fef47cd807c
THANK YOU FOR YOUR CONSIDERATION***

The program expects the user to input a vector on standard input. The input should be a sequence of numbers separated by whitespace, with no leading or trailing whitespace.

The program includes several functions and templates to support its functionality:

printVector: a template function that takes in a vector of any type and outputs the elements in the vector, separated by whitespace
numberOfValues: a function that takes in a vector of tableVec objects and returns the number of values each tableVec object has
numberOfCalculation: a function that takes in a string and returns an enum value representing the type of distance calculation to perform
turnLineIntoVector: a function that takes in a string and returns a vector of strings, with each element of the vector being a substring of the input string separated by the comma (,) character
compareDistance: a function that takes in two tableVec objects and returns a boolean value indicating whether the distance of the first tableVec is less than the distance of the second tableVec. This function is used as a comparison function for the sort function.
main: the main function of the program, which reads in the vectors from the file, receives the vector from the user, calculates the distances between the two sets of vectors, sorts the vectors by distance, and outputs the smallest k distances.


## Authors
Or Haroni\
Adar Katz


## Environment Variables

To run this project, you will need to add the following environment variables to your file

`k: an integer representing the number of smallest distances to output`

`filename: the path to the file containing the vectors to compare against`

`distance_type: a string indicating the type of distance calculation to perform`

## FAQ

#### How to run the program?
Enter via terminal to the folder where the project in saved.

Write make

Enter ./a.out and then the 3 Environment variables listed above to the command line.

#### What did you learned from this project?

We learned more about mechine lerning and c++ OOP.

#### What template methods did you use?

We used the Iterator template method.

#### With which data structures and algorithms did you work?

We worked with vectors, map and we did the "KNN" algorithm.


![istockphoto-1142790620-1024x1024](https://user-images.githubusercontent.com/110082803/207814972-ad2f2cb6-211b-40f5-8404-9ce25cf5e7c1.jpg)
