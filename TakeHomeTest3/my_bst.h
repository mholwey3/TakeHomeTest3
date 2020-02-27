//Michael Holwey

#ifndef MY_BST_H
#define MY_BST_H

#include <stdexcept>
#include <iostream>

using namespace std;

template<typename KeyType>
class My_BST
{
	public:

		My_BST();
		My_BST(const My_BST<KeyType>& other);
		My_BST& operator=(const My_BST<KeyType>& other);
		~My_BST();

		void insert(const KeyType& newDataItem);
		bool search(const KeyType& searchKey);
		bool retrieve(const KeyType& searchKey, KeyType& searchItem);
		void remove_by_copying_iop(const KeyType& deleteKey);
		void remove_by_copying_ios(const KeyType& deleteKey);

		void print_preorder() const;
		void print_sorted() const; //print inorder
		void print_postorder() const;
		void print_levels() const;

		void showStructure() const;

		int getHeight() const;

		bool isAVLHeightBalanced();
		bool isLeftistHeight();
		KeyType findLowestCommonAncestor(const KeyType& key1, const KeyType& key2);
		void writeLessThan(const KeyType& key);
		void convertToMirror();

	private:

		class BSTNode
		{
			public:

				BSTNode(const KeyType &nodeDataItem, BSTNode *leftPtr, BSTNode *rightPtr);

				KeyType dataItem;
				BSTNode *left;
				BSTNode *right;
		};

		//helper functions
		void copyTree(BSTNode *otherTreeNode);
		void deleteHelper(BSTNode *p);
		void insertHelper(BSTNode *&p, const KeyType& newDataItem);
		void removeHelper(BSTNode *p, const KeyType& deleteKey, bool copyIOP);
		void copy_iop_iosHelper(BSTNode *p, bool copyIOP);
		bool searchHelper(BSTNode *p, const KeyType& searchKey);
		void print_preorderHelper(BSTNode *p) const;
		void print_sortedHelper(BSTNode *p) const;
		void print_postorderHelper(BSTNode *p) const;
		void print_levelsHelper(BSTNode *p, int level) const;
		void showHelper(BSTNode *p, int level) const;
		int getHeightHelper(BSTNode *p) const;

		void writeLessThanHelper(BSTNode *p, const KeyType& key);
		bool isAVLHeightBalancedHelper(BSTNode *p, bool& isBalanced);
		bool isLeftistHeightHelper(BSTNode *p, bool& isLeftist);
		void convertToMirrorHelper(BSTNode *p);
		int shortestPathToExternal(BSTNode *p);
		KeyType findLowestCommonAncestorHelper(BSTNode *p, const KeyType& key1, const KeyType& key2);

		BSTNode *root;

};
#endif