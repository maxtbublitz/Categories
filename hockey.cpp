#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//***********************************************************************************//
//******************************YEAR TREE IMPLEMENTATION*****************************//
//***********************************************************************************//

YearTree::YearTree(){ root = 0; }

YearTree::~YearTree(){ }

void YearTree::addYear(int y){
	YearNode* newYear = new YearNode;
	newYear->year = y;
	// assign a pointer to a hash table

	if(root == 0){
		root = newYear;
	}
	else{
		YearNode* curr = root;
		YearNode* prev = 0;
		while(curr != 0){
			if(y < curr->year){
				prev = curr;
				curr = curr->left;
			}
			else{
				prev = curr;
				curr = curr->right;
			}
		}
		if(y < prev->year){
			prev->left = y;
		}
		else{
			prev->right = y;
		}
	}
	return;
}

void YearTree::printCategories(); 

void YearTree::printCategories(int year); 

//***********************************************************************************//
//***************************HASH CATEGORIES IMPLEMENTATION**************************//
//***********************************************************************************//