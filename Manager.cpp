#include "Manager.h"
Manager::Manager(int bpOrder) {
	bp=new BpTree(bpOrder);
	avl=new AVLTree;
}

Manager::~Manager() {

}

void Manager::run(const char* command_txt) {
	ifstream fin;
	ofstream flog;
	fin.open(command_txt);// Open "Command.txt"
    flog.open("log.txt", ios::app);//Open "log.txt"
    if (!fin) // if fail to open "Command.txt"
    {
        flog << "File Open Error" << endl; //Print Error code
        return;
    }

    char cmd[100];
    while (!fin.eof())//Read String of "Command.txt" line by line
    {
        fin.getline(cmd, 100);
        char * tmp = strtok(cmd, " "); //tmp is first token of cmd
        if(tmp==NULL)
        {
            continue;
        }
        if(strcmp(tmp, "LOAD") == 0)//if tmp is "LOAD"
		{
			if(LOAD())
			{
				printSuccess("LOAD");
			}
			else
			{
				printErrorCode(100);
			}
		}
		else if(strcmp(tmp,"VLOAD")== 0)
		{
			if(VLOAD())
			{
				printSuccess("VLOAD");
			}
			else
			{
				printErrorCode(200);
			}
		}
		else if(strcmp(tmp,"ADD")== 0)
		{
			char* name = strtok(NULL," ");
			if(name==NULL) {printErrorCode(300); continue;}
			char* Vname = strtok(NULL," ");
			if(Vname==NULL) {printErrorCode(300); continue;}
			char* age = strtok(NULL," ");
			if(age==NULL) {printErrorCode(300); continue;}
			char* location = strtok(NULL," ");
			if(location==NULL) {printErrorCode(300); continue;}
			if(CheckNum(age)==false)
			{
				printErrorCode(300);
				continue;
			}
			if(!ADD(name,Vname,atoi(age),location))
			{
				printErrorCode(300);
			}

		}
		else if(strcmp(tmp,"SEARCH_BP")== 0)
		{
			char* cmd1= strtok(NULL," ");
			if(cmd1==NULL){printErrorCode(400); continue;}
			char* cmd2= strtok(NULL," ");
			if(cmd1!=NULL && cmd2!=NULL)
			{
				if(!SEARCH_BP(cmd1,cmd2))
				{
					printErrorCode(400);
				}
			}
			else if(cmd1!=NULL&& cmd2==NULL)
			{
				if(!SEARCH_BP(cmd1))
				{
					printErrorCode(400);
				}

			}
			else
			{
				printErrorCode(400);
			}
		}
		else if(strcmp(tmp,"SEARCH_AVL")== 0)
		{
			char* name = strtok(NULL," ");
			if(name==NULL)
			{
				printErrorCode(500);
			}
			else if(!SEARCH_AVL(name))
			{
				printErrorCode(500);
			}
		}
		else if(strcmp(tmp,"VPRINT")== 0)
		{
			char* cmd = strtok(NULL," ");
			if(cmd==NULL)
			{
				printErrorCode(700);
			}
			else if(!VPRINT(cmd))
			{
				printErrorCode(700);
			}
		}
		else if(strcmp(tmp,"PRINT_BP")== 0)
		{
			if(bp->isEmpty()==true)
			{
				printErrorCode(700);
			}
			else
			{
				bp->Print();
			}
		}
		else if(strcmp(tmp,"EXIT")== 0)
		{
			delete bp;
			delete avl;
			Print_vector.clear();
			fin.close();
			flog.close();
			return;
		}
	}

}

bool Manager::LOAD() {
	ifstream fdata;
	fdata.open("input_data.txt");//open "input_data.txt"
	if(!fdata)//if false to open input_data.txt
	{
		return false;
	}
	if(!bp->isEmpty())
	{
		return false;
	}

	char d_line[100];
	fdata.getline(d_line,100);
	if(d_line==NULL)//is Empty input_data.txt
	{
		return false;
	}
	fdata.close();
	fdata.open("input_data.txt");
	while(!fdata.eof())//read "input_data.txt" line by line
	{
		fdata.getline(d_line,100);
		VaccinationData* VData=new VaccinationData;//Create new Vacciantion data
		/*Set Data's information*/
		char* d_tmp=strtok(d_line," ");
		VData->SetUserName(d_tmp);
		d_tmp= strtok(NULL," ");
		VData->SetVaccineName(d_tmp);
		d_tmp=strtok(NULL," ");
		VData->SetTimes(atoi(d_tmp));
		d_tmp=strtok(NULL," ");
		VData->SetAge(atoi(d_tmp));
		d_tmp=strtok(NULL," ");
		VData->SetLocationName(d_tmp);
		bp->Insert(VData);
	}
	return true;

}

bool Manager::VLOAD() {
	if(avl->isEmpty()==true)
	{
		return false;
	}
	if(Print_vector.empty()==false)
	{
		Print_vector.clear();
	}
	avl->GetVector(Print_vector);
	return true;
}

bool Manager::ADD(char* name, char* Vname, int age, char* location) {
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	BpTreeNode* tmpNode=bp->searchDataNode(name);
	if(avl->Search(name)!=nullptr)//if Data exist in AVL Tree
	{
		return false;
	}
	if(tmpNode==nullptr)//data  is not exist in BpTree
	{
		/*set information of VaccinationData*/
		VaccinationData* VNode = new VaccinationData;
		VNode->SetUserName(name);
		VNode->SetVaccineName(Vname);
		VNode->SetAge(age);
		VNode->SetLocationName(location);
		VNode->SetTimesInc();
		if(VNode->GetVaccineName().compare("Janssen")==0)
		{
			avl->Insert(VNode);
		}
		bp->Insert(VNode);
	}
	else
	{
		VaccinationData* v = tmpNode->getDataMap()->find(name)->second;
		if(v->GetVaccineName().compare("Janssen")==0)//if Vaccin name is janssen
		{
			if(v->GetTimes()<1)
			{
				v->SetTimesInc();
				avl->Insert(v);//insert data to complete vaccine
			}
		}
		else
		{
			if(v->GetTimes()==0)
			{
				v->SetTimesInc();
			}
			else if(v->GetTimes()==1)
			{
				v->SetTimesInc();
				avl->Insert(v);
			}
		}
	}
    fout << "========== " << "ADD" << " ==========" << endl;
    fout << name<<" "<<Vname<<" "<<age<<" "<<location<<endl;
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

bool Manager::SEARCH_BP(string name) {
	BpTreeNode* tmpNode = bp->searchDataNode(name);
	if(tmpNode==nullptr)//if it not exist Data
	{
		return false;
	}
	for(auto it=tmpNode->getDataMap()->begin();it!=tmpNode->getDataMap()->end();it++)
	{
		if(name.compare(it->first)==0)
		{
			VaccinationData* v=it->second;
			ofstream fout;
			fout.open("log.txt", ofstream::app);
			fout << "========== " << "SEARCH_BP" << " ==========" << endl;
    		fout << v->GetUserName()<<" "<<v->GetVaccineName()<<" "<<v->GetTimes()<<" "<<v->GetAge()<<" "<<v->GetLocationName()<<endl;
    		fout << "============================" << endl << endl;
			fout.close();
			return true;
		}
	}
	return false;
}

bool Manager::SEARCH_BP(string start, string end) {
	if(start[1]!='\0'||end[1]!='\0')
	{
		return false;
	}
	bp->SearchRange(start,end);
	return true;
}

bool Manager::SEARCH_AVL(string name) {
	VaccinationData* v = avl->Search(name);
	if(v==nullptr)
	{
		return false;
	}
	ofstream fout;
	fout.open("log.txt", ofstream::app);
    fout << "========== " << "PRINT_AVL" << " ==========" << endl;
    fout << v->GetUserName()<<" "<<v->GetVaccineName()<<" "<<v->GetTimes()<<" "<<v->GetAge()<<" "<<v->GetLocationName()<<endl;
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

bool Compare(VaccinationData* vac1, VaccinationData* vac2) {
	string Vname1=vac1->GetVaccineName();
	string Vname2=vac2->GetVaccineName();
	string name1=vac1->GetUserName();
	string name2=vac2->GetUserName();
	for(int i=0;i<Vname1.length();i++)
	{
		if(Vname1[i]>='A' && Vname1[i]<='Z')
		{
			Vname1[i]+=32;
		}
	}
	for(int i=0;i<Vname2.length();i++)
	{
		if(Vname2[i]>='A' && Vname2[i]<='Z')
		{
			Vname2[i]+=32;
		}
	}
	for(int i=0;i<name1.length();i++)
	{
		if(name1[i]>='A' && name1[i]<='Z')
		{
			name1[i]+=32;
		}
	}
	for(int i=0;i<name2.length();i++)
	{
		if(name2[i]>='A' && name2[i]<='Z')
		{
			name2[i]+=32;
		}
	}
	if(Vname1==Vname2)
	{
		if(vac1->GetAge()==vac2->GetAge())
		{
			return name1 < name2;
		}
		else
		{
			return vac1->GetAge()<vac2->GetAge();
		}
	}
	else
	{
		return Vname1<Vname2;
	}
}

bool Compare2(VaccinationData* vac1, VaccinationData* vac2) {
	string name1=vac1->GetUserName();
	string name2=vac2->GetUserName();
	string Lname1=vac1->GetLocationName();
	string Lname2=vac2->GetLocationName();
	for(int i=0;i<name1.length();i++)
	{
		if(name1[i]>='A' && name1[i]<='Z')
		{
			name1[i]+=32;
		}
	}
	for(int i=0;i<name2.length();i++)
	{
		if(name2[i]>='A' && name2[i]<='Z')
		{
			name2[i]+=32;
		}
	}
	for(int i=0;i<Lname1.length();i++)
	{
		if(Lname1[i]>='A' && Lname1[i]<='Z')
		{
			Lname1[i]+=32;
		}
	}
	for(int i=0;i<Lname2.length();i++)
	{
		if(Lname2[i]>='A' && Lname2[i]<='Z')
		{
			Lname2[i]+=32;
		}
	}
	if(Lname1==Lname2)
	{
		if(vac1->GetAge()==vac2->GetAge())
		{
			return name1 < name2;
		}
		else
		{
			return vac1->GetAge() > vac2->GetAge();
		}
	}
	else
	{
		return Lname1<Lname2;
	}
}

bool Manager::VPRINT(string type_) {
	if(avl->isEmpty()==true)
	{
		return false;
	}
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	if(type_.compare("A")==0)
	{
		fout << "========== " << "VPRINT A" << " ==========" << endl;
		sort(Print_vector.begin(), Print_vector.end(),Compare);
		for(int i=0;i<Print_vector.size();i++)
		{
			fout<<Print_vector[i]->GetUserName()<<" "<<Print_vector[i]->GetVaccineName()<<" "<<Print_vector[i]->GetTimes()<<" "<<Print_vector[i]->GetAge()<<" "<<Print_vector[i]->GetLocationName()<<endl;
		}
	}
	else if(type_.compare("B")==0)
	{
		fout << "========== " << "VPRINT B" << " ==========" << endl;
		sort(Print_vector.begin(), Print_vector.end(),Compare2);
		for(int i=0;i<Print_vector.size();i++)
		{
			fout<<Print_vector[i]->GetUserName()<<" "<<Print_vector[i]->GetVaccineName()<<" "<<Print_vector[i]->GetTimes()<<" "<<Print_vector[i]->GetAge()<<" "<<Print_vector[i]->GetLocationName()<<endl;
		}		
	}
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

void Manager::printErrorCode(int n) {
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	fout << "========== ERROR ==========" <<endl;
	fout << n << endl;
	fout << "===========================" << endl << endl;
	fout.close();
}

void Manager::printSuccess(char* act)
{
	ofstream fout;
	fout.open("log.txt", ofstream::app);
    fout << "========== " << act << " ==========" << endl;
    fout << "Success" << endl;
    fout << "============================" << endl << endl;
	fout.close();
}

bool Manager::CheckNum(char* str){
    if(str[0]=='0')
    {
        return false;
    }
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]<'0' || str[i] >'9')
        {
            return false;
        }
    }
    return true;
}

