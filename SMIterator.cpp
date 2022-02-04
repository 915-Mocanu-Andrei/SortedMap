#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//TODO - Implementation
	this->index = 0;
	this->maximum = m.nr_elems;
	this->array = new TElem[m.nr_elems];
	this->elems = m.elems;
	this->right = m.right;
	this->left = m.left;
	this->prev = m.prev;
	this->root = m.root;
	this->r = m.r;
	visit(this->root);
	//cout << "Array:";
	//for (int i = 0; i <= maximum;i++) {
	//	cout << this->array[i].first<<" ";
	//}
	//cout << '\n';
	this->index = 0;
}

void SMIterator::first(){
	//TODO - Implementation
	this->index = 0;
}

void SMIterator::next(){
	//TODO - Implementation
	if (!this->valid())
		throw exception();
	this->index++;
}

bool SMIterator::valid() const{
	//TODO - Implementation
	//if (this->maximum == 1) {
	//	return false;
	//}
	if (this->index < this->maximum) {
		return true;
	}
	return false;
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	if (!this->valid())
		throw exception();
	return this->array[this->index];
}

void SMIterator::visit(int node_index) {
	if (node_index == -1) {
		return;
	}
	if (this->r(1, 2) == true) {
		if (this->left[node_index] != -1)
			visit(this->left[node_index]);
		array[index] = this->elems[node_index];
		index++;
		if (this->right[node_index] != -1)
			visit(this->right[node_index]);
	}
	else {
		if (this->right[node_index] != -1)
			visit(this->right[node_index]);
		array[index] = this->elems[node_index];
		index++;
		if (this->left[node_index] != -1)
			visit(this->left[node_index]);
	}
}


