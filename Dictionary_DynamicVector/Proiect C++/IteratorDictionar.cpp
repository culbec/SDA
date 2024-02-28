#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

const char eroare[] = "Iterator invalid.\n";

IteratorDictionar::IteratorDictionar(const Dictionar &d) : dict(d) {
    // Complexitate = theta(1)
    this->index = 0;
}


void IteratorDictionar::prim() {
    // Complexitate: theta(1)
    // resetam index-ul
    this->index = 0;
}


void IteratorDictionar::urmator() {
    /* Complexitate: theta(1) */
    // actualizam index-ul
    if(this->valid())
        this->index++;
    else
        throw(eroare);
}


TElem IteratorDictionar::element() const {
    if(!this->valid())
        throw(eroare);
    return pair<TCheie, TValoare>(dict.vec[this->index].first, dict.vec[this->index].second);
}


bool IteratorDictionar::valid() const {
    // Complexitate: theta(1)
    if(this->index < dict.lungime)
        return true;
    return false;
}

