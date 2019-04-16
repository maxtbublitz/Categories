#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// linked list for teams
struct TeamNode {

	string name; 
	float goalsFor; // teams goals divided by games played
	float goalsAgainst;

	TeamNode* next;
};

// tree to store years
struct YearNode {
	TeamNode** table; // points to hash table
	int year; 
	YearNode *left;
	YearNode *right;
};

class YearTree {
public:
	YearTree();
	~YearTree();
	void addYear(int y);
	YearNode* searchYear(int y);
	void printCategories(int y); // prints categories for one year
	void createTeamNode(string nm, float gf60, float ga60, int year);
	void readFile(string filename, int y);
private:
	YearNode* root;
	YearNode* createYearNode(int y);
	YearNode* addYearHelper(YearNode* n, int y);
};

string getTeamAbrv(string name);




