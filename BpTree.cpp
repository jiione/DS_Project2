#include "BpTree.h"
bool BpTree::Insert(VaccinationData* newData){
    if(root == nullptr)
    {
        root=new BpTreeDataNode;
        root->insertDataMap(newData->GetUserName(),newData);
        return true;
    }
    BpTreeNode* currNode = root;
    while(currNode->getMostLeftChild()!=nullptr)//find Data Node
    {
        for(auto it=currNode->getIndexMap()->begin(); it!=currNode->getIndexMap()->end();it++)
        {
            if(it->first.compare(newData->GetUserName())>0)
            {
                if(it==currNode->getIndexMap()->begin())
                {
                    currNode=currNode->getMostLeftChild();
                    break;
                }
                else
                {
                    currNode=(--it)->second;
                    break;
                }
            }
            else if(it==--(currNode->getIndexMap()->end()))
            {
                currNode=it->second;
                break;
            }
        }
    }
    currNode->insertDataMap(newData->GetUserName(),newData);
    
    if(exceedDataNode(currNode)==false)
    {
        return true;
    }
 /*exceed and split*/
    splitDataNode(currNode);
    return true;


}
BpTreeNode * BpTree::searchDataNode(string n) {
    if(root==nullptr)//if tree is Empty
    {
        return nullptr;
    }
    BpTreeNode* currNode=root;
    while(currNode->getMostLeftChild()!=nullptr)//find Data Node
    {
        for(auto it=currNode->getIndexMap()->begin(); it!=currNode->getIndexMap()->end();it++)
        {
            if(it->first.compare(n)>0)
            {
                if(it==currNode->getIndexMap()->begin())
                {
                    currNode=currNode->getMostLeftChild();
                    break;
                }
                else
                {
                    currNode=(--it)->second;
                    break;
                }
            }
            else if(it->first.compare(n)==0)
            {
                currNode=it->second;
                break;
            }
            else if(it==--(currNode->getIndexMap()->end()))
            {
                currNode=it->second;
                break;
            }
        }
    }
    for(auto k=currNode->getDataMap()->begin();k!=currNode->getDataMap()->end();k++)
    {
        if(k->first.compare(n)==0)
        {
            return currNode;
        }
    }
    return nullptr;
}
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    BpTreeNode* LcNode= new BpTreeDataNode;//left child node
    if(pDataNode==root)//if pDataNode is root
    {
        BpTreeNode* pNode = new BpTreeIndexNode;//declare parent index node
        auto it = pDataNode -> getDataMap()->begin();//index to access pDataNode's Map
        /*split and connect tree*/
        LcNode ->insertDataMap(it->first,it->second);//insert first Data of pDataNode in LcNode
        it++;//access second Data of pDataNode
        pNode->insertIndexMap(it->first,pDataNode);//insert second Data of pDataNode in pNode
        pNode->setMostLeftChild(LcNode);//connect pNode and LcNode
        pDataNode->getDataMap()->erase(pDataNode->getDataMap()->begin());//delete first Data of pDataNode
        LcNode->setNext(pDataNode);//Link DataNodes
        pDataNode->setPrev(LcNode);
        pDataNode->setParent(pNode);
        LcNode->setParent(pNode);
        root=pNode;
        return;
    }

    BpTreeNode* parent = pDataNode->getParent();//parent is pDataNode's parent Node
    auto it = pDataNode -> getDataMap()->begin();//index to access pDataNode's Map
    LcNode ->insertDataMap(it->first,it->second);//set information of Left child Node
    it++;
    parent ->insertIndexMap(it->first,pDataNode);//insert Data in parent Index Node and connect pDataNode
    pDataNode->getDataMap()->erase(pDataNode->getDataMap()->begin());
    if(parent->getMostLeftChild()==pDataNode)
    {
        parent->setMostLeftChild(LcNode);
        LcNode->setParent(parent);
    }
    else
    {
        for(auto k = parent->getIndexMap()->begin();k!=parent->getIndexMap()->end();k++)
        {
            if(k->second==pDataNode)
            {
                k->second=LcNode;
                LcNode->setParent(parent);
                break;
            }
        }
    }
    if(pDataNode->getPrev()!=nullptr)
    {
        pDataNode->getPrev()->setNext(LcNode);
        LcNode->setPrev(pDataNode->getPrev());
    }
    pDataNode->setPrev(LcNode);
    LcNode->setNext(pDataNode);

    if(exceedIndexNode(parent)==true)
    {
        splitIndexNode(parent);
    }
    
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    if(pIndexNode->getParent()==NULL)//if pIndexNode is root
    {
        /*split and connect tree*/
        BpTreeNode* LcNode = new BpTreeIndexNode;//create Left child node
        BpTreeNode* pNode = new BpTreeIndexNode;//create parent node
        auto it = pIndexNode->getIndexMap()->begin();
        LcNode ->insertIndexMap(it->first,it->second);//set Data of left child node
        it->second->setParent(LcNode);
        LcNode->setMostLeftChild(pIndexNode->getMostLeftChild());
        pIndexNode->getMostLeftChild()->setParent(LcNode);
        it++;
        pNode->setMostLeftChild(LcNode);
        LcNode->setParent(pNode);
        pNode->insertIndexMap(it->first,pIndexNode);//set Data of parent Node
        pIndexNode->setParent(pNode);
        pIndexNode->setMostLeftChild(it->second);
        pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin());
        pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin());
        root=pNode;
        return;
    }
    /*if pIndexNode is not root*/
    BpTreeNode* LcNode = new BpTreeIndexNode;
    BpTreeNode* parent = pIndexNode->getParent();
    auto it = pIndexNode->getIndexMap()->begin();
    LcNode->insertIndexMap(it->first,it->second);//set Data of Left child Node
    it->second->setParent(LcNode);
    LcNode->setMostLeftChild(pIndexNode->getMostLeftChild());
    pIndexNode->getMostLeftChild()->setParent(LcNode);
    it++;
    parent->insertIndexMap(it->first,pIndexNode);
    pIndexNode->setMostLeftChild(it->second);
    pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin());   
    pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin());
    if(parent->getMostLeftChild()==pIndexNode)
    {
        parent->setMostLeftChild(LcNode);
        LcNode->setParent(parent);
    }
    else
    {
        for(auto k = parent->getIndexMap()->begin();k!=parent->getIndexMap()->end();k++)
        {
            if(k->second==pIndexNode)
            {
                k->second=LcNode;
                LcNode->setParent(parent);
                break;
            }
        }
    }
    if(exceedIndexNode(parent)==true)
    {
        splitIndexNode(parent);
    }
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode) {
    if(pDataNode->getDataMap()->size()<order)
    {
        return false;
    }
    else
    {
        return true;
    }

}

bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode) {
    if(pIndexNode->getIndexMap()->size()<order)
    {
        return false;
    }
    else
    {
        return true;
    }

}
bool BpTree::CheckRange(BpTreeNode* node,string start,string end)
{
    BpTreeNode* currNode=node;
    while(currNode)
    {
        for(auto it=currNode->getDataMap()->begin();it!=currNode->getDataMap()->end();it++)
        {
            if(start.front()<=it->first.front())
            {
                if(it->first.front()<=end.front())
                {
                    return true;
                }
            }
        }
        currNode=currNode->getNext();
    }
    return false;
}

void BpTree::SearchRange(string start, string end) {
    BpTreeNode* currNode=root;
    while(currNode->getMostLeftChild()!=nullptr)
    {
        for(auto it=currNode->getIndexMap()->begin(); it!=currNode->getIndexMap()->end();it++)
        {
            if(start.front()<=it->first.front())
            {
                if(it==currNode->getIndexMap()->begin())
                {
                    currNode=currNode->getMostLeftChild();
                    break;
                }
                currNode=(--it)->second;
                break;
            }
            else if(it == --(currNode->getIndexMap()->end()))
            {
                currNode=it->second;
                break;
            }
        }
    }
	ofstream fout;
	fout.open("log.txt", ofstream::app);
    if(CheckRange(currNode,start,end)==false)
    {
	    fout << "========== ERROR ==========" <<endl;
	    fout << 400 << endl;
	    fout << "===========================" << endl << endl;
	    fout.close();
    }
    fout << "========== " << "SEARCH_BP" << " ==========" << endl;
    while(currNode)
    {
        for(auto it=currNode->getDataMap()->begin();it!=currNode->getDataMap()->end();it++)
        {
            if(end.front()<it->first.front())
            {
                fout << "============================" << endl << endl;
                return;
            }
            if(start.front()<=it->first.front())
            {
                fout<<it->second->GetUserName()<<" "<<it->second->GetVaccineName()<<" "<<it->second->GetTimes()
                <<" "<<it->second->GetAge()<<" "<<it->second->GetLocationName()<<endl;
            }
        }
        currNode=currNode->getNext();
    }
    fout << "============================" << endl << endl;
    fout.close();
}

void BpTree::Print() {
    ofstream fout;
	fout.open("log.txt", ofstream::app);
    fout << "========== " << "PRINT_BP" << " ==========" << endl;
    BpTreeNode* currNode =root;
    while(currNode->getMostLeftChild())
    {
        currNode=currNode->getMostLeftChild();
    }
    while(currNode)
    {
        for(auto it=currNode->getDataMap()->begin();it!=currNode->getDataMap()->end();it++)
        {
            fout<<it->second->GetUserName()<<" "<<it->second->GetVaccineName()<<" "<<it->second->GetTimes()<<" "<<it->second->GetAge()<<" "<<it->second->GetLocationName()<<endl;
        }
        currNode=currNode->getNext();
    }
    fout << "============================" << endl << endl;
    fout.close();
}
BpTree::~BpTree(){
    if(root->getMostLeftChild()==nullptr)
    {
        auto it =--(root->getDataMap()->end());
        int s=root->getDataMap()->size();
        for(int i=0; i<s;i++)
        {
            delete it->second;
            it--;
        }
        delete root;
        return;
    }
    queue<BpTreeNode*> q;
    BpTreeNode* currNode=root;
    BpTreeNode* deleteNode;
    while(currNode->getMostLeftChild()!=nullptr)
    {
        q.push(currNode->getMostLeftChild());
        for(auto it=currNode->getIndexMap()->begin();it!=currNode->getIndexMap()->end();it++)
        {
            q.push(it->second);
        }
        deleteNode=currNode;
        currNode=q.front();
        q.pop();
        deleteNode->getIndexMap()->clear();
        delete deleteNode;
    }
    auto it =--(currNode->getDataMap()->end());
    int s=currNode->getDataMap()->size();
    for(int i=0; i<s;i++)
    {
        delete it->second;
        it--;
    }
    currNode->getDataMap()->clear();
    delete currNode;
    while(q.empty()!=true)
    {
        deleteNode = q.front();
        q.pop();
        s=deleteNode->getDataMap()->size();
        auto it =--(deleteNode->getDataMap()->end());
        for(int i=0; i<deleteNode->getDataMap()->size();i++)
        {
            delete it->second;
            it--;
        }
        deleteNode->getDataMap()->clear();
        delete deleteNode;
    }
}