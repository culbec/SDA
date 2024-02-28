#include <cassert>

#include "LO.h"
#include "IteratorLO.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

// conditia care trebuie respectata
bool conditie(TElement e) {
    return e % 2 == 0;
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    IteratorLO itCauta = lo.cauta(1);
    assert(itCauta.valid());
    assert(itCauta.element() == 1);
    itCauta.urmator();
    assert(!itCauta.valid());
    itCauta.prim();
    assert(itCauta.valid());
    IteratorLO itPrim = lo.prim();
    assert(itPrim.valid());
    assert(itPrim.element() == 1);
    assert(lo.sterge(itCauta) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());

    // test pentru functia de filtrare

    lo.adauga(1);
    lo.adauga(2);
    lo.adauga(7);
    lo.adauga(8);
    lo.adauga(5);

    assert(!lo.vida());
    lo.filtreaza(conditie);
    assert(lo.dim() == 2);
}

