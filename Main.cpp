/*
* File:   Main.cpp
* CSIS 215-<D01>
* Author Isaac Craig
*/

#include <string>
#include <sstream>
#include <iostream>
#include "BST.h"
using namespace std;

void PauseScreen(); //Used to pause screen output
int main() {
	BST<int, string> *Test = new BST<int, string>;

	// Tests BST functions **************************************************
	cout << "Building tree and printing said tree" << endl;
	Test->insert(77, "seventy - seven"); //inserts a node into the tree
	Test->insert(70, "seventy");
	Test->insert(75, "seventy-five");
	Test->insert(66, "sixty-six");
	Test->insert(79, "seventy-nine");
	Test->insert(68, "sixty-eight");
	Test->insert(67, "sixty-seven");
	Test->insert(69, "sixty-nine");
	Test->insert(90, "ninety");
	Test->insert(85, "eighty-five");
	Test->insert(83, "eighty-three");
	Test->insert(87, "eighty-seven");
	Test->insert(65, "sixty - five");
	Test->print();
	cout << endl << endl;
	cout << "testing inorder print" << endl;
	Test->inOrder();
	cout << endl << endl;
	cout << "testing post order print" << endl;
	Test->postOrder();
	// *********************************************************************
PauseScreen();
return 0;
}

//Used to pause the screen wherever desired
void PauseScreen()
{
	char ch;
	cout << "\nPress the Enter key to continue ... ";
	cin.get(ch);
}