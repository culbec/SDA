#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

Dictionar::Dictionar() {
    /*
     * Constructorul va instantia un obiect de tip Dictionar si va valorifica parametrii
     * Complexitate: Theta(1)
     */
    this->capacitate = 1;
    this->lungime = 0;
    this->vec = new TElem[1];
    IteratorDictionar iter = iterator();
}

Dictionar::~Dictionar() {
    /* Destructorul va distruge doar instanta curenta
     * Complexitate: Theta(1)
     */
    delete (this->vec);
}

TValoare Dictionar::adauga(TCheie c, TValoare v) {
    /* Metoda adauga va avea 3 outcome-uri:
     * 1. In cazul in care nu exista cheia lungimea == capacitatea, redimensionam dictionarul, adaugam inregistrarea
     *    si returnam valorea inregistrarii.
     * 2. In cazul in care exista cheia, inlocuim valoarea si returnam valoarea modificata.
     * 3. In cazul in care nu exista cheia si lungimea < capacitatea, adaugam inregistrarea si returnam valoarea
     *    inregistrarii.
     * Complexitate: O(n)
     */
    // construim iteratorul
    IteratorDictionar iter = iterator();
    // pozitionam iteratorul pe primul element din dictionar
    iter.prim();
    // parcurgem container-ul cat timp iteratorul este valid (nu depaseste capacitatea dictionarului)
    while (iter.valid()) {
        if (iter.element().first == c) {
            TValoare _v = this->vec[iter.index].second;
            this->vec[iter.index].second = v;
            return _v;
        }
        iter.urmator();
    }
    // daca nu exista inregistrarea, o adaugam
    // posibil sa fie nevoie sa redimensionam intai -> verificam daca lungimea + 1 = capacitatea
    if (this->lungime == this->capacitate) {
        this->redim();
        // adaugam elementul
        this->vec[this->lungime] = TElem(c, v);
        // actualizam lungimea
        this->lungime++;
    } else
        // trebuie doar sa adaugam inregistrarea
        this->vec[this->lungime++] = TElem(c, v);
    return NULL_TVALOARE;
}


//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const {
    // Complexitate: O(n)

    // construim iteratorul
    IteratorDictionar iter = iterator();
    // il pozitionam pe primul element(adresa de inceput a dictionarului)
    iter.prim();
    // cat timp este valid, cautam cheia
    while (iter.valid()) {
        if (iter.element().first == c)
            return iter.element().second;
        // ne pozitionam pe urmatorul element
        iter.urmator();
    }
    return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c) {
    // Complexitate: O(n)

    /* Stergere: identificam pozitia la care se afla elementul cu cheia c (daca exista acest element)
     *           si mutam toate elementele din dreapta lui la stanga cu o pozitie
    */

    // instantiem iteratorul
    IteratorDictionar iter = iterator();
    // il pozitionam pe primul element
    iter.prim();
    //cautam acest element cu cheia c cat timp iteratorul este valid
    while (iter.valid()) {
        if (iter.element().first == c) {
            TValoare _v = iter.element().second;
            for (int i = iter.index; i < lungime - 1; i++)
                this->vec[i] = this->vec[i + 1];
            this->lungime--;
            return _v;
        }
        // ne pozitionam pe urmatorul element
        iter.urmator();
    }
    return NULL_TVALOARE;
}

void Dictionar::redim() {
    // Complexitate: theta(n)

    // declaram o noua locatie de memorie cu capacitate dubla fata de cea curenta
    TElem *vec_new = new TElem[2 * this->capacitate];

    // copiem toate elementele din container-ul curent in cel nou
    // instantiem un iterator
    IteratorDictionar iter = iterator();
    // il pozitionam pe primul element
    iter.prim();

    while (iter.valid()) {

        vec_new[iter.index] = iter.element();
        iter.urmator();
    }

    delete this->vec;
    this->vec = vec_new;
    this->capacitate *= 2;
}


int Dictionar::dim() const {
    /* Complexitate: Theta(1) */
    // verificam prima data daca dictionarul e vid
    if (!this->vid())
        return this->lungime;
    return 0;
}

bool Dictionar::vid() const {
    // Complexitate: theta(1)
    if (this->lungime > 0)
        return false;
    return true;
}


IteratorDictionar Dictionar::iterator() const {
    return IteratorDictionar(*this);
}


