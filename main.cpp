#include <iostream>
#include <cstdlib>
#include "Simulation.h"

using namespace std;
int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "ERROR: Invalid arguments.\nUSAGE: <./executable> <input-filename> <output-filename>" << endl;
        exit(1);
    }

    Simulation simulation;

    try {
        simulation.init(argv[1]);
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    simulation.run();
    return 0;
}