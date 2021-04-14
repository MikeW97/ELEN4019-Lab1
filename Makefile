# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g -fopenmp
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o matrixGen.o rank2TensorMultOpenMP.o rank2TensorMultPThread.o rank3TensorMultOpenMP.o rank3TensorMultPThread.o
	$(CC) $(CFLAGS) -o main main.o matrixGen.o rank2TensorMultOpenMP.o rank2TensorMultPThread.o rank3TensorMultOpenMP.o rank3TensorMultPThread.o
 
# The main.o target can be written more simply
 
main.o: main.cpp matrixGen.h rank2TensorMultOpenMP.h rank2TensorMultPThread.h rank3TensorMultOpenMP.h rank3TensorMultPThread.h
	$(CC) $(CFLAGS) -c main.cpp

matrixGen.o: matrixGen.h

rank2TensorMultOpenMP.o: rank2TensorMultOpenMP.h 

rank2TensorMultPThread.o: rank2TensorMultPThread.h

rank3TensorMultOpenMP.o: rank3TensorMultOpenMP.h 

rank3TensorMultPThread.o: rank3TensorMultPThread.h

clean:
	rm -f *.o main