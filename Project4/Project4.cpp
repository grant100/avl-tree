#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Tree.h"

//constants
const int ONE = 1;
const int TWO = 2;


using namespace std;
typedef int node_entry;

// Function Name: continueInput()
// Purpose:	  check that input from user is valid
// Parameters: none
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int continueInput()
{
	int input;
	std::cin >> input;
	while (std::cin.fail() || input > TWO || input < ONE)//if failed, not number
	{
		std::cin.clear();
		std::cin.ignore();
		cout << "\nError... Incorrect input!" << "\nLoad new file? 1 = Yes 2 = No : ";
		std::cin >> input;
	}
	return input;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Tree tree;
	ifstream iFile;
	node_entry data;
	int continue_in;
	bool isOpen = false;
	bool isContinue = true;
	std::cout << "Grant Sowards" << "\nCS 2420" << "\nProject 4 AVL Tree" << endl;
	
	while (isContinue)
	{
		std::cout << "\nEnter file name (include extension), e.g. numbers.txt: " << endl;
		while (!isOpen)
		{
			string cinName;
			cin >> cinName;
			string fileName = cinName;
			iFile.open(fileName);
			if (iFile.is_open())
			{
				isOpen = true;
				std::cout << "\nOpening File..." << endl;
			}
			else
			{
				cin.clear();
				std::cout << "Could not open file!" << "\n\nTry Again: ";
			}

		}
		while (!iFile.eof()) //read in file
		{
			iFile >> data;
			tree.insert(data);
			//cout << "\n" << data;
		}
	
		iFile.close();

		cout << "\n\n------------------Recursive In-Order Traversal-----------------------"<<endl;
		tree.inOrderTraversal(tree.getRoot());
		cout << "\n\n------------------Non-Recursive Pre-Order Traversal------------------"<<endl;
		tree.preOrderTraversal(tree.getRoot());

		cout << "\n\nDeleting Tree...";
		tree.stackDelete();
		tree.treeDelete(tree.getRoot());
		tree.setRootNULL();
		
		cout << "\nAll Items Deleted...";
		cout << "\nLoad a new file? 1 = Yes 2 = No: ";
		continue_in = continueInput();//check for continuation
		if (continue_in == ONE)
		{
			isContinue = true;
			isOpen = false;
		}
		else if (continue_in == TWO)
		{
			isContinue = false;
		}
	}
	
	cout << "\nExiting..." << endl;
	
	std::cin.clear();
	std::cin.ignore();
	std::cin.get();
	return 0;
}
