#pragma once
#include <string>
using namespace std;

typedef int TElem;

class IteratorAB;

class Node {
public:
    TElem data; // informatia relevanta din nod
    int pozitie, left, right; // pozitiile in tablou ale nodului si ale subarborilor

    Node() {
        this->data = -1;
        this->pozitie = -1;
        this->left = -1;
        this->right = -1;
    }

    Node(TElem d, int p, int l, int r): data{d}, pozitie{p}, left{l}, right{r} {}

    Node(const Node& node) {
        this->data = node.data;
        this->pozitie = node.pozitie;
        this->left = node.left;
        this->right = node.right;
    }
};

class AB {

private:
    Node* tree; // tabloul care va contine arborele
    int* spatiuLiber; // pentru gestionarea spatiului liberS
    Node root; // radacina radacinii
    int primLiber; // pozitia primei pozitii libere din arbore

    int size, cp; // marimea si capacitatea listei

    void redim(); // pentru redimensionarea arborelui -> complexitate: Theta(n)

    Node copiere(Node* _tree, const Node& node); // pentru copierea nodurilor -> complexitate: Theta(n)

    void distruge(Node* _tree, const Node& node); // pentru distrugerea subarborilor

    static Node adaugare(AB& _ab, Node *_tree, const Node& node); // pentru crearea de subarbori plecand de la un subarbore al
                                                     // arborelui principal

public:
	friend class IteratorAB;
	friend class IteratorPreordine;
	friend class IteratorInordine;
	friend class IteratorPostordine;
	friend class IteratorLatime;

		//constructorul implicit
        // complexitate: Theta(capacitate initiala)
		AB();

		//contructor de copiere
        // complexitate: Theta(capacitate initiala)
		AB(const AB& ab);

		//creeaza un arbore binar care se reduce la o frunza
        // complexitate: Theta(capacitate initiala)
		AB(TElem elem);

		//constructor arbore binar
        // complexitate: Theta(n)
		AB(const AB& st, TElem elem, const AB& dr);

		//adauga unui arbore binar subarborele stang
		//arunca exceptie daca arborele este vid
        // complexitate: O(h)
		void adaugaSubSt(const AB& st);

		//adauga unui arbore binar subarborele drept
		//arunca exceptie daca arborele este vid
        // complexitate: O(ab.h)
		void adaugaSubDr(const AB& dr);

		//verifica daca arborele este vid
        // complexitate: Theta(1)
   		 bool vid() const;

		//accesare element din radacina
		//arunca exceptie daca arborele este vid
        // complexitate: Theta(1)
		TElem element() const;

		//accesare subarbore stang
		//arunca exceptie daca arborele este vid
        // complexitate: Theta(st.n)
		AB stang();

		//accesare subarbore drept
		//arunca exceptie daca arborele este vid
        // complexitate: Theta(dr.n)
		AB drept();

		//iteratori pe arborele binar (ordine="preordine", "postordine", "inordine", "latime")
		IteratorAB* iterator(string ordine) const;

		// destructorul arborelui binar
        // complexitate: Theta(1)
		~AB();
};



