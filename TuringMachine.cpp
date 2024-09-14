#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "TuringMachine.h"
#include "Tape.h"

using namespace std;

TuringMachine::TuringMachine(string filename) {
    // Read the file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        exit(1);
    }
    
    // Get the number of states and transitions
    string line;
    numStates = 0;
    numTransitions = 0;
    while (getline(file, line)) {
        if (line.find("state") == 0) {
            numStates++;
        } else if (line.find("transition") == 0) {
            numTransitions++;
        }
    }

    // Reset the file
    file.clear();
    file.seekg(0, ios::beg);

    // Initialize the states and transitions
    states = new State[numStates];
    transitions = new Transition[numTransitions];

    // Read the states and transitions
    int readStates = 0;
    int readTransitions = 0;
    while (getline(file, line)) {
        if (line.find("state") == 0) {
            int stateNum;
            char stateType = ' '; // Default in case there is no label
            sscanf(line.c_str(), "state\t%d\t%c", &stateNum, &stateType);
            
            states[readStates].id = stateNum;
            if (stateType == 'a') {
                states[readStates].isAccepting = true;
            } else if (stateType == 'r') {
                states[readStates].isRejecting = true;
            } else if (stateType == 's') {
                states[readStates].isStart = true;
            }

            readStates++;
        } else if (line.find("transition") == 0) {
            int currentState, nextState;
            char readSymbol, writeSymbol, direction;
            sscanf(line.c_str(), "transition\t%d\t%c\t%d\t%c\t%c", &currentState, &readSymbol, &nextState, &writeSymbol, &direction);

            if (readSymbol == '_') {
                readSymbol = ' ';
            }
            if (writeSymbol == '_') {
                writeSymbol = ' ';
            }

            transitions[readTransitions].currentState = currentState;
            transitions[readTransitions].nextState = nextState;
            transitions[readTransitions].readSymbol = readSymbol;
            transitions[readTransitions].writeSymbol = writeSymbol;
            transitions[readTransitions].direction = direction;

            readTransitions++;
        }
    }

    // Close the file
    file.close();
}

TuringMachine::~TuringMachine() {
    delete[] states;
    delete[] transitions;
}

State TuringMachine::getState(int id) {
    for (int i = 0; i < numStates; i++) {
        if (states[i].id == id) {
            return states[i];
        }
    }
    cout << "Error: state " << id << " not found" << endl;
    exit(1);
}

State TuringMachine::getStartState() {
    for (int i = 0; i < numStates; i++) {
        if (states[i].isStart) {
            return states[i];
        }
    }
    cout << "Error: no start state found" << endl;
    exit(1);
}

State TuringMachine::transition(Tape *tape, int currentState, char readSymbol) {
    for (int i = 0; i < numTransitions; i++) {
        if (transitions[i].currentState == currentState && transitions[i].readSymbol == readSymbol) {
            tape->write(transitions[i].writeSymbol);
            if (transitions[i].direction == 'L') {
                tape->moveLeft();
            } else if (transitions[i].direction == 'R') {
                tape->moveRight();
            }
            return getState(transitions[i].nextState);
        }
    }
    cout << "Error: no transition found for state " << currentState << " and symbol " << readSymbol << endl;
    exit(1);
}

void TuringMachine::run(string input, int maxTransitions) {
    Tape tape(input);
    State currentState = getStartState();
    int numTransitions = 0;
    string exitReason;
    while (true) {
        if (currentState.isAccepting) {
            exitReason = "accept";
            break;
        } else if (currentState.isRejecting) {
            exitReason = "reject";
            break;
        } else if (numTransitions >= maxTransitions) {
            exitReason = "quit";
            break;
        }
        currentState = transition(&tape, currentState.id, tape.read());
        numTransitions++;
    }
    tape.print();
    cout << " " << exitReason << endl;
}
