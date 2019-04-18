#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "hockey.hpp"

using namespace std;

int getHash(float gf, float ga){
	if(gf >= 2.73){ // team has above average offense and
		if(ga <= 2.73){ // above average defense
			return 0;
		}
		else{ // below average defense
			return 1;
		}
	}
	else{ // team has below average offense and
		if(ga <= 2.73){ // above average defense
			return 2;
		}
		else{ // below average defense
			return 3;
		}
	}
}

//***********************************************************************************//
//******************************YEAR TREE IMPLEMENTATION*****************************//
//***********************************************************************************//

YearTree::YearTree(){ root = 0; }

YearTree::~YearTree(){ }

TeamNode* createNodeHelper(string name, float gf, float ga){
	TeamNode* newNode = new TeamNode;
	newNode->name = name;
	newNode->goalsFor = gf;
	newNode->goalsAgainst = ga;
	newNode->next = NULL;
	return newNode;
}

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

	newNode->hist.r1v2 = 0;
	newNode->hist.r1v3 = 0;
	newNode->hist.r1v4 = 0;
	newNode->hist.r2v1 = 0;
	newNode->hist.r2v3 = 0;
	newNode->hist.r2v4 = 0;
	newNode->hist.r3v1 = 0;
	newNode->hist.r3v2 = 0;
	newNode->hist.r3v4 = 0;
	newNode->hist.r4v1 = 0;
	newNode->hist.r4v2 = 0;
	newNode->hist.r4v3 = 0;
	newNode->hist.r1v2p = 0;
	newNode->hist.r1v3p = 0;
	newNode->hist.r1v4p = 0;
	newNode->hist.r2v1p = 0;
	newNode->hist.r2v3p = 0;
	newNode->hist.r2v4p = 0;
	newNode->hist.r3v1p = 0;
	newNode->hist.r3v2p = 0;
	newNode->hist.r3v4p = 0;
	newNode->hist.r4v1p = 0;
	newNode->hist.r4v2p = 0;
	newNode->hist.r4v3p = 0;

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

int YearTree::searchTeam(string name, int y){ // returns teams category number 
	YearNode* year = searchYear(y);
	for(int i = 0; i < 4; i++){
		TeamNode* temp = year->table[i];
		while(temp != NULL){
			if(name == temp->name){
				return i+1;
			}
			else{
				temp = temp->next;
			}
		}
	}
	return 0;
}

void YearTree::printCategories(int y){
	YearNode* n = searchYear(y);
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
	if(nm < temp->name){ // case 1: less than head of linked list
		prev = temp;
		y->table[index] = addNode;
		addNode->next = prev;
		return;
	}
	else{
		prev = temp;
		temp = temp->next;
	}
	while(temp != NULL){
		if(nm < temp->name){
			prev->next = addNode;
			addNode->next = temp;
			return;
		}
		else{
			prev = temp;
			temp = temp->next;
		}
	}
	prev->next = addNode;
	// cout << "Adding " << addNode->name << endl;
	return;
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
			float gf60 = stof(tokens[9])/stof(tokens[3]); // divide total goals by games played
			float ga60 = stof(tokens[10])/stof(tokens[3]); // divide total goals by games played
			nm.erase(remove(nm.begin(), nm.end(), '*'), nm.end()); // remove *
			nm = getTeamAbrv(nm); 
			createTeamNode(nm, gf60, ga60, y);
		}
	}
}

// Date, home, home score, away, away score, OT/SO/REG

void YearTree::readRecord(string filename, int y){
	YearNode* node = searchYear(y);
	
	ifstream ifs(filename);
	if(ifs.is_open()){
		string line;
		while(getline(ifs, line)){
			vector <string> tokens;
			stringstream check1(line);
			string intermediate;
			int count = 0;
			while(getline(check1, intermediate, ',')){
				tokens.push_back(intermediate);
				count++;
			}
			// store tokens in variables
			// filenames are structured differently depending on year?
			string home = getTeamAbrv(tokens[1]);
			int homeScore = stoi(tokens[2]);
			string away = getTeamAbrv(tokens[3]);
			int awayScore = stoi(tokens[4]);
			string finish = tokens[5];
			// find teams in their respective categories
			int homeCat = searchTeam(home, y);
			int awayCat = searchTeam(away, y);
			if(homeCat != awayCat){ // check to see if teams are in the same category
				if(homeScore > awayScore){
					if(finish != "SO"){
						if(homeCat == 1 && awayCat == 2){
							node->hist.r1v2 += 2;
							node->hist.r1v2p += 2;
							node->hist.r2v1p += 2;
						}
						if(homeCat == 1 && awayCat == 3){
							node->hist.r1v3 += 2;
							node->hist.r1v3p += 2;
							node->hist.r3v1p += 2;
						}
						if(homeCat == 1 && awayCat == 4){
							node->hist.r1v4 += 2;
							node->hist.r1v4p += 2;
							node->hist.r4v1p += 2;
						}
						if(homeCat == 2 && awayCat == 3){
							node->hist.r2v3 += 2;
							node->hist.r2v3p += 2;
							node->hist.r3v2p += 2;
						}
						if(homeCat == 2 && awayCat == 4){
							node->hist.r2v4 += 2;
							node->hist.r2v4p += 2;
							node->hist.r4v2p += 2;
						}
						if(homeCat == 3 && awayCat == 4){
							node->hist.r3v4 += 2;
							node->hist.r3v4p += 2;
							node->hist.r4v3p += 2;
						}
					}
					// else if(finish != "SO"){ // game did go in to OT or SO, away team gets a point 
					// 	if(homeCat == 1 && awayCat == 2){
					// 		node->hist.r1v2 += 2;
					// 		node->hist.r1v2p += 2;
					// 		node->hist.r2v1 += 1;
					// 		node->hist.r2v1p += 2;
					// 	}
					// 	if(homeCat == 1 && awayCat == 3){
					// 		node->hist.r1v3 += 2;
					// 		node->hist.r1v3p += 2;
					// 		node->hist.r3v1 += 1;
					// 		node->hist.r3v1p += 2;
					// 	}
					// 	if(homeCat == 1 && awayCat == 4){
					// 		node->hist.r1v4 += 2;
					// 		node->hist.r1v4p += 2;
					// 		node->hist.r4v1 += 1;
					// 		node->hist.r4v1p += 2;
					// 	}
					// 	if(homeCat == 2 && awayCat == 3){
					// 		node->hist.r2v3 += 2;
					// 		node->hist.r2v3p += 2;
					// 		node->hist.r3v2 += 1;
					// 		node->hist.r3v2p += 2;
					// 	}
					// 	if(homeCat == 2 && awayCat == 4){
					// 		node->hist.r2v4 += 2;
					// 		node->hist.r2v3p += 2;
					// 		node->hist.r4v2 += 1;
					// 		node->hist.r4v2p += 2;
					// 	}
					// 	if(homeCat == 3 && awayCat == 4){
					// 		node->hist.r3v4 += 2;
					// 		node->hist.r3v4p += 2;
					// 		node->hist.r4v3 += 1;
					// 		node->hist.r4v3p += 2;
					// 	}
					// }
				} // end of home wins loop
				else{ // away team won
					if(finish != "SO"){
						if(homeCat == 1 && awayCat == 2){
							node->hist.r2v1 += 2;
							node->hist.r2v1p += 2;
							node->hist.r1v2p += 2;
						}
						if(homeCat == 1 && awayCat == 3){
							node->hist.r3v1 += 2;
							node->hist.r3v1p += 2;
							node->hist.r1v3p += 2;
						}
						if(homeCat == 1 && awayCat == 4){
							node->hist.r4v1 += 2;
							node->hist.r4v1p += 2;
							node->hist.r1v4p += 2;
						}
						if(homeCat == 2 && awayCat == 3){
							node->hist.r3v2 += 2;
							node->hist.r3v2p += 2;
							node->hist.r2v3p += 2;
						}
						if(homeCat == 2 && awayCat == 4){
							node->hist.r4v2 += 2;
							node->hist.r4v2p += 2;
							node->hist.r2v4p += 2;
						}
						if(homeCat == 3 && awayCat == 4){
							node->hist.r4v3 += 2;
							node->hist.r4v3p += 2;
							node->hist.r3v4p += 2;
						}
					}
					// else if(finish != "SO"){ // home team gets a point
					// 	if(homeCat == 1 && awayCat == 2){
					// 		node->hist.r2v1 += 2;
					// 		node->hist.r2v1p += 2;
					// 		// node->hist.r1v2 += 1;
					// 		node->hist.r1v2p += 2;
					// 	}
					// 	if(homeCat == 1 && awayCat == 3){
					// 		node->hist.r3v1 += 2;
					// 		node->hist.r3v1p += 2;
					// 		// node->hist.r1v3 += 1;
					// 		node->hist.r1v3p += 2;
					// 	}
					// 	if(homeCat == 1 && awayCat == 4){
					// 		node->hist.r4v1 += 2;
					// 		node->hist.r4v1p += 2;
					// 		// node->hist.r1v4 += 1;
					// 		node->hist.r1v4p += 2;
					// 	}
					// 	if(homeCat == 2 && awayCat == 3){
					// 		node->hist.r3v2 += 2;
					// 		node->hist.r3v2p += 2;
					// 		// node->hist.r2v3 += 1;
					// 		node->hist.r2v3p += 2;
					// 	}
					// 	if(homeCat == 2 && awayCat == 4){
					// 		node->hist.r4v2 += 2;
					// 		node->hist.r4v2p += 2;
					// 		// node->hist.r2v4 += 1;
					// 		node->hist.r2v4p += 2;
					// 	}
					// 	if(homeCat == 3 && awayCat == 4){
					// 		node->hist.r4v3 += 2;
					// 		node->hist.r4v3p += 2;
					// 		// node->hist.r3v4 += 1;
					// 		node->hist.r3v4p += 2;
					// 	}
					// }
				}
			}
		}
	}
}

void YearTree::getTotalRecord(int min, int max){
	// points made
	float t1v2 = 0;
	float t1v3 = 0;
	float t1v4 = 0;
	float t2v1 = 0;
	float t2v3 = 0;
	float t2v4 = 0;
	float t3v1 = 0;
	float t3v2 = 0;
	float t3v4 = 0;
	float t4v1 = 0;
	float t4v2 = 0;
	float t4v3 = 0;

	int t1v2p = 0;
	int t1v3p = 0;
	int t1v4p = 0;
	int t2v1p = 0;
	int t2v3p = 0;
	int t2v4p = 0;
	int t3v1p = 0;
	int t3v2p = 0;
	int t3v4p = 0;
	int t4v1p = 0;
	int t4v2p = 0;
	int t4v3p = 0;

	for(int i = min; i <= max; i++){
		if(searchYear(i)){
			YearNode* N = searchYear(i);
			t1v2 += N->hist.r1v2;
			t1v2p += N->hist.r1v2p;
			t1v3 += N->hist.r1v3;
			t1v3p += N->hist.r1v3p;
			t1v4 += N->hist.r1v4;
			t1v4p += N->hist.r1v4p;
			t2v1 += N->hist.r2v1;
			t2v1p += N->hist.r2v1p;
			t2v3 += N->hist.r2v3;
			t2v3p += N->hist.r2v3p;
			t2v4 += N->hist.r2v4;
			t2v4p += N->hist.r2v4p;
			t3v1 += N->hist.r3v1;
			t3v1p += N->hist.r3v1p;
			t3v2 += N->hist.r3v2;
			t3v2p += N->hist.r3v2p;
			t3v4 += N->hist.r3v4;
			t3v4p += N->hist.r3v4p;
			t4v1 += N->hist.r4v1;
			t4v1p += N->hist.r4v1p;
			t4v2 += N->hist.r4v2;
			t4v2p += N->hist.r4v2p;
			t4v3 += N->hist.r4v3;
			t4v3p += N->hist.r4v3p;
		}
	}
	cout << "RESULTS FOR ALL YEARS" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Category 1 winning percentage vs:" << endl;
	cout << "2: " << setprecision(2) << (t1v2/t1v2p)*100 << "%" << endl;
	cout << "3: " << (t1v3/t1v3p)*100 << "%" << endl;
	cout << "4: " << (t1v4/t1v4p)*100 << "%" << endl;
	cout << "Category 2 winning percentage vs:" << endl;
	cout << "1: " << (t2v1/t2v1p)*100 << "%" << endl;
	cout << "3: " << (t2v3/t2v3p)*100 << "%" << endl;
	cout << "4: " << (t2v4/t2v4p)*100 << "%" << endl;
	cout << "Category 3 winning percentage vs:" << endl;
	cout << "1: " << (t3v1/t3v1p)*100 << "%" << endl;
	cout << "2: " << (t3v2/t3v2p)*100 << "%" << endl;
	cout << "4: " << (t3v4/t3v4p)*100 << "%" << endl;
	cout << "Category 4 winning percentage vs:" << endl;
	cout << "1: " << (t4v1/t4v1p)*100 << "%" << endl;
	cout << "2: " << (t4v2/t4v2p)*100 << "%" << endl;
	cout << "3: " << (t4v3/t4v3p)*100 << "%" << endl;
	cout << "------------------------------------------------------------------------" << endl;
}

void YearTree::printAll(int year){
	ofstream myfile;
	myfile.open("output.txt");
	cout << "RESULTS FOR " << year << endl;
	// cout << "------------------------------------------------------------------------" << endl;
	// printCategories(year);
	// cout << "------------------------------------------------------------------------" << endl;
	// printRecord(year);
	// cout << "------------------------------------------------------------------------" << endl << endl;
	myfile << "------------------------------------------------------------------------" << endl;
	printCategories(year);
	myfile << "------------------------------------------------------------------------" << endl;
	printRecord(year);
	myfile << "------------------------------------------------------------------------" << endl << endl;
	myfile.close();
}

void YearTree::printRecord(int y){
	YearNode* node = searchYear(y);
	cout << "Category 1 winning percentage vs:" << endl;
	cout << "2: " << setprecision(2) << (node->hist.r1v2/node->hist.r1v2p)*100 << "%" << endl;
	cout << "3: " << (node->hist.r1v3/node->hist.r1v3p)*100 << "%" <<endl;
	cout << "4: " << (node->hist.r1v4/node->hist.r1v4p)*100 << "%" <<endl;
	cout << "Category 2 winning percentage vs:" << endl;
	cout << "1: " << (node->hist.r2v1/node->hist.r2v1p)*100 << "%" << endl;
	cout << "3: " << (node->hist.r2v3/node->hist.r2v3p)*100 << "%" << endl;
	cout << "4: " << (node->hist.r2v4/node->hist.r2v4p)*100 << "%" << endl;
	cout << "Category 3 winning percentage vs:" << endl;
	cout << "1: " << (node->hist.r3v1/node->hist.r3v1p)*100 << "%" << endl;
	cout << "2: " << (node->hist.r3v2/node->hist.r3v2p)*100 << "%" << endl;
	cout << "4: " << (node->hist.r3v4/node->hist.r3v4p)*100 << "%" << endl;
	cout << "Category 4 winning percentage vs:" << endl;
	cout << "1: " << (node->hist.r4v1/node->hist.r4v1p)*100 << "%" << endl;
	cout << "2: " << (node->hist.r4v2/node->hist.r4v2p)*100 << "%" << endl;
	cout << "3: " << (node->hist.r4v3/node->hist.r4v3p)*100 << "%" << endl;
}

string getTeamAbrv(string name){
	if(name == "Anaheim Ducks"){
		return "ANA";
	}
	if(name == "Arizona Coyotes" || name == "Phoenix Coyotes"){
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