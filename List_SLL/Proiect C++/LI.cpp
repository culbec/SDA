#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

LI::LI() {
    this->prim = nullptr;
    this->ultim = nullptr;
}

int LI::dim() const {
    if(this->prim == nullptr)
        return 0; // nu are rost sa parcurgem pentru ca lista e vida

    int lg = 0;

    Node* ref = this->prim; // referinta catre primul nod

    while(ref != nullptr) {
        lg++;
        ref = ref->getNext(); // se actualizeaza cu referinta spre urmatorul
    }
    return lg;
}


bool LI::vida() const {
    return this->prim == nullptr;
}

TElem LI::element(int i) const {
    if(i >= dim() || i < 0)
        // eroare daca index depaseste lungimea listei
        throw std::runtime_error("Index nu refera un element din lista.");

    // referinta spre primul element
    Node* ref = this->prim;

    // parcurgem lista pana la index
    for(int j = 0; j < i; j++)
        ref = ref->getNext();

    // preluam informatia utila si o returnam
    TElem elem = ref->getData();
    return elem;
}

TElem LI::modifica(int i, TElem e) {
    if(i >= dim() || i < 0)
        // eroare daca index depaseste lungimea listei
        throw std::runtime_error("Index nu refera un element din lista.");

    Node* ref; TElem oldElem;

    // cazul in care nodul de modificat este primul
    if(i == 0) {
        oldElem = prim->getData();
        prim->setData(e);
        return oldElem;
    }
    // referinta spre primul element
    ref = this->prim;

    // parcurgem lista pana la pozitia index
    for(int j = 0; j < i - 1; j++)
        ref = ref->getNext();

    // cazul in care nodul de modificat este ultimul
    if(ref->getNext() == ultim) {
        oldElem = ultim->getData();
        ultim->setData(e);
        return oldElem;
    }
    // salvam vechiul element si il actualizam
    oldElem = (ref->getNext())->getData();
    (ref->getNext())->setData(e);

    return oldElem;
}

void LI::adaugaSfarsit(TElem e) {
    // initializam un nou nod cu inf. util. = elem
    Node* newNode = new Node(e);

    // actualizam referinta catre next a ultimului element si
    // actualizam referinta spre ultimul element
    if(this->ultim == nullptr)
        this->ultim = newNode;
    else {
        (this->ultim)->setNext(newNode);
        this->ultim = newNode;
    }

    // actualizam si referinta primului element, in caz ca acesta este nul
    if(this->prim == nullptr)
        this->prim = newNode;
}

void LI::adauga(int i, TElem e) {
    if(i >= dim() || i < 0)
        throw std::runtime_error("Index nu refera un element din lista.");

    Node* ref = this->prim; // iteram de la primul nod

    for(int j = 0; j < i - 1; j++)
        ref = ref->getNext();

    // initializam un nod nou
    Node* newNode = new Node(e);

    // setam referinta catre urmatorul nod al nodului nou catre
    // nodul referinta catre nodul urmator al nodului vechi

    // nodul se adauga la inceputul listei
    if(i == 0) {
        newNode->setNext(ref);
        ref->setNext(ref->getNext());
        prim = newNode;
    }
    else {
        newNode->setNext(ref->getNext());
        ref->setNext(newNode);
    }
    if(prim == ultim)
        ultim = newNode;
}

TElem LI::sterge(int i) {
    if(i >= dim() || i < 0)
        throw std::runtime_error("Index nu refera un element din lista.");

    Node* ref; TElem oldElem;

    // cazul in care elementul de sters este primul
    if(i == 0) {
        ref = prim->getNext();
        oldElem = prim->getData();
        delete prim;
        prim = ref;
        return oldElem;
    }

    // incepem iteratia de la primul nod
    ref = this->prim;

    for(int j = 0; j < i - 1; j++)
        ref = ref->getNext();

    // cazul in care ultimul nod este cel de sters
    if(ref->getNext() == ultim) {
        oldElem = ultim->getData();
        delete ultim;
        ultim = ref;
        ultim->setNext(nullptr);
        return oldElem;
    }

    // in restul cazurilor, exista ANTERIOR - CURENT - POSTERIOR
    // se pot actualiza legaturile
    Node* nextRef = (ref->getNext())->getNext();
    oldElem = (ref->getNext())->getData();

    delete ref->getNext();
    ref->setNext(nextRef);

    return oldElem;
}

int LI::cauta(TElem e) const{
    // se itereaza peste lista folosind iteratorul, care contine indici
    IteratorLI iterator = this->iterator();

    while(iterator.valid()) {
        if(iterator.element() == e)
            return iterator.currentIndex; // se returneaza index-ul iteratorului, in caz ca s-a gasit elementul
        iterator.urmator();
    }
    return -1; // altfel, -1
}

IteratorLI LI::iterator() const {
    return IteratorLI(*this);
}

LI::~LI() {
    deleteNodes(this->prim);
}
