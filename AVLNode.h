#ifndef _AVLNODE_H_
#define _AVLNODE_H_

#include "VaccinationData.h"

class AVLNode
{
private:
	AVLNode*			pRight;
	AVLNode*			pLeft;
	VaccinationData*	pVaccinationData;
	int					mBF;

public:
	AVLNode(){
		pRight = nullptr;
		pLeft = nullptr;
		pVaccinationData = nullptr;
		mBF = 0;
	};
	~AVLNode(){};

	void setRight(AVLNode* SN){pRight = SN;}
	void setLeft(AVLNode* SN){pLeft = SN;}
	void setVacData(VaccinationData* pVac){ pVaccinationData = pVac;}
	void setBF(int a){mBF = a;}
	AVLNode*	getRight(){return pRight;}
	AVLNode*	getLeft(){return pLeft;}
	VaccinationData*	getVacData(){return pVaccinationData;}
	int				getBF(){return mBF;}
};

#endif