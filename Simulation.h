//
// Created by amichai on 10/01/19.
//

#ifndef JASMINE_CPP_5_SIMULATION_H
#define JASMINE_CPP_5_SIMULATION_H

#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include "Element.h"

using namespace std;
class Simulation {

public:
    void init(const char * filename);
    void run();
    friend ostream& operator<<(ostream &stream, Simulation &simulation);

    struct InvalidFilenameException : public exception {
        const char* filename;

        explicit InvalidFilenameException(const char* filename) : filename(filename){ }

        virtual const char *what() const throw(){
            stringstream ss;
            ss << "ERROR: " << filename << " does not exist or cannot be opened";
            char *message = new char[ss.str().length()+1];
            strcpy(message,ss.str().c_str());
            return message;
        }
    };
    struct InvalidDefinition : public exception {
        const char* filename;

        explicit InvalidDefinition(const char* filename) : filename(filename){ }

        virtual const char *what() const throw(){
            stringstream ss;
            ss << "ERROR: simulation definition in " << filename << " is invalid";
            char *message = new char[ss.str().length()+1];
            strcpy(message,ss.str().c_str());
            return message;
        }
    };
    struct InvalidPopulationDefinition : public exception {
        const char* filename;
        const int lineNumber;

        explicit InvalidPopulationDefinition(const char* filename, const int lineNumber) : filename(filename), lineNumber(lineNumber){ }

        virtual const char *what() const throw(){
            stringstream ss;
            ss << "ERROR: population definition in " << filename << " at line " << lineNumber << " is invalid";
            char *message = new char[ss.str().length()+1];
            strcpy(message,ss.str().c_str());
            return message;
        }
    };


private:
    vector<Element*> elements;
    static const int MAX_NUM_OF_ELEMENTS = 1000;
    static const int MAX_INPUT_VECTOR_DIMENSION = 100;
    int numOfElements;
    int numOfIterations;

    void doublePopulation();
};


#endif //JASMINE_CPP_5_SIMULATION_H
