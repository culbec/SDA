#include "AB.h"
#include "IteratorAB.h"

void IteratorInordine::adaugaRec(const Node& node) {
    Node _root = node;

    if(_root.pozitie == -1) {
        return;
    }

    if(_root.right != -1) {
        this->adaugaRec(this->ab.tree[_root.right]);
    }

    this->nodes.push(_root);

    if(_root.left != -1) {
        this->adaugaRec(this->ab.tree[_root.left]);
    }
}

IteratorInordine::IteratorInordine(const AB& _ab):ab(_ab) {
	this->adaugaRec(_ab.root);
}

void IteratorInordine::prim(){
	while(!this->nodes.empty()) {
        this->nodes.pop();
    }

    this->adaugaRec(this->ab.root);
}

bool IteratorInordine::valid(){
	if(this->nodes.empty())
	    return false;
    return true;
}

TElem IteratorInordine::element() {
	if(!this->valid())
        throw std::exception();

	return this->nodes.top().data;
}

void IteratorInordine::urmator(){
	if(!this->valid())
        throw std::exception();

    this->nodes.pop();
}

void IteratorPreordine::adaugaRec(const Node &node) {
    Node _root = node;

    if(_root.pozitie == -1) {
        return;
    }

    if(_root.right != -1) {
        this->adaugaRec(this->ab.tree[_root.right]);
    }

    if(_root.left != -1) {
        this->adaugaRec(this->ab.tree[_root.left]);
    }

    this->nodes.push(_root);
}

IteratorPreordine::IteratorPreordine(const AB& _ab):ab(_ab){
	this->adaugaRec(ab.root);
}

void IteratorPreordine::prim(){
 	while(!this->nodes.empty()) {
         this->nodes.pop();
     }

     this->adaugaRec(this->ab.root);
}


bool IteratorPreordine::valid(){
	if(this->nodes.empty()) {
        return false;
    }
    return true;
}

TElem IteratorPreordine::element(){
	if(!this->valid()) {
        throw std::exception();
    }

    Node node = this->nodes.top();
    return node.data;
}

void IteratorPreordine::urmator(){
	if(!this->valid()) {
        throw std::exception();
    }

    this->nodes.pop();
}

void IteratorPostordine::adaugaRec(const Node &node) {
    Node _root = node;

    if(_root.pozitie == -1) {
        return;
    }

    this->nodes.push(_root);

    if(_root.right != -1) {
        this->adaugaRec(this->ab.tree[_root.right]);
    }

    if(_root.left != -1) {
        this->adaugaRec(this->ab.tree[_root.left]);
    }
}

IteratorPostordine::IteratorPostordine(const AB& _ab):ab(_ab){
	this->adaugaRec(ab.root);
}

void IteratorPostordine::prim(){
	while(!this->nodes.empty()) {
        this->nodes.pop();
    }

    this->adaugaRec(this->ab.root);
}


bool IteratorPostordine::valid(){
    if(this->nodes.empty()) {
        return false;
    }
    return true;
}

TElem IteratorPostordine::element(){
 	if(!this->valid()) {
         throw std::exception();
     }
	return this->nodes.top().data;
}

void IteratorPostordine::urmator(){
	if(!this->valid()) {
        throw std::exception();
    }
    this->nodes.pop();
}

void IteratorLatime::adaugaRec(const Node &node) {
    Node _root = node;

    if(_root.pozitie == -1) {
        return;
    }

    std::queue<Node> queue;
    queue.push(_root);

    while(!queue.empty()) {
        Node current = queue.front();
        queue.pop();
        this->nodes.push_back(current);

        if(current.left != -1) {
            queue.push(this->ab.tree[current.left]);
        }
        if(current.right != -1) {
            queue.push(this->ab.tree[current.right]);
        }
    }
}

IteratorLatime::IteratorLatime(const AB& _ab):ab(_ab){
	this->adaugaRec(ab.root);
}

void IteratorLatime::prim(){
	while(!this->nodes.empty()) {
        this->nodes.pop_front();
    }
    this->adaugaRec(this->ab.root);
}


bool IteratorLatime::valid(){
	if(this->nodes.empty()) {
        return false;
    }
    return true;
}

TElem IteratorLatime::element(){
	if(!this->valid()) {
        throw std::exception();
    }
	return this->nodes.front().data;
}

void IteratorLatime::urmator(){
	if(!this->valid()) {
        throw std::exception();
    }
    this->nodes.pop_front();
}
