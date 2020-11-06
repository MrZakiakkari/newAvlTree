// AVL Tree.cpp : Defines the entry point for the console application.
//


#include <iomanip>
#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;


const int InsertCode = 1;
const int PrintCode = 2;
const int ExitCode = 6;
const int DeleteCode = 5;
const int PrintMenuCode = 3;
const int SearchCode = 4;


void PrintMenu() {

	cout << "Type " << InsertCode << " to insert an item to the AVL Tree" << endl;
	cout << "Type " << PrintCode << " to print the AVL Tree" << endl;
	cout << "Type " << PrintMenuCode << " to Print the Menu." << endl;
	cout << "Type " << SearchCode << " to search an item in the AVL Tree" << endl;
	cout << "Type " << DeleteCode << " to delete an item in the AVL Tree" << endl;
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
		cout << "\nPlease enter the item you would like to add: (Enter 0 to cancel)\n";
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
	cout << "PrintAVLTree: (Enter 0 to cancel)" << endl;
	cout << "AVL TREE";
	avl.PrintTree();
}
void SearchTree() {
	string name;
	do
	{
		cout << "\nPlease enter the name you would like to Search: (Enter 0 to cancel)\n";
		cin >> name;
		if (name != "0")
		{
			cout << "Searching to see if " << name << " is in the tree " << endl;
			avl.PrintTree();
			avl.Contains(name);

		}
	} while (name != "0");
	

}

void DeleteTree() {
	string name;
	do
	{
		cout << "\nPlease enter the name you would like to Delete:\n";
		cin >> name;
		avl.Contains(name);

		if (Located == true)
		{
			cout << "Now deleting " << name << endl;
			avl.DeleteItem(name);
		}
		else if (Located == false)
		{
			cout << name << " is Not Found... " << endl;
		}

		avl.PrintTree();
	} while (name != "0");


}


void InitializeAvlTree()
{
	/*
	avl.InsertItem("Mark");
	avl.InsertItem("Ann");
	avl.InsertItem("Tom");
	avl.InsertItem("Sarah");
	avl.InsertItem("Simon");
	*/
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
		case SearchCode:
			SearchTree();
			break;
		case DeleteCode:
			DeleteTree();
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
