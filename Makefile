CC = g++ -std=c++11

OBJS = tableVec.o distance.o


	RM = rm -rf
	ERROR_IGNORE = 2>/dev/null
	EXE = a.out

all: $(OBJS) main.o
	$(CC) $(OBJS) main.o
%.o: %.cpp %.h
	$(CC) -c $< -o $@

%.h:

%.cpp:
main.o: main.cpp
	$(CC) -c main.cpp
clean:
	$(RM) $(OBJS) $(ERROR_IGNORE)
	$(RM) $(EXE) $(ERROR_IGNORE)

run:all
	./a.out 3.3 datasets/iris/iris_classified.csv AUC