#!/bin/bash

g++ -c Book.cpp
g++ -c Menu.cpp
g++ -c CW.cpp

g++ Menu.o CW.o Book.o -o launcher
