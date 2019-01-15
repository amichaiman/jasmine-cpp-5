#include <iostream>
#include <cstdlib>
#include "Simulation.h"
#include <ctime>

using namespace std;
int main(int argc, char **argv) {
    srand(time(0));
    if (argc != 3) {
        cerr << "ERROR: Invalid arguments.\nUSAGE: <./executable> <input-filename> <output-filename>" << endl;
        exit(1);
    }

    Simulation simulation;

    try {
        simulation.init(argv[1]);
    } catch (exception &e) {
        cout << e.what() << endl;
        exit(2);
    }
    simulation.run();

    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cerr << "ERROR: Invalid output file" << endl;
        exit(3);
    }
    outputFile << simulation;
    return 0;
}