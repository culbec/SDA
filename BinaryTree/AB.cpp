#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

void AB::redim() {
    this->cp = 2 * this->cp;
    Node *newTree = new Node[this->cp];
    int *newSpatiuLiber = new int[this->cp];

    for (int i = 0; i < this->size; i++) {
        newTree[i] = this->tree[i];
    }

    for (int i = 0; i < this->size; i++) {
        newSpatiuLiber[i] = this->spatiuLiber[i];
    }

    for (int i = this->size; i < this->cp - 1; i++) {
        newSpatiuLiber[i] = i + 1;
    }

    newSpatiuLiber[this->cp - 1] = -1;

    this->primLiber = this->size;

    delete[] this->tree;
    this->tree = newTree;

    delete[] this->spatiuLiber;
    this->spatiuLiber = newSpatiuLiber;
}

Node AB::copiere(Node *_tree, const Node& node) {
    if (node.pozitie == -1) {
        return {};
    }

    if (this->primLiber == -1) {
        this->redim();
    }

    int _pos = this->primLiber;
    this->primLiber = this->spatiuLiber[this->primLiber];
    this->size++;

    Node leftChild, rightChild;

    if(_tree[node.pozitie].left != -1) {
        leftChild = this->copiere(_tree, _tree[_tree[node.pozitie].left]);
    }

    if(_tree[node.pozitie].right != -1) {
        rightChild = this->copiere(_tree, _tree[_tree[node.pozitie].right]);
    }

    this->tree[_pos] = Node{node.data, _pos,
                            leftChild.pozitie,
                            rightChild.pozitie};
    return this->tree[_pos];

}

void AB::distruge(Node *_tree, const Node &node) {
    if (node.left == -1 && node.right == -1) {
        return;
    }

    if (_tree[node.left].pozitie != -1) {
        int oldPrimLiber = this->primLiber;
        this->primLiber = _tree[node.left].pozitie;
        this->spatiuLiber[this->primLiber] = oldPrimLiber;
        this->distruge(_tree, _tree[node.left]);
        this->size--;
        _tree[node.left] = Node();
    }

    if (_tree[node.right].pozitie != -1) {
        int oldPrimLiber = this->primLiber;
        this->primLiber = _tree[node.right].pozitie;
        this->spatiuLiber[this->primLiber] = oldPrimLiber;
        this->distruge(_tree, _tree[node.right]);
        this->size--;
        _tree[node.right] = Node();
    }
    _tree[node.pozitie] = Node();
    this->size--;
}

Node AB::adaugare(AB &_ab, Node* _tree, const Node &node) {
    if(_ab.primLiber == -1) {
        _ab.redim();
    }

    if(node.pozitie == -1) {
        return {};
    }

    int pos = _ab.primLiber;
    _ab.primLiber = _ab.spatiuLiber[_ab.primLiber];
    _ab.size++;

    Node leftChild, rightChild;

    if(_tree[pos].left != -1) {
        leftChild = _ab.adaugare(_ab, _tree, _tree[_tree[pos].left]);
    }

    if(_tree[pos].right != -1) {
        rightChild = _ab.adaugare(_ab, _tree, _tree[_tree[pos].right]);
    }

    _ab.tree[pos] = Node{node.data, node.pozitie, leftChild.pozitie, rightChild.pozitie};
    return _ab.tree[pos];
}

AB::AB() {
    // Complexitate: Theta(1)
    this->size = 0; // arborele este gol
    this->cp = 2; // capacitatea initiala

    this->root = Node();
    this->tree = new Node[this->cp];
    this->spatiuLiber = new int[this->cp];
    this->primLiber = 0; // accesul va fi, initial, secvential

    // alocarea spatiului liber
    for (int i = 0; i < this->cp - 1; i++) {
        this->spatiuLiber[i] = i + 1;
    }

    this->spatiuLiber[this->cp - 1] = -1;

}

AB::AB(const AB &ab) {
    // constructor de copiere
    // Complexitate: Theta(n);

    // copiem atributele default ale unui arbore
    this->cp = ab.cp;
    this->size = ab.size;
    this->root = ab.root;
    this->primLiber = ab.primLiber;

    // initializam arborele
    this->tree = new Node[this->cp];
    this->spatiuLiber = new int[this->cp];

    for (int i = 0; i < this->cp; i++) {
        this->tree[i] = ab.tree[i]; // pur si simplu copiem content-ul
    }

    // realocarea spatiului liber

    for (int i = 0; i < this->size; i++) {
        this->spatiuLiber[i] = ab.spatiuLiber[i];
    }

    for (int i = this->size; i < this->cp - 1; i++) {
        this->spatiuLiber[i] = i + 1;
    }

    this->spatiuLiber[this->cp - 1] = -1;
}

AB::AB(TElem e) {
    this->cp = 2;
    this->size = 1;
    this->primLiber = 1;

    this->root = Node{e, this->primLiber - 1, -1, -1};
    this->tree = new Node[this->cp];
    this->tree[0] = this->root;

    this->spatiuLiber = new int[this->cp];
    for (int i = 0; i < this->cp; i++) {
        this->spatiuLiber[i] = -1;
    }
}

AB::AB(const AB &st, TElem e, const AB &dr) {
    this->cp = 2;
    this->size = 0;
    this->primLiber = 0;

    this->tree = new Node[this->cp];
    this->spatiuLiber = new int[this->cp];

    for (int i = 0; i < this->cp - 1; i++)
        this->spatiuLiber[i] = i + 1;
    this->spatiuLiber[this->cp - 1] = -1;

    Node leftChild = this->copiere(st.tree, st.root);
    Node rightChild = this->copiere(dr.tree, dr.root);

    if(this->primLiber == -1) {
        this->redim();
    }

    this->root = Node{e, this->primLiber, leftChild.pozitie, rightChild.pozitie};
    this->primLiber = this->spatiuLiber[this->primLiber];
    this->size++;

    this->tree[root.pozitie] = root;
}

void AB::adaugaSubSt(const AB &st) {
    if (this->vid()) {
        throw std::exception();
    }

    if (root.left != -1) {
        distruge(this->tree, this->tree[this->root.left]);
    }

    if(st.root.pozitie != -1) {
        Node leftRoot = this->copiere(st.tree, st.root);
        this->tree[root.pozitie].left = leftRoot.pozitie;
        root.left = leftRoot.pozitie;
    } else {
        this->tree[root.pozitie].left = -1;
        root.left = -1;
    }
}

void AB::adaugaSubDr(const AB &dr) {
    if (this->vid()) {
        throw std::exception();
    }

    if (root.right != -1) {
        distruge(this->tree, this->tree[this->root.right]);
    }
    if(dr.root.pozitie != -1) {
        Node rightRoot = this->copiere(dr.tree, dr.root);
        this->tree[root.pozitie].right = rightRoot.pozitie;
        root.right = rightRoot.pozitie;
    } else {
        this->tree[root.pozitie].right = -1;
        root.right = -1;
    }
}

TElem AB::element() const {
    if (this->vid()) {
        throw std::exception();
    }

    return this->root.data;
}

AB AB::stang() {
    if (this->vid()) {
        throw std::exception();
    }

    if(this->root.left != -1) {
        AB ab; // arborele nou
        ab.root = ab.adaugare(ab, this->tree, this->tree[root.left]);
        return ab;
    }

    return {};
}

AB AB::drept() {
    if (this->vid()) {
        throw std::exception();
    }

    if (this->root.right != -1) {
        AB ab;
        ab.root = ab.adaugare(ab, this->tree, this->tree[root.right]);
        return ab;
    }

    return {};
}

AB::~AB() {
    delete[] this->tree;
    delete[] this->spatiuLiber;
}

bool AB::vid() const {
    if (this->root.pozitie == -1) { return true; }
    return false;
}


IteratorAB *AB::iterator(string s) const {
    if (s == "preordine")
        return new IteratorPreordine(*this);
    if (s == "inordine")
        return new IteratorInordine(*this);
    if (s == "postordine")
        return new IteratorPostordine(*this);
    if (s == "latime")
        return new IteratorLatime(*this);
    return nullptr;
};
