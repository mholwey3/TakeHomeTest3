//Michael Holwey

#include "my_bst.cpp"

int main()
{
	My_BST<int> bst1;
	My_BST<int> bst2;

	bst1.insert(5);
	bst1.insert(2);
	bst1.insert(6);
	bst1.insert(1);
	bst1.insert(4);
	bst1.insert(3);

	bst1.showStructure();

	cout << "Search for 1: " << bst1.search(1) << endl;
	cout << "Search for 18: " << bst1.search(18) << endl;

	int searchItem;

	cout << "Retrieve 1: ";
	
	if(bst1.retrieve(1, searchItem))
		cout << "Found: " << searchItem << endl;
	else
		cout << "Item not found." << endl;
	
	cout << "Retrieve 18: ";
	
	if(bst1.retrieve(18, searchItem))
		cout << "Found: " << searchItem << endl;
	else
		cout << "Item not found." << endl;

	cout << endl;

	cout << "Print Preorder:  ";
	bst1.print_preorder();
	cout << endl;

	cout << "Print Sorted:    ";
	bst1.print_sorted();
	cout << endl;

	cout << "Print Postorder: ";
	bst1.print_postorder();
	cout << endl;

	cout << "Print Levels: ";
	bst1.print_levels();
	cout << endl;

	cout << "Write less than 4: ";
	bst1.writeLessThan(4);
	cout << endl;

	cout << "Is Tree AVL Height Balanced? " << bst1.isAVLHeightBalanced() << endl;

	cout << "Is Tree Leftist? " << bst1.isLeftistHeight() << endl;

	cout << "Lowest Common Ancestor of 1 and 4: " << bst1.findLowestCommonAncestor(1, 4) << endl;
	cout << "Lowest Common Ancestor of 2 and 4: " << bst1.findLowestCommonAncestor(2, 4) << endl;

	cout << "Convert to Mirror:" << endl;
	bst1.convertToMirror();
	bst1.showStructure();

	cout << "New Binary Search Tree from old:" << endl;
	bst2 = My_BST<int>(bst1);
	bst2.showStructure();
}