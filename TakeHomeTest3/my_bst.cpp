//Michael Holwey

#include "my_bst.h"
#include <algorithm>

template<typename KeyType>
My_BST<KeyType>::BSTNode::BSTNode(const KeyType &nodeDataItem, BSTNode *leftPtr, BSTNode *rightPtr)
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template<typename KeyType>
My_BST<KeyType>::My_BST()
{
	root = 0;
}

template<typename KeyType>
My_BST<KeyType>::My_BST(const My_BST<KeyType>& other)
{
	if(other.root == 0)
		root = 0;
	else
	{
		root = 0;
		copyTree(other.root);
	}
}

template<typename KeyType>
My_BST<KeyType>& My_BST<KeyType>::operator=(const My_BST<KeyType>& other)
{
	if(this != &other)
	{
		deleteHelper(root);

		if(other.root == 0)
			root = 0;
		else
			copyTree(other.root);
	}

	return *this;
}

template<typename KeyType>
void My_BST<KeyType>::copyTree(BSTNode *otherTreeNode)
{
	if (root == 0)
		root = new BSTNode(otherTreeNode->dataItem, 0, 0);
	else
	{
		BSTNode* temp = root;
		
		while(true)
		{
			if(otherTreeNode->dataItem < temp->dataItem && temp->left != 0)
				temp = temp->left;
			else if(otherTreeNode->dataItem >= temp->dataItem && temp->right != 0)
				temp = temp->right;
			else
				break;
		}

		if(otherTreeNode->dataItem < temp->dataItem)
			temp->left = new BSTNode(otherTreeNode->dataItem, 0, 0);
		else
			temp->right = new BSTNode(otherTreeNode->dataItem, 0, 0);
	}

	if(otherTreeNode->left != 0)
		copyTree(otherTreeNode->left);

	if(otherTreeNode->right != 0)
		copyTree(otherTreeNode->right);
}

template<typename KeyType>
My_BST<KeyType>::~My_BST()
{
	deleteHelper(root);
}

template<typename KeyType>
void My_BST<KeyType>::deleteHelper(BSTNode *p)
{
	if(p != 0)
	{
		deleteHelper(p->left);
		deleteHelper(p->right);
		delete p;
	}
}

template<typename KeyType>
void My_BST<KeyType>::insert(const KeyType& newDataItem)
{
	if(root == 0)
		root = new BSTNode(newDataItem, 0, 0);
	else
		insertHelper(root, newDataItem);
}

template<typename KeyType>
void My_BST<KeyType>::insertHelper(BSTNode *&p, const KeyType& newDataItem)
{
	if(p == 0)
		p = new BSTNode(newDataItem, 0, 0);
	else if(newDataItem < p->dataItem)
		insertHelper(p->left, newDataItem);
	else
		insertHelper(p->right, newDataItem);
}

template<typename KeyType>
void My_BST<KeyType>::remove_by_copying_iop(const KeyType& deleteKey)
{
	if(root == 0)
		cout << "TREE IS EMPTY. CANNOT REMOVE ITEM." << endl;
	else
	{
		if(search(deleteKey))
			removeHelper(root, deleteKey, true);
		else
			cout << "Key not found." << endl;
	}
}

template<typename KeyType>
void My_BST<KeyType>::remove_by_copying_ios(const KeyType& deleteKey)
{
	if(root == 0)
		cout << "TREE IS EMPTY. CANNOT REMOVE ITEM." << endl;
	else
	{
		if(search(deleteKey))
			removeHelper(root, deleteKey, false);
		else
			cout << "Key not found." << endl;
	}
}

template<typename KeyType>
void My_BST<KeyType>::removeHelper(BSTNode *p, const KeyType& deleteKey, bool copyIOP)
{
	if(deleteKey < p->dataItem)
		removeHelper(p->left, deleteKey, copyIOP);
	else if(deleteKey > p->dataItem)
		removeHelper(p->right, deleteKey, copyIOP);
	else
		copy_iop_iosHelper(p, copyIOP);
}

template<typename KeyType>
void My_BST<KeyType>::copy_iop_iosHelper(BSTNode *p, bool copyIOP)
{
	BSTNode *temp;
	BSTNode *temp2;

	if(p->left != 0 && p->right != 0)
	{
		if(copyIOP)
		{
			if(p->left != 0)
			{
				temp = p->left;
				temp2 = temp;

				while(temp->right != 0)
				{
					temp2 = temp;
					temp = temp->right;
				}

				if(p->left == temp)
					p->left = temp->left;

				temp2->right = 0;
			}
		}
		else
		{
			if(p->right != 0)
			{
				temp = p->right;
				temp2 = temp;

				while(temp->left != 0)
				{
					temp2 = temp;
					temp = temp->left;
				}

				if(p->right == temp)
					p->right = temp->right;

				temp2->left = 0;
			}
		}

		p->dataItem = temp->dataItem;
		delete temp;
	}
	else if(p->left != 0 && p->right == 0)
	{
		if(p->left != 0)
		{
			temp = p->left;
			temp2 = temp;

			while(temp->right != 0)
			{
				temp2 = temp;
				temp = temp->right;
			}

			if(p->left == temp)
				p->left = temp->left;

			temp2->right = 0;
		}

		p->dataItem = temp->dataItem;
		delete temp;
	}
	else if(p->left == 0 && p->right != 0)
	{
		if(p->right != 0)
		{
			temp = p->right;
			temp2 = temp;

			while(temp->left != 0)
			{
				temp2 = temp;
				temp = temp->left;
			}

			if(p->right == temp)
				p->right = temp->right;

			temp2->left = 0;
		}

		p->dataItem = temp->dataItem;
		delete temp;
	}
	else
	{
		if(root->left == 0 && root->right == 0)
		{
			delete root;
			root = 0;
		}
		else
		{
			temp = root;

			while(true)
			{
				if(temp->left == p || temp->right == p)
					break;
				else if(p->dataItem < temp->dataItem)
					temp = temp->left;
				else if(p->dataItem > temp->dataItem)
					temp = temp->right;
			}

			if(temp->left == p)
				temp->left = 0;
			else if(temp->right == p)
				temp->right = 0;

			delete p;
		}
	}
}

template<typename KeyType>
bool My_BST<KeyType>::search(const KeyType& searchKey)
{
	return searchHelper(root, searchKey);
}

template<typename KeyType>
bool My_BST<KeyType>::searchHelper(BSTNode *p, const KeyType& searchKey)
{
	if(p != 0)
	{
		if(searchKey == p->dataItem)
			return true;
		else if(searchKey < p->dataItem)
			searchHelper(p->left, searchKey);
		else if(searchKey >= p->dataItem)
			searchHelper(p->right, searchKey);
	}
	else
		return false;
}

template<typename KeyType>
bool My_BST<KeyType>::retrieve(const KeyType& searchKey, KeyType& searchItem)
{
	if(searchHelper(root, searchKey))
	{
		searchItem = searchKey;
		return true;
	}
	else
		return false;
}

template<typename KeyType>
void My_BST<KeyType>::print_preorder() const
{
	print_preorderHelper(root);
}

template<typename KeyType>
void My_BST<KeyType>::print_preorderHelper(BSTNode *p) const
{
	if(p != 0)
	{
		cout << p->dataItem << " ";
		print_preorderHelper(p->left);
		print_preorderHelper(p->right);
	}
}

template<typename KeyType>
void My_BST<KeyType>::print_sorted() const
{
	print_sortedHelper(root);
}

template<typename KeyType>
void My_BST<KeyType>::print_sortedHelper(BSTNode *p) const
{
	if(p != 0)
	{
		print_sortedHelper(p->left);
		cout << p->dataItem << " ";
		print_sortedHelper(p->right);
	}
}

template<typename KeyType>
void My_BST<KeyType>::print_postorder() const
{
	print_postorderHelper(root);
}

template<typename KeyType>
void My_BST<KeyType>::print_postorderHelper(BSTNode *p) const
{
	if(p != 0)
	{
		print_postorderHelper(p->left);
		print_postorderHelper(p->right);
		cout << p->dataItem << " ";
	}
}

template<typename KeyType>
void My_BST<KeyType>::print_levels() const
{
	cout << endl;
	unsigned int height = getHeight();
	for(unsigned int i = 1; i <= height; i++)
	{
		print_levelsHelper(root, i);
		cout << endl;
	}
}

template<typename KeyType>
void My_BST<KeyType>::print_levelsHelper(BSTNode *p, int level) const
{
	if(p == 0)
		return;
	if(level == 1)
		cout << p->dataItem << " ";
	else if (level > 1)
	{
		print_levelsHelper(p->left, level-1);
		print_levelsHelper(p->right, level-1);
	}
}

template < typename KeyType >
void My_BST<KeyType>::showStructure() const
{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}


template < typename KeyType >
void My_BST<KeyType>::showHelper(BSTNode *p, int level) const
{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem;   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}

template<typename KeyType>
int My_BST<KeyType>::getHeight() const
{
	int leftHeight, rightHeight, maxHeight;

	if(root == 0)
		return 0;

	leftHeight = getHeightHelper(root->left);
	rightHeight = getHeightHelper(root->right);
	maxHeight = 1 + max(leftHeight, rightHeight);
	
	return maxHeight;
}

template<typename KeyType>
int My_BST<KeyType>::getHeightHelper(BSTNode *p) const
{
	if(p == 0)
		return 0;

	return 1 + max(getHeightHelper(p->left), getHeightHelper(p->right));
}

template<typename KeyType>
bool My_BST<KeyType>::isAVLHeightBalanced()
{
	bool isBalanced = true;
	return isAVLHeightBalancedHelper(root, isBalanced);
}

template<typename KeyType>
bool My_BST<KeyType>::isAVLHeightBalancedHelper(BSTNode *p, bool& isBalanced)
{
	int leftHeight, rightHeight;
	if(p != 0)
	{
		leftHeight = getHeightHelper(p->left);
		rightHeight = getHeightHelper(p->right);

		if((leftHeight - rightHeight) > 1 || (rightHeight - leftHeight) > 1)
			isBalanced = false;

		isAVLHeightBalancedHelper(p->left, isBalanced);
		isAVLHeightBalancedHelper(p->right, isBalanced);
	}

	return isBalanced;
}

template<typename KeyType>
bool My_BST<KeyType>::isLeftistHeight()
{
	bool isLeftist = true;
	return isLeftistHeightHelper(root, isLeftist);
}

template<typename KeyType>
bool My_BST<KeyType>::isLeftistHeightHelper(BSTNode *p, bool& isLeftist)
{
	int leftHeight, rightHeight;
	if(p != 0)
	{
		leftHeight = shortestPathToExternal(p->left);
		rightHeight = shortestPathToExternal(p->right);

		if(leftHeight < rightHeight)
			isLeftist = false;

		isLeftistHeightHelper(p->left, isLeftist);
	}

	return isLeftist;
}

template<typename KeyType>
int My_BST<KeyType>::shortestPathToExternal(BSTNode *p)
{
	if(p == 0)
		return 0;
	return min(getHeightHelper(p), getHeightHelper(p));
}

template<typename KeyType>
KeyType My_BST<KeyType>::findLowestCommonAncestor(const KeyType& key1, const KeyType& key2)
{
	return findLowestCommonAncestorHelper(root, key1, key2);
}

template<typename KeyType>
KeyType My_BST<KeyType>::findLowestCommonAncestorHelper(BSTNode *p, const KeyType& key1, const KeyType& key2)
{
	if(p != 0)
	{
		if((p->dataItem <= key2 && p->dataItem >= key1) || (p->dataItem >= key2 && p->dataItem <= key1))
			return p->dataItem;
		else if(p->dataItem > key2 && p->dataItem > key1)
			findLowestCommonAncestorHelper(p->left, key1, key2);
		else
			findLowestCommonAncestorHelper(p->right, key1, key2);
	}
}

template<typename KeyType>
void My_BST<KeyType>::writeLessThan(const KeyType& key)
{
	if(root != 0)
		writeLessThanHelper(root, key);
}

template<typename KeyType>
void My_BST<KeyType>::writeLessThanHelper(BSTNode *p, const KeyType& key)
{
	if(p != 0)
	{
		writeLessThanHelper(p->left, key);

		if(p->dataItem < key)
			cout << p->dataItem << " ";

		writeLessThanHelper(p->right, key);
	}
}

template<typename KeyType>
void My_BST<KeyType>::convertToMirror()
{
	convertToMirrorHelper(root);
}

template<typename KeyType>
void My_BST<KeyType>::convertToMirrorHelper(BSTNode *p)
{
	if(p != 0)
	{
		BSTNode *temp = p->right;

		p->right = p->left;
		p->left = temp;

		convertToMirrorHelper(p->left);
		convertToMirrorHelper(p->right);
	}
}