# Advanced Program Project Exercise #4


The next program is multythreading Server\Client based.
The client connects to the server and gets a menu.
The client can upload data, manage the settings of the classification and than display or download the data.

## Authors
Or Haroni\
Adar Katz


## Environment Variables

To run Server, you will need to write the next line: "server.out port_number" where:

'port': number of port the server will run on.


To run Client, you will need to write the next line: "client.out ip port" where:

'ip': the ip number of the Server.

'port': number of port.

But first, you need to write make. 
The make file will make 2 object files.

## FAQ

#### How to run the program?
Write make to the command line, then write the line above (Server\Client).
The Client need to upload data, ajust the settings of the classification (or not, the default k=5 and distance AUC).
than the client ask the server to do the classification, display it and even download it to his own computer.

## What is the number K is larger than the max number of vectors in the train file?
The program will set K to be the max number of vectors in the train file.

##What will the program do, if one of the arguments given is not valid?
The program will prints error message and will shut down.
in any other event, the program will not shut down, just write a message and returns to the menu.

##How many clients can connect to the server parallely?
5 client can work with the server parallely.

#### What did you learned from this project?

We learned more about mechine lerning and c++ OOP.
We learned how to communicate between computers via the net (and sockets ofcourse).
We learned how big systems with Clients and Server work to the dot.
We learned how servers really works with multythreading programming.
In the end, in this whole project we learned how to use Github and work as a team of programers.

#### What template methods did you use?

We used the Iterator template method.
We used the Command template method.
We used Flyweight with funcions of adding, it just says "add" but the programmer does not
know the complexity behind the function.

#### With which data structures and algorithms did you work?

We worked with vectors, map and we did the "KNN" algorithm.
We worked with sockets and the connection to the net.
We worked with thread.

For further questions you can DM us or e-mail at or.haroni@gmail.com and adkat80@gmail.com.


![istockphoto-1142790620-1024x1024](https://user-images.githubusercontent.com/110082803/207814972-ad2f2cb6-211b-40f5-8404-9ce25cf5e7c1.jpg)
