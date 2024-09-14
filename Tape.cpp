#include <iostream>
#include <stdlib.h>
#include "Tape.h"

using namespace std;

Tape::Tape(string startString) {
    head = new TapeItem;
    TapeItem *current = head;
    for (int i = 0; i < startString.length(); i++) {
        current->c = startString[i];
        current->next = new TapeItem;
        current->next->prev = current;
        current = current->next;
    }
}

Tape::~Tape() {
    TapeItem *forward = head;
    TapeItem *backward = head->prev;
    while (forward != NULL) {
        TapeItem *next = forward->next;
        delete forward;
        forward = next;
    }
    while (backward != NULL) {
        TapeItem *prev = backward->prev;
        delete backward;
        backward = prev;
    }
}

void Tape::print() {
    TapeItem *current = head;
    while (current->prev != NULL) {
        current = current->prev;
    }
    while (current != NULL) {
        cout << current->c;
        current = current->next;
    }
}

void Tape::moveLeft() {
    if (head->prev == NULL) {
        head->prev = new TapeItem;
        head->prev->prev = NULL;
        head->prev->next = head;
    }
    head = head->prev;
}

void Tape::moveRight() {
    if (head->next == NULL) {
        head->next = new TapeItem;
        head->next->next = NULL;
        head->next->prev = head;
    }
    head = head->next;
}

void Tape::write(char c) {
    head->c = c;
}

char Tape::read() {
    return head->c;
}
