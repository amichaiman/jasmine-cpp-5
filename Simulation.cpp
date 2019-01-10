//
// Created by amichai on 10/01/19.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

bool fileStateIsGood(ifstream &file) {
    return !file.bad() && !file.fail();
}
void Simulation::init(const char *filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw InvalidFilenameException(filename);
    }
    int inputVectorDimension;
    int targetVectorDimension;
    file >> numOfElements >> inputVectorDimension >> targetVectorDimension >> numOfIterations;

    if (!fileStateIsGood(file) || numOfElements > MAX_NUM_OF_ELEMENTS || inputVectorDimension > MAX_INPUT_VECTOR_DIMENSION || inputVectorDimension <= targetVectorDimension) {
        throw InvalidDefinition(filename);
    }

    for (int i=0; i<numOfElements; i++) {
        Element *element = new Element(inputVectorDimension, targetVectorDimension);
        try {
            file >> *element;
        } catch (exception &e) {
            throw InvalidPopulationDefinition(filename, i+1);
        }
        element->createTargetVector();
        elements.push_back(element);
    }
    long pos = file.tellg();
    file.seekg(0, ios::end);
    if (file.tellg() - pos > 1) {
        throw InvalidPopulationDefinition(filename, numOfElements+1);
    }
}

void Simulation::run() {
    for (int i=0; i <numOfIterations; i++) {
        doublePopulation();
    }
}

void Simulation::doublePopulation() {
    for (int i=0; i<numOfElements; i++) {
        Element* newElement = elements.at(static_cast<unsigned long>(i))->getShiftedBeRandomClone();
        elements.push_back(newElement);
    }

}

double roundToSixDecimalPoints(double n) {
    return (floor(n*1000000))/1000000.0;
}
ostream &operator<<(ostream& stream, Element element) {
    for (int i=0; i<element.targetVectorDimension; i++) {
        stream << roundToSixDecimalPoints(element.targetVector[i]) << ' ';
    }
    return stream;
}
ifstream &operator>>(ifstream& stream, Element element) {
    for (int i=0; i<element.inputVectorDimension; i++) {
        stream >> element.inputVector[i];
        if (!fileStateIsGood(stream) || stream.peek() != (i == element.inputVectorDimension-1 ? '\n' : ' ')) {
            throw exception();
        }
    }
    return stream;
}
