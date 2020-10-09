#pragma once
#include <iostream>

using namespace std;


typedef enum { LeftHigher, EqualHeight, RightHigher } BalanceFactor;
bool Located = false;

template <class T>
struct TreeNode {

	T info;
	T root;
	BalanceFactor bf;
	TreeNode* leftSubTree;
	TreeNode* rightSubTree;
};


template <class T>
class AVLtree
{
public:
	AVLtree();
	~AVLtree();
	void InsertItem(T item);
	void PrintTree();
	void Contains(T item);
	void DeleteItem(T item);


	void Insert(TreeNode<T>*& tree, T item, bool& taller);
	void Print(TreeNode<T>*& tree);
	void RightBalance(TreeNode<T>*& tree, bool& taller);
	void LeftBalance(TreeNode<T>*& tree, bool& taller);
	void Search(TreeNode<T>*& tree, T item);
	void Delete(TreeNode<T>*& tree, T item, bool& shorter);
	void DeleteNode(TreeNode<T>*& tree, bool& shorter);
	//void RotateRight(TreeNode<T>*& tree;
	//void RotateLeft(TreeNode<T>*& tree);
private:

	TreeNode<T>* root;
};

//constructor
template <class T>
AVLtree<T>::AVLtree() {
	root = NULL;
}

//destructor
template <class T>
AVLtree<T>::~AVLtree() {

}

template<class T>
void AVLtree<T>::InsertItem(T item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}


template<class T>
void AVLtree<T>::Insert(TreeNode<T>*& tree, T item, bool& taller)
// Inserts item into tree.
// Post: item is in tree; search property is maintained
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new TreeNode<T>;
		tree->leftSubTree = NULL;
		tree->rightSubTree = NULL;
		tree->info = item;
		tree->bf = EqualHeight;
		taller = true;
	}
	else if (item == tree->info)
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	else if (item < tree->info)
	{
		Insert(tree->leftSubTree, item, taller);
		// Insert into leftSubTree subtree if (taller)	switch (tree->bf)
		{
			switch (tree->bf)
			{
			case LeftHigher: LeftBalance(tree, taller);	break;
			case EqualHeight: tree->bf = LeftHigher;	break;
			case RightHigher: tree->bf = EqualHeight;	taller = false; break;
			}

		}
	}

	else {
		Insert(tree->rightSubTree, item, taller);
		// Insert into rightSubTree subtree if (taller)
		switch (tree->bf)
		{
		case RightHigher: RightBalance(tree, taller); break;
		case EqualHeight: tree->bf = RightHigher; break;
		case LeftHigher: tree->bf = EqualHeight; taller = false; break;
		}
	}
}

template<class T>
void AVLtree<T>::PrintTree()
{
	Print(root);
}

template<class T>
void AVLtree<T>::Contains(T item)
{
	Search(root, item);
}

template<class T>
void AVLtree<T>::Search(TreeNode<T>*& tree, T item)
{

	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Search(tree->leftSubTree, item);

		}
		else if (item > tree->info)
		{
			Search(tree->rightSubTree, item);
		}
		else
		{
			Located = true;
			cout << "\n\nName found in tree" << endl;
		}
	}
	else
	{
		cout << "\n\nName not found in Avl Tree" << endl;
	}
}

template<class T>
void AVLtree<T>::DeleteItem(T item)
// Calls recursive function Delete to delete item from tree.

{
	bool shorter;
	Delete(root, item, shorter);
	Located = false;

}

template <class T>
void AVLtree<T>::Delete(TreeNode<T>*& tree, T item, bool& shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->leftSubTree, item, shorter);
			// Look in leftSubTree subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LeftHigher:
					tree->bf = EqualHeight;
					break;
				case EqualHeight:
					tree->bf = RightHigher;
					shorter = false;
					break;
				case RightHigher:
					DelRightBalance(tree, shorter);
					break;
				} // END SWITCH
		}
		else if (item > tree->info)
		{
			Delete(tree->rightSubTree, item, shorter);
			// Look in rightSubTree subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LeftHigher:
					DelLeftBalance(tree, shorter);
					break;
				case EqualHeight:
					tree->bf = LeftHigher;
					shorter = false;
					break;
				case RightHigher:
					tree->bf = EqualHeight;
					break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);

		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
	//cout << "Item Deleted" << endl;

}

template <class T>
void AVLtree<T>::DeleteNode(TreeNode <T>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	T data;
	TreeNode <T>* tempPtr;
	tempPtr = tree;
	if (tree->leftSubTree == NULL)
	{
		tree = tree->rightSubTree;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->rightSubTree == NULL)
	{
		tree = tree->leftSubTree;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->leftSubTree, data, shorter);
		// Delete the predecessor node
		if (shorter)
		{
			switch (tree->bf)
			{
			case LeftHigher:
				tree->bf = EqualHeight;
				break;
			case EqualHeight:
				tree->bf = RightHigher;
				shorter = false;
				break;
			case RightHigher:
				DelRightBalance(tree, shorter);
				break;
			}
		}
	}
}

template <class T>
void GetPredecessor(TreeNode<T>* tree, T& data)
// Sets data to the info member of the rightSubTree-most node in tree.
{
	tree = tree->leftSubTree;
	while (tree->rightSubTree != NULL)
		tree = tree->rightSubTree;
	data = tree->info;
}

template <class T>
void DelRightBalance(TreeNode<T>*& tree, bool& shorter)
{
	TreeNode<T>* rs = tree->rightSubTree;
	TreeNode<T>* ls;
	switch (rs->bf)
	{
	case RightHigher:	tree->bf = rs->bf = EqualHeight;
		RotateLeft(tree);
		shorter = true; break;
	case EqualHeight:	tree->bf = RightHigher;
		rs->bf = LeftHigher;
		RotateLeft(tree);
		shorter = false; break;
	case LeftHigher:	ls = rs->leftSubTree;
		switch (ls->bf)
		{
		case RightHigher:	tree->bf = LeftHigher;
			rs->bf = EqualHeight; break;
		case EqualHeight:	tree->bf = rs->bf = EqualHeight;
			break;
		case LeftHigher:	tree->bf = EqualHeight;
			rs->bf = RightHigher; break;
		} // END SWITCH

		ls->bf = EqualHeight;
		RotateRight(tree->rightSubTree);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class T>
void DelLeftBalance(TreeNode<T>*& tree, bool& shorter)
{
	TreeNode<T>* ls = tree->leftSubTree;
	TreeNode<T>* rs;
	switch (ls->bf)
	{
	case LeftHigher:
		tree->bf = ls->bf = EqualHeight;
		RotateRight(tree);
		shorter = true; break;
	case EqualHeight:
		tree->bf = LeftHigher;
		ls->bf = RightHigher;
		RotateRight(tree);
		shorter = false; break;
	case RightHigher:
		rs = ls->rightSubTree;
		switch (rs->bf)
		{
		case LeftHigher:	tree->bf = RightHigher;
			ls->bf = EqualHeight; break;
		case EqualHeight:	tree->bf = ls->bf = EqualHeight;
			break;
		case RightHigher:	tree->bf = EqualHeight;
			ls->bf = LeftHigher; break;
		} // END SWITCH
		rs->bf = EqualHeight;
		RotateLeft(tree->leftSubTree);
		RotateRight(tree);
		ls->bf = EqualHeight;
		shorter = true;
	}
}

template<class T>
void AVLtree<T>::Print(TreeNode<T>*& tree)
{
	string bf, leftSubTree, rightSubTree;
	//If tree is empty print empty tree
	if (tree == NULL)
		//cout << "  AVL tree is empty.\n  Please enter names to fill AVL Tree\n\n" << endl;
		return;
	else
	{

		Print(tree->leftSubTree);

		if (tree != NULL)
		{
			cout << "\n\t " << tree->info << ":";
		}


		if (tree->leftSubTree == NULL)
		{
			leftSubTree = "NULL";
			cout << "\tLeft: " << leftSubTree << "";
		}
		else
			cout << "\tLeft: " << tree->leftSubTree->info << " ";

		if (tree->rightSubTree == NULL)
		{
			rightSubTree = "NULL";
			cout << "\tRight: " << rightSubTree << "";
		}
		else
			cout << "\tRight: " << tree->rightSubTree->info << "  ";

		switch (tree->bf)
		{
		case 0: bf = "Left High "; break;
		case 1: bf = "Equal High "; break;
		case 2: bf = "Right High "; break;
		}
		cout << "\tBalance Factor: " << bf << "" << endl;

		Print(tree->rightSubTree);
	}

}

template<class T>
void AVLtree<T>::RightBalance(TreeNode<T>*& tree, bool& taller) {
	TreeNode<T>* rs = tree->rightSubTree;
	TreeNode<T>* ls;

	switch (rs->bf)
	{
	case RightHigher:	tree->bf = rs->bf = EqualHeight;
		RotateLeft(tree);
		taller = false;
		break;

	case EqualHeight:
		cerr << "Tree already BalanceFactord " << endl;
		break;
	case LeftHigher:	ls = rs->leftSubTree;
		switch (ls->bf)
		{
		case RightHigher:	tree->bf = LeftHigher;
			rs->bf = EqualHeight;
			break;
		case EqualHeight:	tree->bf = rs->bf = EqualHeight;
			break;
		case LeftHigher:	tree->bf = EqualHeight;
			rs->bf = RightHigher;
			break;
		}

		ls->bf = EqualHeight;
		RotateRight(tree->rightSubTree);
		RotateLeft(tree);
		taller = false;
	}
}

template<class T>
void AVLtree<T>::LeftBalance(TreeNode<T>*& tree, bool& taller)
{
	TreeNode<T>* ls = tree->leftSubTree;
	TreeNode<T>* rs;

	switch (ls->bf)
	{
	case LeftHigher:
		tree->bf = ls->bf = EqualHeight;
		RotateRight(tree);
		taller = false;
		break;

	case EqualHeight:
		cerr << "Tree already BalanceFactord " << endl;
		break;
	case RightHigher:
		rs = ls->rightSubTree;
		switch (rs->bf)
		{
		case LeftHigher:
			tree->bf = RightHigher;
			ls->bf = EqualHeight;
			break;
		case EqualHeight:
			tree->bf = ls->bf = EqualHeight;
			break;
		case RightHigher:
			tree->bf = EqualHeight;
			ls->bf = LeftHigher;
			break;
		}

		rs->bf = EqualHeight;
		RotateLeft(tree->leftSubTree);
		RotateRight(tree);
		taller = false;
	}
}

template<class T>
void RotateRight(TreeNode<T>*& tree)
{
	TreeNode<T>* ls;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	else if (tree->leftSubTree == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->leftSubTree;
		tree->leftSubTree = ls->rightSubTree;
		ls->rightSubTree = tree;
		tree = ls;
	}
}

template<class T>
void RotateLeft(TreeNode<T>*& tree)
{
	TreeNode<T>* rs;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	else if (tree->rightSubTree == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->rightSubTree;
		tree->rightSubTree = rs->leftSubTree;
		rs->leftSubTree = tree;
		tree = rs;
	}
}
