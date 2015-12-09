all: main

AssParser.cpp: AssParser.y
	bison -d -oAssParser.cpp -hAssParser.h AssParser.y

AssScanner.cpp: AssScanner.l
	flex -oAssScanner.cpp AssScanner.l

AssParser.o: AssParser.cpp
	g++ -c AssParser.cpp

AssScanner.o: AssScanner.cpp
	g++ -c AssScanner.cpp
main.o: AssParser.cpp main.cpp 
	g++ -c main.cpp
main:  main.o AssScanner.o
	g++ -o main main.o  AssScanner.o

clean:
		rm -f *.o main AssParser.cpp AssScanner.cpp AssParser.h