
all: Main Polynom TApplication
	g++ Main.o Polynom.o TApplication.o -o Application
	
start: all
	clear
	./Application

Main:
	g++ -c Main.cpp

Polynom:
	g++ -c Polynom.cpp
	
TApplication:
	g++ -c TApplication.cpp
	
clear:
	rm *.o Application
