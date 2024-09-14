#include <iostream>
#include <stdlib.h>
#include "TuringMachine.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <machine file> <input> <max_transitions>" << endl;
        exit(1);
    }

    TuringMachine tm(argv[1]);
    tm.run(argv[2], atoi(argv[3]));

    return 0;
}
