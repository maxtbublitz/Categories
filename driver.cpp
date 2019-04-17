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

	cout << endl;

	T.readFile("2018.txt", 2018);
	T.readRecord("2018rec.txt", 2018);
	T.printAll(2018);
	// cout << endl;
	T.readFile("2017.txt", 2017);
	T.readRecord("2017rec.txt", 2017);
	T.printAll(2017);
	// cout << endl;
	T.readFile("2016.txt", 2016);
	T.readRecord("2016rec.txt", 2016);
	T.printAll(2016);

	T.getTotalRecord(2016, 2018);

	
	return 0;
}