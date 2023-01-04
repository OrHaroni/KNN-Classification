CC = g++ -std=c++11

OBJS = ExtraFunc.o tableVec.o distance.o Client.o Server.o


	RM = rm -rf
	ERROR_IGNORE = 2>/dev/null
	EXE = a.out

all:$(OBJS) mainServer.o mainClient.o
	$(CC) $(OBJS) server.o -o server.out
	$(CC) $(OBJS) client.o -o client.out

%.o: %.cpp %.h
	$(CC) -c $< -o $@

%.h:

%.cpp:
mainServer.o: mainServer.cpp
	$(CC) -c -o server.o mainServer.cpp
mainClient.o: mainClient.cpp
	$(CC) -c -o client.o mainClient.cpp
clean:
	$(RM) $(OBJS) $(ERROR_IGNORE)
	$(RM) $(EXE) $(ERROR_IGNORE)

run: $(OBJ) server.o client.o
	 $(CC) $(OBJ) server.o -o server.out & $(CC) $(OBJ) client.o -o client.out
