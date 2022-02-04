#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"

#include <assert.h>
#include <iostream>
using namespace std;

bool relu(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	cout << "Test Get Range" << endl;
	SortedMap sm(relu);
	sm.add(2, 2);
	sm.add(5, 2);
	sm.add(0, 2);
	sm.add(8, 2);
	sm.add(1, 2);

	sm.add(9, 2);
	sm.add(24, 2);
	sm.add(3, 2);
	sm.add(4, 2);
	assert(sm.getRange() == 24);

	SortedMap sm2(relu);
	assert(sm2.getRange() == -1);
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


