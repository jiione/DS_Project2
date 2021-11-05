#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, VaccinationData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;

public:
	BpTreeDataNode(){
		pNext=nullptr;
		pPrev=nullptr;
	}
	void setNext(BpTreeNode* pN){pNext = pN;}
	void setPrev(BpTreeNode* pN){pPrev = pN;}
	BpTreeNode* getNext(){return pNext;}
	BpTreeNode* getPrev(){return pPrev;}

	void insertDataMap(string n, VaccinationData* pN){
		mapData.insert(map<string, VaccinationData*>::value_type(n,pN));
	}

	void deleteMap(string n){
		mapData.erase(n);
	}
	map<string, VaccinationData*>* getDataMap(){return &mapData;}
};

#endif