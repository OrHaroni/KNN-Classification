CC = g++ -std=c++11

OBJS = ExtraFunc.o tableVec.o distance.o Client.o Server.o


	RM = rm -rf
	ERROR_IGNORE = 2>/dev/null
	EXE = a.out

all: $(OBJS) mainServer.o
	$(CC) $(OBJS) mainServer.o
%.o: %.cpp %.h
	$(CC) -c $< -o $@

%.h:

%.cpp:
main.o: mainServer.cpp
	$(CC) -c mainServer.cpp
clean:
	$(RM) $(OBJS) $(ERROR_IGNORE)
	$(RM) $(EXE) $(ERROR_IGNORE)

run:all
	./a.out datasets/iris/iris_classified.csv 12345