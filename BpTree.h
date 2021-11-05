#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "VaccinationData.h"

using namespace std;
// BpTree
class BpTree{
private:
	BpTreeNode*	root;
	int			order;		// m children

public:
	BpTree(int order = 3){
		root = nullptr;
		this->order = order;
	}
	~BpTree();

	bool		isEmpty(){return root==NULL;}
	bool		Insert(VaccinationData* newData);//for Load,Add
	bool		exceedDataNode(BpTreeNode* pDataNode);//Load
	bool		exceedIndexNode(BpTreeNode* pIndexNode);//Load
	void		splitDataNode(BpTreeNode* pDataNode);//Load
	void		splitIndexNode(BpTreeNode* pIndexNode);//Load
	BpTreeNode*	searchDataNode(string n); //search VaccinationData node Search Bp
	void	SearchRange(string start, string end);//
	void	Print(); // print all
	bool CheckRange(BpTreeNode* node,string start,string end);

};

#endif
