#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <iostream>
#include <stdlib.h>

#include "Tape.h"

using namespace std;

struct State {
    bool isAccepting = false;
    bool isRejecting = false;
    bool isStart = false;
    int id;
};

struct Transition {
    int currentState;
    int nextState;
    char readSymbol;
    char writeSymbol;
    char direction;
};

class TuringMachine {
    private:
        State *states;
        Transition *transitions;
        int numStates;
        int numTransitions;
        State getState(int id);
        State getStartState();
        State transition(Tape *tape, int currentState, char readSymbol);
        
    public:
        TuringMachine(string filename);
        ~TuringMachine();
        void run(string input, int maxTransitions);
};

#endif
