all: scanner

clean:
	-rm main.o testScanner.o input.txt scanner.o scanner 

scanner: main.o testScanner.o scanner.o
	g++ -o scanner main.o scanner.o testScanner.o

main.o: main.cpp
	g++ -g main.cpp
testScanner.o: testScanner.cpp
	g++ -g testScanner.cpp

scanner.o: scanner.cpp
	g++ -g scanner.cpp


