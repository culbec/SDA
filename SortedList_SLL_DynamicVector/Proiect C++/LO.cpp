#include "LO.h"
#include "IteratorLO.h"
#include <exception>

using namespace std;


LO::Node::Node(TElement elem, int next) {
    // initializarea unui nod
    this->elem = elem;
    this->next = next;
}

LO::LO(Relatie r) {
    this->relatie = r; // relatie de ordine a listei

    // initializam vectorul
    this->lungime = 0;
    this->capacitate = 2;
    this->elems = new Node[this->capacitate];

    this->first = -1; // nu exista elemente in lista

    // alocam 'primLiber'
    for (int i = 0; i < this->capacitate; i++)
        this->elems[i].next = i + 1;
    this->elems[this->capacitate - 1].next = -1;

    // prim liber va fi pozitia primului element din lista
    this->primLiber = 0;
}

IteratorLO LO::alocaNod() {
    // se marcheaza faptul ca primLiber nu mai este ocupat si se actualizeaza primLiber
    IteratorLO iter{*this};  // elementul se va plasa pe pozitia 'primLiber'
    iter.pozitie = this->primLiber;
    this->primLiber = this->elems[this->primLiber].next; // primLiber devine urmatoarea legatura din lista liberilor
    return iter; // returnam pozitia unde se poate adauga
}

void LO::dealocaNod(IteratorLO &poz) {
    // salvam pozitia pentru dealocat
    int posDealoc = poz.pozitie;

    // verificam daca elementul de dealocat se afla pe prima pozitie
    if (posDealoc == this->prim().pozitie) {
        // refacem legaturile pentru primLiber
        this->elems[posDealoc].next = this->primLiber;
        this->primLiber = posDealoc;
    } else {
        // alftel, elementul se afla undeva in lista noastra
        // iteram prin lista pentru a-i cauta pozitia
        int posPrev = this->prim().pozitie;

        while (this->elems[posPrev].next != posDealoc) {
            posPrev = this->elems[posPrev].next;
        }

        // refacem legaturile
        this->elems[posPrev].next = this->elems[posDealoc].next;
        this->elems[posDealoc].next = this->primLiber;
        this->primLiber = posDealoc;
    }
}

void LO::redim() {
    this->capacitate = this->capacitate * 2; // recapacitam
    Node *newElems = new Node[this->capacitate]; // vector nou alocat

    // mutam elementele
    for (int i = 0; i < this->lungime; i++)
        newElems[i] = this->elems[i];

    // refacem legaturile pentru lista primLiber;
    for (int i = this->lungime; i < this->capacitate; i++)
        newElems[i].next = i + 1;
    newElems[this->capacitate - 1].next = -1;

    // actualizam primLiber
    this->primLiber = this->lungime;

    // stergem vectorul vechi si reactualizam legatura
    delete[] this->elems;
    this->elems = newElems;
}

// returnare dimensiune
int LO::dim() const {
    return this->lungime;
}

// verifica daca LO e vida
bool LO::vida() const {
    return this->lungime == 0;
}

// prima pozitie din LO
IteratorLO LO::prim() const {
    return IteratorLO{*this};
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(IteratorLO &poz) const {
    if (!poz.valid())
        throw exception();
    return poz.element();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(IteratorLO &poz) {
    if (!poz.valid())
        throw exception();

    TElement deleted = this->elems[poz.pozitie].elem; // elementul sters

    IteratorLO prev = poz; // referinta catre pozitia elementului de sters
    poz.urmator(); // trecem pe nodul urmator
    this->dealocaNod(prev); // dealocam nodul
    this->lungime--; // actualizam lungimea

    if (prev.pozitie == this->first)
        this->first = poz.pozitie; // reactualizam pozitia primului element

    return deleted;
}

// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
IteratorLO LO::cauta(TElement e) const {
    auto iter = this->prim(); // ne plasam cu un iterator peste primul element din lista
    while (iter.valid() && iter.element() != e)
        iter.urmator(); // actualizam iteratorul cat timp acesta este valid sau nu contine elementul
    return iter; // returnam iteratorul -> fie invalid, fie reprezinta pozitia primului element gasit
}

// adaugare element in LO
void LO::adauga(TElement e) {
    // verificam daca iteratorul ce determina primul element liber este valid
    // daca nu este, inseamna ca avem nevoie de o redimensionare
    if (this->lungime == this->capacitate)
        this->redim();

    // acum, trebuie sa alocam un nou spatiu pentru nodul nostru
    auto iter = this->alocaNod();

    // acum, vom cauta prin lista locul unde nu se mai respecta ordinea dintre elementele listei
    // si elementul de adaugat

    // verificam intai daca lista este goala -> adaugam primul element din lista
    if (this->vida()) {
        this->first = iter.pozitie;
        this->elems[iter.pozitie].elem = e; // elementul va fi egal cu e
        this->elems[iter.pozitie].next = -1; // legatura spre urmatorul nod nu exista
        this->lungime++; // actualizam lungimea
    }
        // apoi daca elementul se afla in relatie cu primul element -> e devine primul element din lista
    else if (this->relatie(e, this->prim().element())) {
        this->elems[iter.pozitie].elem = e; // elementul va fi egal cu e
        this->elems[iter.pozitie].next = this->first; // elementul va lua locul primului element din lista
        this->first = iter.pozitie;
        this->lungime++; // actualizam lungimea
    }
        // atunci elementul se afla undeva in lista, dar nu la inceput
    else {
        int posPrev = this->prim().pozitie; // salvam pozitia elementului precedent
        int posCurrent = this->elems[posPrev].next; // pentru a itera prin lista

        // cautam pozitia unde ar trebui sa adaugam elementul
        while (posCurrent != -1 && this->relatie(this->elems[posCurrent].elem, e)) {
            posPrev = posCurrent;
            posCurrent = this->elems[posCurrent].next;
        }

        // elementul nostru va fi ultimul element
        if (posCurrent == -1) {
            this->elems[iter.pozitie].elem = e;
            this->elems[iter.pozitie].next = -1;
            this->elems[posPrev].next = iter.pozitie;
            this->lungime++;
        } else {
            // adaugam elementul
            this->elems[iter.pozitie].elem = e;
            this->elems[iter.pozitie].next = posCurrent;
            this->elems[posPrev].next = iter.pozitie;
            this->lungime++;
        }
    }
}

void LO::filtreaza(Conditie cond) {
    // verificam daca lista este vida
    if (this->vida())
        return;

    // plasam un iterator pe primul element din lista
    IteratorLO iter{*this};

    // parcurgem lista si stergem elementele care nu respecta conditia
    while (iter.valid()) {
        if (!cond(iter.element())) {
            this->sterge(iter);
        } else {
            iter.urmator();
        }
    }
}

//destructor
LO::~LO() {
    delete[] this->elems;
}
