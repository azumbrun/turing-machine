# Default target
all: zumbrun_p1

zumbrun_p1: zumbrun_p1.o Tape.o TuringMachine.o
	g++ -std=c++17 -Wall -o zumbrun_p1 zumbrun_p1.o Tape.o TuringMachine.o

zumbrun_p1.o: zumbrun_p1.cpp Tape.h TuringMachine.h
	g++ -std=c++17 -Wall -c zumbrun_p1.cpp -o zumbrun_p1.o

Tape.o: Tape.cpp Tape.h
	g++ -std=c++17 -Wall -c Tape.cpp -o Tape.o

TuringMachine.o: TuringMachine.cpp TuringMachine.h
	g++ -std=c++17 -Wall -c TuringMachine.cpp -o TuringMachine.o

clean:
	rm -f zumbrun_p1.o Tape.o TuringMachine.o zumbrun_p1
