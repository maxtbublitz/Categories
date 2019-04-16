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
	float gf = 2;
	float ga = 2;
	string name = "VAN";
	string nam = "BOS";
	T.createTeamNode(name, gf, ga, year);
	T.createTeamNode(nam, gf, ga, year);
	T.printCategories(year);
	
	return 0;
}