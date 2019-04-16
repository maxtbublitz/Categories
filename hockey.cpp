#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "hockey.hpp"

using namespace std;

int getHash(int gf, int ga){
	if(gf >= 2.8){ // team has above average offense and
		if(ga <= 2.8){ // above average defense
			return 1;
		}
		else{ // below average defense
			return 2;
		}
	}
	else{ // team has below average offense and
		if(ga <= 2.8){ // above average defense
			return 3;
		}
		else{ // below average defense
			return 4;
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
		return;

	}
	while(temp != NULL){
		prev = temp;
		temp = temp->next;
	}
	prev->next = addNode;
	return;
}

