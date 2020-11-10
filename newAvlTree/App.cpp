// AVL Tree.cpp : Defines the entry point for the console application.
//


#include <iomanip>
#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;


const int InsertCode = 1;
const int PrintCode = 2;
const int ExitCode = 7;
const int clear = 6;
const int DeleteCode = 5;
const int PrintMenuCode = 3;
const int SearchCode = 4;


void PrintMenu() {

	cout << "Type " << InsertCode << " to insert an item to the AVL Tree" << endl;
	cout << "Type " << PrintCode << " to print the AVL Tree" << endl;
	cout << "Type " << PrintMenuCode << " to Print the Menu." << endl;
	cout << "Type " << SearchCode << " to search an item in the AVL Tree" << endl;
	cout << "Type " << DeleteCode << " to delete an item in the AVL Tree" << endl;
	cout << "Type " << clear << " clear" << endl;
	cout << "Type " << ExitCode << " To Exit the program." << endl;

}
void InValidOption() {
	cout << "Invalid option entered." << endl;
	PrintMenu();
}

AvlTree<string> avl;

void InsertTree() {
	string name;
	do
	{
		cout << "\nPlease enter the item you would like to add: (Enter 0 to cancel)\n";
		cin >> name;
		if (name != "0")
		{
			cout << "Now adding " << name << endl;
			avl.Insert(name);
			cout << "Item has been added";
		}
	} while (name != "0");

}

void PrintAVLTree() {
	cout << "PrintAVLTree: (Enter 0 to cancel)" << endl;
	cout << "AVL TREE" << endl;
	cout << avl.ToString() << endl;
}
void SearchTree() {
	string name;
	while (name != "0")
	{
		cout << "\nPlease enter the name you would like to Search: (Enter 0 to cancel)\n";
		cin >> name;
		if (name != "0")
		{
			cout << "Searching to see if " << name << " is in the tree " << endl;
			cout<<avl.ToString()<<endl;
			avl.Contains(name);

		}
	}
	

}

void DeleteTree() {
	string name;
	do
	{
		cout << "\nPlease enter the name you would like to Delete:(Enter 0 to cancel)\n";
		cin >> name;
		avl.Contains(name);

		if (avl.Contains(name))
		{
			cout << "Now deleting " << name << endl;
			avl.Remove(name);
		}
		else
		{
			cout << name << " is Not Found... " << endl;
		}

		cout << avl.ToString() << endl;
	} while (name != "0");


}
void ClearTree() {
	
	avl.Clear();
	cout << "all cleared" << endl;
}


void InitializeAvlTree()
{
	
	/*avl.Insert("Tom");
	avl.Insert("Ursula");
	avl.Insert("Mary");
	avl.Insert("Zaki");
	avl.Insert("Tim");
	avl.Insert("Amy");
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
		case clear:
			ClearTree();
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
