#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "hockey.hpp"

using namespace std;

int getHash(int gf, int ga){
	if(gf >= 2.8){ // team has above average offense and
		if(ga <= 2.8){ // above average defense
			return 0;
		}
		else{ // below average defense
			return 1;
		}
	}
	else{ // team has below average offense and
		if(ga <= 2.8){ // above average defense
			return 2;
		}
		else{ // below average defense
			return 3;
		}
	}
}

/*
FILENAME STUCTURE:
Rank, Name, Average Age, Games Played, Wins, Losses, OT Losses, Points, Point%, GF, GA, 22 more items
Seperated by commas
*/

void YearTree::readFile(string filename, int y){
	YearNode* node = searchYear(y);
	ifstream ifs(filename);
	if(ifs.is_open()){
		string line;
		while(getline(ifs, line)){
			vector <string> tokens; // create a vector of strings 
			stringstream check1(line); 
			string intermediate; 
			int count = 0; // initialize count to 0
			while(getline(check1, intermediate, ',')){
				tokens.push_back(intermediate); // add new string to the vector
				count++; // keep track of count to access that element in the vector
			}
			// cout << tokens[1] << " " << tokens[9] << " " << tokens[10] << endl;
			string nm = tokens[1];
			float gf60 = stof(tokens[9])/stof(tokens[3]);
			float ga60 = stof(tokens[10])/stof(tokens[3]);
			nm.erase(remove(nm.begin(), nm.end(), '*'), nm.end());
			nm = getTeamAbrv(nm);
			createTeamNode(nm, gf60, ga60, y);
		}
	}
}

//***********************************************************************************//
//******************************YEAR TREE IMPLEMENTATION*****************************//
//***********************************************************************************//

YearTree::YearTree(){ root = 0; }

YearTree::~YearTree(){ }

YearNode* YearTree::createYearNode(int y){
	// Tree
	YearNode* newNode = new YearNode;
	newNode->year = y;
	newNode->left = NULL;
	newNode->right = NULL;
	// Hash Table
	newNode->table = new TeamNode*[4];
	for(int i = 0; i < 4; i++){
		newNode->table[i] = NULL;
	}
	return newNode;
}

YearNode* YearTree::addYearHelper(YearNode* n, int y){
	if(root == NULL){
		root = createYearNode(y);
		return root;
	}
	if(n == NULL){
		return createYearNode(y);
	}
	else if(y < n->year){
		n->left = addYearHelper(n->left, y);
	}
	else if(y > n->year){
		n->right = addYearHelper(n->right, y);
	}
	return n;
}

void YearTree::addYear(int y){
	addYearHelper(root, y);
}

YearNode* searchYearHelper(YearNode* n, int y){
	if(n == 0){
		return NULL;
	}
	else{
		if(n->year == y){
			return n;
		}
		else{
			if(n->year > y){
				return searchYearHelper(n->left, y);
			}
			else{
				return searchYearHelper(n->right, y);
			}
		}
	}
}

YearNode* YearTree::searchYear(int y){
	YearNode* n = searchYearHelper(root, y);
	return n;
}

void YearTree::printCategories(int y){
	YearNode* n = searchYear(y);
	cout << "----------" << "-----------------------------" << "----------" << endl;
	cout << "--------- " << "Printing Cateogories For " << y << " ---------" << endl;
	cout << "----------" << "-----------------------------" << "----------" << endl;
	for(int i = 0; i < 4; i++){
		cout << "Category " << i+1 << ":" << endl;
		TeamNode* team = n->table[i];
		while(team != NULL){
			cout << team->name << " ";
			team = team->next;
		}
		cout << endl;
	}
}



TeamNode* createNodeHelper(string name, float gf, float ga){
	TeamNode* newNode = new TeamNode;
	newNode->name = name;
	newNode->goalsFor = gf;
	newNode->goalsAgainst = ga;
	newNode->next = NULL;
	return newNode;
}

void YearTree::createTeamNode(string nm, float gf60, float ga60, int year){
	
	YearNode* y = searchYear(year); // find year
	int index = getHash(gf60, ga60); // get index

	TeamNode* addNode = createNodeHelper(nm, gf60, ga60);

	TeamNode* temp = y->table[index];
	TeamNode* prev = NULL;
	if(temp == NULL){
		y->table[index] = addNode;
		// cout << "Adding " << addNode->name << endl;
		return;

	}
	while(temp != NULL){
		prev = temp;
		temp = temp->next;
	}
	prev->next = addNode;
	// cout << "Adding " << addNode->name << endl;
	return;
}

//***********************************************************************************//
//**********************************OTHER FUNCTIONS**********************************//
//***********************************************************************************//


string getTeamAbrv(string name){
	if(name == "Anaheim Ducks"){
		return "ANA";
	}
	if(name == "Arizona Coyotes"){
		return "ARI";
	}
	if(name == "Boston Bruins"){
		return "BOS";
	}
	if(name == "Buffalo Sabres"){
		return "BUF";
	}
	if(name == "Calgary Flames"){
		return "CGY";
	}
	if(name == "Carolina Hurricanes"){
		return "CAR";
	}
	if(name == "Chicago Blackhawks"){
		return "CHI";
	}
	if(name == "Colorado Avalanche"){
		return "COL";
	}
	if(name == "Columbus Blue Jackets"){
		return "CBJ";
	}
	if(name == "Dallas Stars"){
		return "DAL";
	}
	if(name == "Detroit Red Wings"){
		return "DET";
	}
	if(name == "Edmonton Oilers"){
		return "EDM";
	}
	if(name == "Florida Panthers"){
		return "FLA";
	}
	if(name == "Los Angeles Kings"){
		return "LAK";
	}
	if(name == "Minnesota Wild"){
		return "MIN";
	}
	if(name == "Montreal Canadiens"){
		return "MTL";
	}
	if(name == "Nashville Predators"){
		return "NSH";
	}
	if(name == "New Jersey Devils"){
		return "NJD";
	}
	if(name == "New York Islanders"){
		return "NYI";
	}
	if(name == "New York Rangers"){
		return "NYR";
	}
	if(name == "Ottawa Senators"){
		return "OTT";
	}
	if(name == "Philadelphia Flyers"){
		return "PHI";
	}
	if(name == "Pittsburgh Penguins"){
		return "PIT";
	}
	if(name == "San Jose Sharks"){
		return "SJS";
	}
	if(name == "St. Louis Blues"){
		return "STL";
	}
	if(name == "Tampa Bay Lightning"){
		return "TBL";
	}
	if(name == "Toronto Maple Leafs"){
		return "TOR";
	}
	if(name == "Vancouver Canucks"){
		return "VAN";
	}
	if(name == "Vegas Golden Knights"){
		return "VGK";
	}
	if(name == "Washington Capitals"){
		return "WSH";
	}
	if(name == "Winnipeg Jets"){
		return "WPG";
	}
	cout << name << " not found" << endl;
	return "NA";
}