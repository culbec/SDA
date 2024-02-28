#include "IteratorLO.h"
#include <exception>

using namespace std;

IteratorLO::IteratorLO(const LO &lo) : lo(lo) {
    this->pozitie = 0; // initializam pozitia
    this->prim(); // plasam iteratorul pe primul element
}

void IteratorLO::prim() {
    // verificam intai daca lista este goala
    if (this->lo.lungime == 0) {
        this->pozitie = -1;
        return;
    }
    this->pozitie = this->lo.first;
}

void IteratorLO::urmator() {
    if (!this->valid())
        throw exception();
    this->pozitie = this->lo.elems[this->pozitie].next;
}

bool IteratorLO::valid() const {
    // verificam daca pozitia elementului referit de iterator nu se afla in lista primilor liberi
    // sau daca pozitia este diferita de -1
    if (this->pozitie == -1)
        return false;

    int currentPos = this->lo.primLiber;
    while (currentPos != -1) {
        if (this->pozitie == currentPos)
            return false;
        currentPos = this->lo.elems[currentPos].next;
    }
    return true;
}

TElement IteratorLO::element() const {
    if (!this->valid())
        throw exception();
    return this->lo.elems[this->pozitie].elem;
}


