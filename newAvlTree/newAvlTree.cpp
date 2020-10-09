// AVL Tree.cpp : Defines the entry point for the console application.
//


#include <iomanip>
#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;


const int InsertCode = 1;
const int PrintCode = 2;
const int ExitCode = 4;
const int PrintMenuCode = 3;



void PrintMenu() {

	cout << "Type " << InsertCode << " to insert an item to the AVL Tree" << endl;
	cout << "Type " << PrintCode << " to print the AVL Tree" << endl;
	cout << "Type " << PrintMenuCode << " to Print the Menu." << endl;
	cout << "Type " << ExitCode << " To Exit the program." << endl;

}
void InValidOption() {
	cout << "Invalid option entered." << endl;
	PrintMenu();
}

AVLtree<string> avl;

void InsertTree() {
	string name;
	do
	{
		cout << "\nPlease enter the name you would like to add: (Enter 0 to cancel)\n";
		cin >> name;
		if (name != "0")
		{
			cout << "Now adding " << name << endl;
			avl.InsertItem(name);
			cout << "Item has been added";
		}
	} while (name != "0");

}

void PrintAVLTree() {
	cout << "PrintAVLTree" << endl;
	cout << "AVL TREE";
	avl.PrintTree();
}



void InitializeAvlTree()
{
	avl.InsertItem("Mark");
	avl.InsertItem("Ann");
	avl.InsertItem("Tom");
	avl.InsertItem("Sarah");
	avl.InsertItem("Simon");
}




int main()
{
	bool run = true;
	int option = -1;

	PrintMenu();

	InitializeAvlTree();
	do
	{
		cin >> option;
		switch (option)
		{
		case PrintCode:
			PrintAVLTree();
			break;
		case InsertCode:
			InsertTree();
			break;
		case PrintMenuCode:
			PrintMenu();
			break;
		case ExitCode:
			run = false;
			break;
		default:
			InValidOption();
			break;
		}


		//The Progam
	} while (run);

}
