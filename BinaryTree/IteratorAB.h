#pragma once
#include "AB.h"
#include <stack>
#include <queue>
#include <deque>

class IteratorAB {
public:

	friend class AB;

	//operatii pe iterator
	virtual void prim()=0;

	virtual void urmator()=0;

	virtual TElem element() = 0;

	virtual bool valid() = 0;

    // pentru adaugarea recursiva a nodurilor in iteratoare
    virtual void adaugaRec(const Node& node) = 0;
};

class IteratorPreordine: public IteratorAB{
    friend class AB;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorPreordine(const AB& _ab);

	//contine o referinta catre containerul pe care il itereaza

   	const AB& ab;
	std::stack<Node> nodes;

public:
		//reseteaza pozitia iteratorului la inceputul containerului
        // complexitate: Theta(n)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
        // complexitate: Theta(1)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		TElem element();

        // complexitate: Theta(n)
        void adaugaRec(const Node& node);
};


#include <exception>
class IteratorInordine: public IteratorAB{
   friend class AB;
private:
  //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
   IteratorInordine(const AB& _ab);

  //contine o referinta catre containerul pe care il itereaza

   const AB& ab;
   /* aici e reprezentarea specifica a iteratorului*/
   std::stack<Node> nodes;


public:
		//reseteaza pozitia iteratorului la inceputul containerului
        // complexitate: Theta(n)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
        // complexitate: Theta(1)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		TElem element();

        // complexitate: Theta(n)
        void adaugaRec(const Node& node);
};


class IteratorPostordine: public IteratorAB{
   friend class AB;
private:

    //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
  	IteratorPostordine(const AB& _ab);
    //contine o referinta catre containerul pe care il itereaza

	const AB& ab;
	/* aici e reprezentarea specifica a itertorului*/
    std::stack<Node> nodes;

public:
		//reseteaza pozitia iteratorului la inceputul containerului
        // complexitate: Theta(n)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
        // complexitate: Theta(1)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		TElem element();

        // complexitate: Theta(n)
        void adaugaRec(const Node& node);
};

class IteratorLatime: public IteratorAB{
   friend class AB;
private:

   //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
   IteratorLatime(const AB& _ab);
   //contine o referinta catre containerul pe care il itereaza

   const AB& ab;
 	/* aici e reprezentarea pecifica a itratorului*/
    std::deque<Node> nodes;


public:
		//reseteaza pozitia iteratorului la inceputul containerului
        // complexitate: Theta(n)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
        // complexitate: Theta(1)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
        // complexitate: Theta(1)
		TElem element();

        // complexitate: Theta(n)
        void adaugaRec(const Node& node);
};
