//
// Created by amichai on 15/01/19.
//

#ifndef JASMINE_CPP_5_PARETO_H
#define JASMINE_CPP_5_PARETO_H

#include <vector>
#include <iostream>
#include "Element.h"
using namespace std;



// assumptions:
//      T object has function size()
//      elements in T object have operator >
//      elements in T object have swap function
//
template<typename T>
class Pareto {
public:
    static void ParetoSorting(T &vector);
    static void ElementsReordering(T &vector);
    static int *ParetoRanking(T &vector);
    static void RankElement(T &vector, unsigned int indexToRank, int *ranks);
};

template<typename T>
void Pareto<T>::ParetoSorting(T &vector) {
    ElementsReordering(vector);
}

template<typename T>
void Pareto<T>::ElementsReordering(T &vector) {
    int *ranks = ParetoRanking(vector);
    for (unsigned int i= static_cast<unsigned int>(vector.size()-1); i > 0; i--) {
        for (unsigned int j=0; j<i; j++) {
            if (ranks[j] > ranks[j+1]) {
                int temp = ranks[j];
                ranks[j] = ranks[j+1];
                ranks[j+1] = temp;
                iter_swap(vector.begin()+j, vector.begin()+j+1);
            }
        }
    }
}

template<typename T>
int *Pareto<T>::ParetoRanking(T &vector) {
    int *ranks = new int[vector.size()]();
    for (unsigned int i=0; i<vector.size(); i++) {
        RankElement(vector, i, ranks);
    }
    return ranks;
}

template<typename T>
void Pareto<T>::RankElement(T &vector, unsigned int indexToRank, int *ranks) {
    for (unsigned int i=0; i<vector.size(); i++) {
        if (i != indexToRank &&
            *(vector.at(static_cast<unsigned long>(i))) > *(vector.at(static_cast<unsigned long>(indexToRank)))) {
            ranks[indexToRank]++;
        }
    }
}


#endif //JASMINE_CPP_5_PARETO_H
