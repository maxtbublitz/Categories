#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "hockey.hpp"

using namespace std;

int main(){
	YearTree T;
	int year = 2015;
	T.addYear(2015);

	T.readFile("2018.txt", year);
	T.printCategories(year);
	
	return 0;
}