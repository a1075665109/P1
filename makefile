all: scanner

clean:
	-rm main.o testScanner.o input.txt scanner.o scanner 

scanner: main.o testScanner.o scanner.o
	g++ -o scanner main.o scanner.o testScanner.o

main.o: main.cpp
	g++ -c main.cpp
testScanner.o: testScanner.cpp
	g++ -c testScanner.cpp

scanner.o: scanner.cpp
	g++ -c scanner.cpp


