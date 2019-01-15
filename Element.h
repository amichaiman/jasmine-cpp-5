//
// Created by amichai on 10/01/19.
//

#ifndef JASMINE_CPP_5_ELEMENT_H
#define JASMINE_CPP_5_ELEMENT_H
#include <fstream>
using namespace std;

class Element {
public:
    Element(int inputVectorDimension, int targetVectorDimension);

    double *getInputVector() const;
    void setInputVector(double *inputVector);
    double *getTargetVector() const;
    void setTargetVector(double *targetVector);
    int getInputVectorDimension() const;
    void setInputVectorDimension(int inputVectorDimension);
    int getTargetVectorDimension() const;
    void setTargetVectorDimension(int targetVectorDimension);
    friend ifstream &operator>>(ifstream& stream, Element element);
    friend ostream &operator<<(ostream& stream, Element element);
    void createTargetVector();
    Element* getShiftedBeRandomClone();
    bool operator>(Element &element);
private:
    int inputVectorDimension;
    int targetVectorDimension;
    double *inputVector;
    double *targetVector;

    void setTargetVectorAt(int i, double n);
};


#endif //JASMINE_CPP_5_ELEMENT_H
