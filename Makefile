CXX = g++

CXXFLAGS = -O3 -march=native -fopenmp

TARGET = model-run

SRC = model-run.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	$ ./model-run

run: model-run
	./model-run	
run-bfs: $ g++ -O3 -fopenmp test.cpp -o test
         $ ./test


