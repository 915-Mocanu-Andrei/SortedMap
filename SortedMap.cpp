#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->r = r;
	//
	this->elems = new TElem[10];//[1000000];
	this->left = new int[10];
	this->right = new int[10];
	this->prev = new int[10];
	this->capacity = 10;
	this->first_empty = 0;
	this->root = 0;
	//this->tail = 0;
	//
	this->left[0] = -1;
	this->right[0] = -1;
	this->prev[0] = -1;
	this->nr_elems = 0;
	//
	this->elems[0].first = -102;
	this->elems[0].first = -102;
	//TODO - Implementation
}

TValue SortedMap::add(TKey k, TValue v) {
	if (this->first_empty == this->capacity - 2) {
		this->elems = this->resize_array(this->elems, this->capacity);
		this->left = this->resize_array(this->left, this->capacity);
		this->right = this->resize_array(this->right, this->capacity);
		this->prev = this->resize_array(this->prev, this->capacity);
		this->capacity = this->capacity * 2;
	}
	if (this->isEmpty()) {
		this->nr_elems++;
		TElem elem;
		elem = TElem(k, v);
		this->elems[this->first_empty] = elem;
		this->left[this->first_empty] = -1;
		this->right[this->first_empty] = -1;
		//this->prev[this->first_empty] = this->tail;
		//if (this->nr_elems != 1)
		//	this->next[this->tail] = this->first_empty;
		//this->tail = this->first_empty;
		this->root = this->first_empty;
		this->first_empty++;
		return NULL_TVALUE;
	}

	//TODO - Implementation
	int index = this->root;
	TElem current = this->elems[index];
	int found = 1;
	while (current.first != k) {
		if (k < current.first) {
			if (this->left[index] != -1) {
				index = this->left[index];
			}
			else {
				this->left[index] = this->first_empty;
				found = 0;
				break;
			}
		}
		if (k > current.first) {
			if (this->right[index] != -1) {
				index = this->right[index];
			}
			else {
				this->right[index] = this->first_empty;
				found = 0;
				break;
			}
		}
		current = this->elems[index];
	}
	if (found == 0) {
		this->nr_elems++;
		TElem elem;
		elem = TElem(k, v);
		this->elems[this->first_empty] = elem;
		this->left[this->first_empty] = -1;
		this->right[this->first_empty] = -1;
		this->prev[this->first_empty] = index;
		this->first_empty++;
		return NULL_TVALUE;
	}
	if (found == 1) {
		//i can use the idex
		auto old_value = this->elems[index].second;
		this->elems[index].second = v;
		return old_value;
	}
	return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
	int index = this->root;
	TElem current = this->elems[index];
	int found = 1;
	if (this->root == -1) {
		return NULL_TVALUE;
	}
	while (current.first != k) {
		if (k < current.first) {
			if (this->left[index] != -1) {
				index = this->left[index];
			}
			else {
				return NULL_TVALUE;
			}
		}
		if (k > current.first) {
			if (this->right[index] != -1) {
				index = this->right[index];
			}
			else {
				return NULL_TVALUE;
			}
		}
		current = this->elems[index];
	}
	return current.second;
	//TODO - Implementation
}

TValue SortedMap::remove(TKey k) {
	//TODO - Implementation
	int index = this->root;
	TElem current = this->elems[index];
	int found = 1;
	
	//ROOT
	if (current.first == k && this->nr_elems == 1)
	{
		this->nr_elems = 0;
		this->root = -1;
		return current.second;
	}
	if (current.first == k && this->nr_elems!=1) {
		//std::cout << "ROOT";
		if (this->left[index] == -1 || this->right[index] == -1) {
			if (this->right[index] != -1) {// with the right node
				this->root = this->right[index];
			}
			if (this->left[index] != -1) {// with the left node
				this->root = this->left[index];
			}
			this->nr_elems--;
			return current.second;
		}
	}
	//ROOT
	while (current.first != k) {
		if (k < current.first) {
			if (this->left[index] != -1) {
				index = this->left[index];

			}
			else {
				return NULL_TVALUE;
			}
		}
		if (k > current.first) {
			if (this->right[index] != -1) {
				index = this->right[index];
			}
			else {
				return NULL_TVALUE;
			}
		}
		current = this->elems[index];
	}
	this->nr_elems--;
	if (this->left[index] == -1 && this->right[index] == -1) {
		if (index == this->root) {
			this->root = -1;
		}
		if (this->right[this->prev[index]] == index) {
			this->right[this->prev[index]] = -1;
			//this->nr_elems--;
		}
		if (this->left[this->prev[index]] == index) {
			this->left[this->prev[index]] = -1;
			//this->nr_elems--;
		}
		return current.second;
	}
	else if (this->left[index] == -1 || this->right[index] == -1) {

		if (this->right[this->prev[index]] == index){ // i need to replace the right node
			if (this->root == index) {
				this->root = this->right[index];
			}
			if (this->right[index] != -1) {// with the right node
				this->right[this->prev[index]] = this->right[index];
				this->prev[this->right[index]] = this->prev[index];
				//this->nr_elems--;
				
			}
			if (this->left[index] != -1) {// with the left node
				this->right[this->prev[index]] = this->left[index];
				this->prev[this->left[index]] = this->prev[index];
				//this->nr_elems--;
			}
		}
		if (this->left[this->prev[index]] == index) { // i need to replace the left node
			if (this->root == index) {
				this->root = this->left[index];
			}
			if (this->right[index] != -1) {// with the right node
				this->left[this->prev[index]] = this->right[index];
				this->prev[this->right[index]] = this->prev[index];
				//this->nr_elems--;
			}
			if (this->left[index] != -1) {// with the left node
				this->left[this->prev[index]] = this->left[index];
				this->prev[this->left[index]] = this->prev[index];
				//this->nr_elems--;
			}
		}
		return current.second;
	}
	//if the function got here then the node it needs to remove has both a left and a right subtree
	//Find the maximum of the left subtree, move it to the node to
	//be deleted, and delete the maximum
	int node_to_be_deleted_index = index;
	current = this->elems[this->left[index]];
	TValue returner = this->elems[node_to_be_deleted_index].second;
	while (true) {
		if (this->right[index] != -1) {
				index = this->right[index];
			}
			else {
				//found the maximum
				// I Part
				this->elems[node_to_be_deleted_index] = this->elems[index];
				// II Part
				this->right[this->prev[index]] = this->left[index];
				this->prev[this->left[index]] = this->prev[index];
				return returner;
			}
		current = this->elems[index];
	}
	return returner;
	//TODO - Implementation
}

int SortedMap::size() const {
	//TODO - Implementation
	return this->nr_elems;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	if (this->nr_elems == 0)
		return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//TODO - Implementation
}

TElem* SortedMap::resize_array(TElem* arr, int size_arr) {
	TElem* new_arr;
	int new_size = 2 * size_arr;
	new_arr = new TElem[new_size];
	for (int i = 0; i <= size_arr; i++) {
		new_arr[i] = arr[i];
	}
	delete[] arr;
	return new_arr;
}

int* SortedMap::resize_array(int* arr, int size_arr) {
	int* new_arr;
	int new_size = 2 * size_arr;
	new_arr = new int[new_size];
	for (int i = 0; i <= size_arr; i++) {
		new_arr[i] = arr[i];
	}
	return new_arr;
}

int SortedMap::getRange() const {
	if (this->isEmpty()) {
		return -1;
	}
	int k1 = this->root;
	int k2 = this->root;
	TElem current = this->elems[k1];
	if (this->root == -1) {
		return NULL_TVALUE;
	}
	while (true) {
		if (this->left[k1] != -1) {
			k1 = this->left[k1];
			current = this->elems[k1];
		}
		else {
			break;
		}
		
	}
	current = this->elems[k2];
	while (true) {
		if (this->right[k2] != -1) {
			k2 = this->right[k2];
			current = this->elems[k2];
		}
		else {
			break;
		}
	}
	int output;
	output = this->elems[k1].first - this->elems[k2].first;
	if (output < 0) {
		return output * -1;
	}
	return output;
}
