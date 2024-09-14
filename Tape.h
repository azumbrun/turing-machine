#ifndef TAPE_H
#define TAPE_H
#include <iostream>
#include <stdlib.h>

using namespace std;

struct TapeItem {
    char c = ' ';
    TapeItem *next = NULL;
    TapeItem *prev = NULL;
};


class Tape {
    private:
        TapeItem* head;
        int size;
        
    public:
        Tape(string startString);
        ~Tape();
        void print();
        void moveLeft();
        void moveRight();
        void write(char c);
        char read();
};


#endif
