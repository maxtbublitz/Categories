#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct record {
	// record();

	// points that a team of one category has against another
	float r1v2;
	float r1v3;
	float r1v4;
	float r2v1;
	float r2v3;
	float r2v4;
	float r3v1;
	float r3v2;
	float r3v4;
	float r4v1;
	float r4v2;
	float r4v3;
	// possible points that a team of one category has against another
	int r1v2p;
	int r1v3p;
	int r1v4p;
	int r2v1p;
	int r2v3p;
	int r2v4p;
	int r3v1p;
	int r3v2p;
	int r3v4p;
	int r4v1p;
	int r4v2p;
	int r4v3p;
};

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
	record hist;
};

class YearTree {
public:
	YearTree();
	~YearTree();

	void createTeamNode(string nm, float gf60, float ga60, int year);

	void addYear(int y);

	YearNode* searchYear(int y);
	int searchTeam(string name, int y);

	void readFile(string filename, int y); // read from the data of teams in a season
	void readRecord(string filename, int y);
	void getTotalRecord(int min, int max);

	void printAll(int year); // calls both below functions
	void printRecord(int y); // prints record of each category vs another
	void printCategories(int y); // prints categories for one year
private:
	YearNode* root;
	YearNode* createYearNode(int y);
	YearNode* addYearHelper(YearNode* n, int y);
};

string getTeamAbrv(string name); 