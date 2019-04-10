#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// linked list for teams
struct TeamNode {

	string name; 
	float goalsFor;
	float goalsAgainst;

	team* next;

	TeamNode();
	~TeamNode();

	void addTeam(string name, float gf60, float gf60);
	void sortAZ();
	void findTeam(string name);
}

// hash table to store categories
class Categories {
private:
	TeamNode* table[5];
	int tableSize = 5;
	int getHash(); // used to get category
public:
	Categories();
	~Categories();
	void insert();
}

// tree to store years
struct YearNode {
	Categories* head = table[0]; // points to hash table
	int year;
	YearNode *parent = NULL;
	YearNode *left = NULL;
	YearNode *right = NULL;
}

class YearTree {
public:
	YearTree();
	~YearTree();
	void addYear(int y);
	void printCategories(); // prints categories for all years
	void printCategories(int y); // prints categories for one year
private:
	YearTree* root;
}


