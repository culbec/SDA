#pragma once
#include "LI.h"

typedef int TElem;

class LI;
class Node;


class IteratorLI{
    friend class LI;
private:
    // constructor iterator
    // iteratorul primeste o referinta catre lista de iterat
    // iteratorul se va pozitiona pe primul element

   	IteratorLI(const LI& lista);

    // referinta catre lista
	const LI& lista;

    // reprezentarea iteratorului
    // va contine o referinta catre elementul curent
    // va contine un index care va da pozitia elementului
    Node* current;
    int currentIndex;

	

public:
        // pozitioneaza iteratorul pe primul element din lista
        // complexitate: Theta(1)
        void prim();

        // pozitioneaza iteratorul pe urmatorul element din lista
        // complexitate: Theta(1)
        // exceptie: iteratorul nu este valid
        void urmator();

        // verifica daca iteratorul este valid (refera un element al listei)
        // complexitate: Theta(1)
        bool valid() const;

        // returneaza valoarea elementului curent din lista
        // complexitate: Theta(1)
        // exceptie: iteratorul nu este valid
        TElem element() const;
};

