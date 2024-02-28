#include "IteratorLI.h"
#include "LI.h"
#include <exception>
#include <iostream>

IteratorLI::IteratorLI(const LI& li): lista(li) {
    this->current = (Node*)li.prim;
    this->currentIndex = 0; // index-ul elem curent
}

void IteratorLI::prim(){
    // resetam iteratorul -> il aducem inapoi pe prima pozitie
    this->current = (Node*)lista.prim;
    this->currentIndex = 0;
}

void IteratorLI::urmator(){
    if(!this->valid())
        throw std::runtime_error("Iterator invalid.");
    this->current = (this->current)->getNext();
    this->currentIndex++;
}

bool IteratorLI::valid() const{
    if(this->current == nullptr)
        return false;
    return true;
}

TElem IteratorLI::element() const{
    if(!this->valid())
        throw std::runtime_error("Iterator invalid.");
    return (this->current)->getData();
}
