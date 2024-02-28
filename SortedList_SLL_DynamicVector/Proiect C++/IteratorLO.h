#pragma once

#include "LO.h"
typedef int TComparabil;
typedef TComparabil TElement;

class LO;

class IteratorLO {
    friend class LO;

private:
    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    explicit IteratorLO(const LO &lo);

    //contine o referinta catre containerul pe care il itereaza
    const LO &lo;

    /* aici e reprezentarea specifica a iteratorului */
    int pozitie; // pozitia pe care se afla elementul in tablou

public:

    //reseteaza pozitia iteratorului la inceputul containerului
    // complexitate: O(n)
    void prim();

    //muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    // complexitate: Theta(1)
    void urmator();

    //verifica daca iteratorul e valid (indica un element al containerului)
    // complexitate: Theta(1)
    bool valid() const;

    //returneaza valoarea elementului din container referit de iterator
    //arunca exceptie daca iteratorul nu e valid
    // complexitate: Theta(1)
    TElement element() const;
};


