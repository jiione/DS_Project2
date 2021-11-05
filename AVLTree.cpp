#include "AVLTree.h"
bool AVLTree::Insert(VaccinationData* pVac){
    if(root == nullptr)
    {
        root = new AVLNode;
        root->setVacData(pVac);
        return true;
    }
    AVLNode* a= root;//most recent node with bf= +-1
    AVLNode* pa=nullptr;//parent of a
    AVLNode* p=root;//p moves through the tree
    AVLNode* pp=nullptr;//parent of p
    AVLNode* rootSub=nullptr;

    while(p!=nullptr)//move p through tree
    {
        if(p->getBF()!=0)//if p Node unbalanced
        {
            a=p;
            pa=pp;
        }
        if(Compare(pVac->GetUserName(),p->getVacData()->GetUserName())<0)
        {
            pp=p;
            p=p->getLeft();
        }
        else if(Compare(pVac->GetUserName(),p->getVacData()->GetUserName())>0)
        {
            pp=p;
            p=p->getRight();
        }
        else
        {
            return false;
        }
    }
    AVLNode* newNode = new AVLNode;//create new AVLNode
    newNode->setVacData(pVac);
    if(Compare(pVac->GetUserName(),pp->getVacData()->GetUserName())<0)
    {
        pp->setLeft(newNode);//insert as left child
    }
    else
    {
        pp->setRight(newNode);//insert as right child
    }

    int d;
    AVLNode* b;//child of a
    AVLNode* c;//child of b

    if(Compare(pVac->GetUserName(),a->getVacData()->GetUserName())>0)
    {
        b=p=a->getRight();
        d=-1;
    }
    else
    {
        b=p=a->getLeft();
        d=1;
    }

    while(p!=newNode)
    {
        if(Compare(pVac->GetUserName(),p->getVacData()->GetUserName())>0)//height of right increases by 1
        {
            p->setBF(-1);
            p=p->getRight();
        }
        else//height of left increases by 1
        {
            p->setBF(1);
            p=p->getLeft();
        }
    }

    if(a->getBF()==0||a->getBF()+d==0)//is tree unbalanced?
    {
        a->setBF(a->getBF()+d);
        return true;
    }
    /*tree unbalanced, determine rotation type*/
    if(d==1)//left imbalance
    {
        if(b->getBF()==1)//rotation type LL
        {
            a->setLeft(b->getRight());
            b->setRight(a);
            a->setBF(0);
            b->setBF(0);
            rootSub=b;
        }
        else//rotation type LR
        {
            c=b->getRight();
            b->setRight(c->getLeft());
            a->setLeft(c->getRight());
            c->setLeft(b);
            c->setRight(a);
            switch(c->getBF()){
                case 0:
                    b->setBF(0); a->setBF(0);
                    break;
                case 1:
                    a->setBF(-1); b->setBF(0);
                    break;
                case -1:
                    b->setBF(1); a->setBF(0);
                    break;
            }
            c->setBF(0);
            rootSub=c;
        }
    }
    else//right imbalance: this is symmetric to left imbalance
    {
        if(b->getBF()==-1)//rotation type RR
        {
            a->setRight(b->getLeft());
            b->setLeft(a);
            a->setBF(0);
            b->setBF(0);
            rootSub=b;
        }
        else//rotation type RL
        {
            c=b->getLeft();
            b->setLeft(c->getRight());
            a->setRight(c->getLeft());
            c->setRight(b);
            c->setLeft(a);
            switch(c->getBF())
            {
                case 0:
                    b->setBF(0); a->setBF(0);
                    break;
                case 1:
                    b->setBF(-1); a->setBF(0);
                    break;
                case -1:
                    a->setBF(1); b->setBF(0);
                    break; 
            }
            c->setBF(0);
            rootSub=c;
        }//end of RL
    }
    if(pa==nullptr)
    {
        root=rootSub;
    }
    else if(a==pa->getLeft())
    {
        pa->setLeft(rootSub);
    }
    else
    {
        pa->setRight(rootSub);
    }
    return true;
}

void AVLTree::GetVector(vector<VaccinationData*>& v){
    queue<AVLNode*> q;
    AVLNode* currNode=root;
    while(currNode)
    {
        v.push_back(currNode->getVacData());
        if(currNode->getLeft())
        {
            q.push(currNode->getLeft());
        }
        if(currNode->getRight())
        {
            q.push(currNode->getRight());
        }
        if(q.empty())
        {
            return;
        }
        currNode=q.front();
        q.pop();
    }
}

VaccinationData* AVLTree::Search(string name){
    if(root==nullptr)
    {
        return nullptr;
    }

    AVLNode* currNode = root;
    while(currNode)
    {
        if(Compare(name,currNode->getVacData()->GetUserName())<0)
        {
            currNode=currNode->getLeft();
        }
        else if(Compare(name,currNode->getVacData()->GetUserName())>0)
        {
            currNode=currNode->getRight();
        }
        else//success to find same Data
        {
            return currNode->getVacData();
        }
    }
    return nullptr;
}

AVLTree::~AVLTree()
{
    Delete(root);
}

void AVLTree::Delete(AVLNode* node)
{
   if(node == NULL)
    {
        return;
    }
    Delete(node->getLeft());
    Delete(node->getRight());
    delete node;
}

int AVLTree::Compare(string str1, string str2)
{
    for(int i=0;str1[i]!='\0';i++)
    {
        if(str1[i]>='A' && str1[i]<='Z')
        {
            str1[i]+=32;
        }
    }
    for(int i=0;str2[i]!='\0';i++)
    {
        if(str2[i]>='A' && str2[i]<='Z')
        {
            str2[i]+=32;
        }
    }
    return str1.compare(str2);
}