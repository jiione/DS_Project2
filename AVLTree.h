#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "VaccinationData.h"
#include "AVLNode.h"
/* class AVL */

class AVLTree{
private:
	AVLNode*	root;

public:
	
	AVLTree(){
		root=nullptr;
	}
	~AVLTree();
	bool		Insert(VaccinationData* pVac);//Insert Data in AVL tree
	VaccinationData*	Search(string name);//search data by name in AVL tree and return VaccinationData
	void GetVector(vector<VaccinationData*>& v);//Load AVL tree in Vector
	bool isEmpty(){return root==nullptr;}//is Empty avl tree?
	void Delete(AVLNode* node);//delete all data in the tree
	int Compare(string str1, string str2);//Compare the two strings in the dictionary order
};

#endif

