#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	//TODO - Representation
	int index;
	int maximum;
	TElem* array;
	void visit(int node_index);
	TElem* elems;
	int* left;
	int* right;
	int* prev;
	int root;
	Relation r;
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

