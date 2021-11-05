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
	bool		Insert(VaccinationData* pVac);
	VaccinationData*	Search(string name);
	void GetVector(vector<VaccinationData*>& v);
	bool isEmpty(){return root==nullptr;}
	void Delete(AVLNode* node);
	int Compare(string str1, string str2);
};

#endif

