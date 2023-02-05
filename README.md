# Advanced Program Project Exercise #3

**THIS EX3 WAS OVERWRITTEN APPROVED BY EREL AND YOAV (MAILED THE COURSE E-MAIL).**

The next program is Server\Client based.
The client should connect to the server with ip number and port number, then send the server valid length vector, type of distance calculation and an integer.
The Server activates its KNN algorithem and send back to the client the type of vector.
It can go on and on until the client insert '-1' and disconnects.
The server will wait to the next Client and will never shut down (or until the terminal is terminated).

## Authors
Or Haroni\
Adar Katz


## Environment Variables

To run Server, you will need to write the next line: "server.out file port" where:

`file: the path to the file containing the vectors to calculate on.

'port': number of port.


To run Client, you will need to write the next line: "client.out ip port" where:

'ip': the ip number of the Server.

'port': number of port.

But first, you need to write make. 
The make file will make 2 object files.

## FAQ

#### How to run the program?
Write make to the command line, then write the line above (Server\Client).
Then, the client need to write "VECTOR DIS_TYPE K" where:
'VECTOR': valid length vector wich you want to know its type.
'DIS_TYPE': the type of calculation you want the server to work on.
'K': the number of neighbours to calculate on (indirectly the accuracy of the server)
the server will send back its answer, and goes on.


#### What did you learned from this project?

We learned more about mechine lerning and c++ OOP.
We learned how to communicate between computers via the net (and sockets ofcourse).
We learned how big systems with Clients and Server work to the dot.

#### What template methods did you use?

We used the Iterator template method.

#### With which data structures and algorithms did you work?

We worked with vectors, map and we did the "KNN" algorithm.
We worked with sockets and the connection to the net.


![istockphoto-1142790620-1024x1024](https://user-images.githubusercontent.com/110082803/207814972-ad2f2cb6-211b-40f5-8404-9ce25cf5e7c1.jpg)
