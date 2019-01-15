//
// Created by amichai on 10/01/19.
//

#include <cstdlib>
#include "Element.h"

double *Element::getInputVector() const {
    return inputVector;
}

void Element::setInputVector(double *inputVector) {
    Element::inputVector = inputVector;
}

double *Element::getTargetVector() const {
    return targetVector;
}

void Element::setTargetVector(double *targetVector) {
    Element::targetVector = targetVector;
}

int Element::getInputVectorDimension() const {
    return inputVectorDimension;
}

void Element::setInputVectorDimension(int inputVectorDimension) {
    Element::inputVectorDimension = inputVectorDimension;
}

int Element::getTargetVectorDimension() const {
    return targetVectorDimension;
}

void Element::setTargetVectorDimension(int targetVectorDimension) {
    Element::targetVectorDimension = targetVectorDimension;
}

Element::Element(int inputVectorDimension, int targetVectorDimension)
        : inputVectorDimension(inputVectorDimension),
          targetVectorDimension(targetVectorDimension),
          inputVector(new double[inputVectorDimension]),
          targetVector(new double[targetVectorDimension]()){}

double square(double n) {
    return n*n;
}

void Element::createTargetVector() {
    for (int i=0; i<targetVectorDimension; i++) {
        for (int j=0; j<inputVectorDimension; j++) {
            targetVector[i] += square(inputVector[j] - (i+1));
        }
    }
}

double randomBetweenZeroAndOne() {
    return (static_cast<double>(rand())/(RAND_MAX));
}

Element *Element::getShiftedBeRandomClone() {
    Element* newElement = new Element(inputVectorDimension, targetVectorDimension);
    for (int i=0 ; i<targetVectorDimension; i++) {
        newElement->setTargetVectorAt(i, targetVector[i]+randomBetweenZeroAndOne());

    }
    return newElement;
}

void Element::setTargetVectorAt(int i, double n) {
    targetVector[i] = n;
}

bool Element::operator>(Element &element) {
    bool oneIsSmaller = false;
    for (int i=0; i<targetVectorDimension; i++) {
        if (targetVector[i] > element.targetVector[i]) {
            return false;
        }
        if (targetVector[i] < element.targetVector[i]) {
            oneIsSmaller = true;
        }
    }
    return oneIsSmaller;
}
