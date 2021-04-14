# LAB 1 - Rank-2 and Rank-3 Tensor Contraction

The goal of this project is to create algorithms that can compute either the rank-2 or 
rank-3 tensor contraction. These two algorithms are ran using two parallelisation 
methods: PThread and OpenMP. 

## Table of contents
* [Team Members](#team-members)
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Compilation](#compilation)
* [Status](#status)
* [Contributions](#contributions)

## Team Members 
* Dino Areias - 1427614 
* Michael Wilkins - 1393005
* Fiskani Banda - 1355621

## General info
The project is written in C++. The main purpose of the project is to use parallelisation and 
compare the execution times between OpenMP and PThread. For each function, there is a timer 
that runs. The outputs of these timers are stored in the file time.log which can be retrieved 
once the code is compiled and runs successfully. The values of the tensors are generated from 
a random number generator. The tensor bounds have been restricted to 10, 20, and 30, but can be
adjusted to test scalability.  

## Technologies
* Editor - Visual Studio Code 1.55.1
* Compiler and language version - GCC/G++ 9.3
* Build Tools - Makefile

## Setup
Editor used is Visual Studio Code and the set up for the c++ environment can be found using 
[@Visual Studio linux guide](https://code.visualstudio.com/docs/cpp/config-linux)


## Compilation
To compile the project using the integrated terminal, run: 

$ make clean && make && ./main

## Status
Project is: Completed

## Contributions

* Michael Wilkins - Random Number Generator , OpenMP implementation, PThread.  
* Fiskani Banda - Rank-2 and Rank-3 tensor contraction algorithms, PThread. 
* Dino Areias - Complications with seeting up the coding environment-unable to set up Visual Studios in Unix environment. Thus took over with writing majority of the lab report which accompanies this project. 