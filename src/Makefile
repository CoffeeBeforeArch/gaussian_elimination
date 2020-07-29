# A simple makefile for Gaussian Elimination benchmarks

CXX_FLAGS = -O3 -march=native -mtune=native -flto -fuse-linker-plugin --std=c++2a
LINKER_FLAGS = -lbenchmark -lpthread

benchmark : serial_ge.o parallel_ge.o 
	g++ benchmark.cpp serial_ge.o parallel_ge.o ${CXX_FLAGS} ${LINKER_FLAGS} -o ge_bench

parallel_ge.o : parallel_ge.cpp
	g++ -c parallel_ge.cpp ${CXX_FLAGS}

serial_ge.o : serial_ge.cpp
	g++ -c serial_ge.cpp ${CXX_FLAGS}

clean :
	rm -rf ge_bench
	rm -rf *.o

