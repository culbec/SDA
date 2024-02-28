#pragma once

#include "IteratorLI.h"

typedef int TElem; // elementul nostru reprezinta de fapt informatia utila a nodului din lista
class IteratorLI;

// lista va contine elemente de tip Node
// Node va contine: data, informatia relevanta, si referinta spre urmatorul nod;

class Node{
    private:
        // reprezentarea unui nod va contine informatia utila
        // si referinta spre un urmator nod
        TElem data;
        Node* next;
    public:
        Node(TElem data) {
            this->data = data;
            this->next = nullptr;
        }

        // gettere
        TElem getData() const {
            return this->data;
        }

        Node* getNext() const {
            return (Node*)this->next;
        }

        // settere
        void setData(TElem data) {
            this->data = data;
        }

        void setNext(Node* next) {
            this->next = next;
        }
};

class LI {
private:
    friend class IteratorLI; // putem accesa campurile private ale clasei Iterator

    // reprezentarea

    // de asemenea lista, va retine o referinta spre primul element
    // se poate retine si o referinta spre ultimul element, dar este optional
    Node *prim;
    Node *ultim;

    // functie pentru dealocarea nodurilor dintr-o lista inlantuita
    void deleteNodes(Node* node) {
        if(node == nullptr)
            return;

        deleteNodes(node->getNext());
        delete node;
    }

public:
        // aici declaram prototipurile operatiilor ce au sens pentru o lista

        // constructorul(operatia de creare) -> initializeaza lista
        // complexitate: Theta(1)
		LI ();

        // se returneaza dimensiunea listei
        // complexitate: Theta(n)
		int dim() const;

        // se verifica daca lista este vida
        // complexitate: Theta(1)
		bool vida() const;

        // se returneaza elementul cu un anumit index
        // complexitate: O(n)
        // exceptie: index-ul nu refera un element valid
		TElem element(int i) const;

        // se modifica un element cu un anumit index si se returneaza elementul vechi
        // complexitate: O(n)
        // exceptie: index-ul nu refera un element valid
		TElem modifica(int i, TElem e);

        // se adauga un element la sfarsitul listei
        // complexitate: Theta(n)
		void adaugaSfarsit(TElem e);

        // se adauga un element la pozitia index
        // complexitate: Theta(1)
        // exceptie: index-ul nu refera pozitia unui element din lista
		void adauga(int i, TElem e);

        // sterge un element de la pozitia index si returneaza elementul sters
        // complexitate: Theta(1)
        // exceptie: index nu refera element valid
		TElem sterge(int i);

        // cauta un element si ii returneaza prima pozitie, daca apare, sau -1
        // complexitate: O(n)
		int cauta(TElem e)  const;

        // returneaza un iterator peste lista
        // complexitate: Theta(1)
		IteratorLI iterator() const;

        // destructor
        // complexitate: Theta(n);
		~LI();
};
