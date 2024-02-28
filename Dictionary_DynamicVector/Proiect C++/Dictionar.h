#pragma once


#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>

typedef std::pair<TCheie, TValoare> TElem;

class Dictionar {
    friend class IteratorDictionar;

private:
    /* aici e reprezentarea -> doar specificarea argumentelor ce vor fi utilizate */

    // declaram un container sub forma unui vector dinamic
    // dinamicitatea: alocare dinamica + lungime modificabila in timp
    TElem *vec;

    /*
     * declaram capacitate + lungime - intregi
     * capacitate - cate elemente poate tine efectiv container-ul
     * lungime - cate elemente au fost introduse
    */
    int capacitate, lungime;

public:

    // constructorul implicit al dictionarului
    Dictionar();

    // adauga o pereche (cheie, valoare) in dictionar
    //daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
    // daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    TValoare adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    TValoare cauta(TCheie c) const;

    //sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    TValoare sterge(TCheie c);

    //redimensioneaza dictionarul
    void redim();

    //returneaza numarul de perechi (cheie, valoare) din dictionar
    int dim() const;

    //verifica daca dictionarul e vid
    bool vid() const;

    // se returneaza iterator pe dictionar
    IteratorDictionar iterator() const;


    // destructorul dictionarului
    ~Dictionar();

};


