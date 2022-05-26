#include <iostream>
#include <fstream>
#include "storeinventory.h"
#include "hashtable.tpp"

#include<memory>

using namespace std;

int main() {

	/* Test HashTable */

	#if 0

	HashTable<int> ht(10); 
	ht.put("one", 1);
	ht.put("two", 2);
	ht.put("three", 3);
	ht.put("one", 4);
	for(auto val : ht.get("one")) {
		cout << val << endl;
	}
	int a = 1;
	ht.remove("two");
	ht.remove("one", a);
	ht.returnAll();

	#endif

	/* Test StoreInventory */

	#if 1

    ifstream customers("data4customers.txt");
	if (!customers) {
		cout << "File could not be opened." << endl;
		return 1;
	}
    ifstream movies("data4movies.txt");
	if (!movies) {
		cout << "File could not be opened." << endl;
		return 1;
	}
    ifstream commands("data4commands.txt");
	if (!commands) {
		cout << "File could not be opened." << endl;
		return 1;
	}

    StoreInventory inv(customers, movies);

	std::cout << inv << std::endl;

	#endif

}
