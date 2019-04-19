#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "hockey.hpp"

using namespace std;

int main(){
	YearTree T;
	T.addYear(2017);
	T.addYear(2018);
	T.addYear(2015);
	T.addYear(2016);
	T.addYear(2014);
	T.addYear(2013);

	ofstream myfile;
	myfile.open("output.txt");

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

	T.readFile("2015.txt", 2015);
	T.readRecord("2015rec.txt", 2015);
	T.printAll(2015);

	T.readFile("2014.txt", 2014);
	T.readRecord("2014rec.txt", 2014);
	T.printAll(2014);

	T.readFile("2013.txt", 2013);
	T.readRecord("2013rec.txt", 2013);
	T.printAll(2013);

	T.getTotalRecord(2013, 2018);

	myfile.close();
	return 0;
}