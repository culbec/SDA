#pragma once

typedef int TElem;

#define NULL_TELEMENT (-1)

// nodul ce va constitui un element in tabela
struct Node {
    // pozitia in matrice -> linie + coloana
    int linie, coloana;
    // valoarea elementului
    TElem valoare;
    // referinta catre urmatorul element
    Node* next;
};

class Matrice {

private:
	// reprezentare sub forma unei matrici rare
    // Node = (linie, coloana, valoare) ; valoare != 0
    // tabela de dispersie prin liste independente

    // avem un nr. de chei fixat ce pot fi acoperite in tabela
    int nrChei;
    int linii, coloane; // nr. de linii si coloane ale matricii

    // tabela propriu zisa
    Node** TD;

    // functia de dispersie
    // complexitate: Theta(1)
    int hash(int linie, int coloana) const;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    // complexitate: Theta(1)
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
    // complexitate: O(nrChei) -> daca toate cheile de disperseaza in acelasi loc
	TElem element(int i, int j) const;


	// returnare numar linii
    // complexitate: Theta(1)
	int nrLinii() const;

	// returnare numar coloane
    // complexitate: Theta(1)
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    // complexitate:
    /*
     * WORST CASE: O(nrChei) -> daca toate cheile de disperseaza in acelasi loc
     * AVERAGE CASE: Theta(1)
     */
	TElem modifica(int i, int j, TElem);

};







