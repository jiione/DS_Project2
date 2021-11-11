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

	bool		isEmpty(){return root==NULL;}//is Empty tree?
	bool		Insert(VaccinationData* newData);//insert Data in B+Tree
	bool		exceedDataNode(BpTreeNode* pDataNode);//if exceed Data Node, return true
	bool		exceedIndexNode(BpTreeNode* pIndexNode);//if exceed Index Node, return true
	void		splitDataNode(BpTreeNode* pDataNode);//if exceed Data Node, split node
	void		splitIndexNode(BpTreeNode* pIndexNode);//if exceed Index Node, split node
	BpTreeNode*	searchDataNode(string n); //Search data Node by name and return the node
	void	SearchRange(string start, string end);//Find the data within the range
	void	Print(); // print all data of tree
	bool CheckRange(BpTreeNode* node,string start,string end);//Check if there is data in the range

};

#endif
