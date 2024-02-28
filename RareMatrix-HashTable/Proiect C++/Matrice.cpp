#include "Matrice.h"
#include <exception>

using namespace std;

int Matrice::hash(int linie, int coloana) const {
    // dispersia unui element in tabela se va face tinand cont de pozitionarea sa
    return (linie + coloana) % this->nrChei;
}

Matrice::Matrice(int m, int n) {
	if(m <= 0 || n <= 0)
        throw exception();

    // initializam tabela
    this->linii = m;
    this->coloane = n;

    // alegem un nr. de chei in functie de liniile si coloanele primite
    this->nrChei = (m * n) % (m + n) + 13;
    this->TD = new Node*[this->nrChei]{nullptr};
}

int Matrice::nrLinii() const{
	return this->linii;
}


int Matrice::nrColoane() const{
	return this->coloane;
}


TElem Matrice::element(int i, int j) const{
	if((i < 0 || i > this->linii) || (j < 0 || j > this->coloane))
        throw exception();

    // preluam dispersia elementului in tabela
    int hashValue = this->hash(i, j);

    // preluam referinta catre elementul din lista de la pozitia hashValue
    Node* ref = this->TD[hashValue];

    // parcurgem lista independenta cat timp referinta nu e nula
    while(ref != nullptr) {
        if(ref->linie == i && ref->coloana == j) {
            return ref->valoare;
        }
        // actualizam legatura
        ref = ref->next;
    }
	// daca am ajuns pe linia aceasta -> nu exista elementul
    return -1;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	if((i < 0 || i > this->linii) || (j < 0 || j > this->coloane))
        throw exception();

    // preluam dispersia elementului in tabela
    int hashValue = this->hash(i, j);

    // incepem sa parcurgem lista de la pozitia hashValue
    // daca gasim elementul -> returnam valoarea vechiului element
    // daca nu il gasim -> inseamna ca nu exista -> il adaugam
    Node *ref = this->TD[hashValue];

    // prima data parcurgem lista pana la final pentru a verifica daca exista elementul
    while(ref != nullptr) {
        if(ref->linie == i && ref->coloana == j) {
            // inseamna ca am gasit elementul
            TElem old = ref->valoare;
            ref->valoare = e;
            return old;
        }
        ref = ref->next;
    }
    // daca am ajuns pe aceasta linie, inseamna ca nu exista elementul in lista noastra
    // il putem adauga in matrice
    Node *node = new Node{i, j, e};
    node->next = this->TD[hashValue];
    this->TD[hashValue] = node;
	return -1;
}

Matrice::~Matrice() {
    // destructorul trebuie sa distruga toate elementele alocate dinamic
    for(int i = 0; i < nrChei; i++)
        if(this->TD[i] != nullptr) {
            Node *ref = this->TD[i];
            while(ref != nullptr) {
                Node *next = ref->next;
                delete ref;
                ref = next;
            }
        }
    // dealocam si tabela
    delete [] TD;
}


