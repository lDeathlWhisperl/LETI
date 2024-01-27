
all: Main Polynom TApplication TComplex
	g++ Main.o Polynom.o TApplication.o TComplex.o -o Application
	
start: all
	clear
	./Application

Main:
	g++ -c Main.cpp

Polynom:
	g++ -c Polynom.cpp
	
TApplication:
	g++ -c TApplication.cpp
	
TComplex:
	g++ -c TComplex.cpp
	
clear:
	rm *.o Application
