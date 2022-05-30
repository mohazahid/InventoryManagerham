#include <iostream>
#include <fstream>
#include "storeinventory.h"
#include "hashtable.tpp"

#include<memory>
#include  "classic.h"
using namespace std;
#include<iostream>
#include<vector>
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
	//int stock, std::string director, std::string title, int year, 
    //std::string firstName, std::string lastName, int month)
	// Classic movie3(10, "hayden abhi", "mohammd is the best", 2020,"abhimanyu","kumar",9);
	// Classic movie2(10, "abhi hayden", "your trash", 2021,"Hayden","Lauritzen",7);
	// Classic movie1(10, "mohammad abhi", "I am the greatest", 2022, "Mohammad","Zahid",8);
	// Comedy movie3(10, "hayden abhi", "mohammd is the best", 2020);
	// Comedy movie2(10, "abhi hayden", "your trash", 2021);
	// Comedy movie1(10, "mohammad abhi", "I am the greatest", 2022);
	// Comedy movie4(10, "hayden abhi", "mohammde is the best", 1999);
	// Comedy movie5(10, "abhi hayden", "your etrash", 1973);
	// Comedy movie6(10, "mohammad abhi", "I ame the greatest", 1983);
	// std::vector<Movie> classics;
	// classics.push_back(dynamic_cast<Comedy *>(&movie1));
	// classics.push_back(dynamic_cast<Comedy *>(&movie2));
	// classics.push_back(dynamic_cast<Comedy *>(&movie3));
	// classics.push_back(dynamic_cast<Comedy *>(&movie4));
	// classics.push_back(dynamic_cast<Comedy *>(&movie5));
	// classics.push_back(dynamic_cast<Comedy *>(&movie6));
	// sort(classics.begin(), classics.end());
   	// for(int i=0; i < classics.size(); i++) {
   	// 	cout << classics.at(i) << ' ';
	// }
    // if(movie3 < movie2) {
	// 	cout << "it failed \n";
	// } else {
	// 	cout <<"it worked \n";
	// }
	StoreInventory inv(customers, movies);

	std::cout << inv << std::endl;

	#endif

}
