#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "hockey.hpp"

using namespace std;

int main(){
	YearTree T;
	T.addYear(2018);
	T.addYear(2017);
	T.addYear(2016);

	T.readFile("2018.txt", 2018);
	T.readRecord("2018rec.txt", 2018);
	T.printCategories(2018);
	T.printRecord(2018);
	cout << endl;
	// T.readFile("2017.txt", 2017);
	// T.printCategories(2017);
	// cout << endl;
	// T.readFile("2016.txt", 2016);
	// T.printCategories(2016);

	
	return 0;
}