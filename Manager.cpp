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
			char* Lcmd = strtok(NULL," ");
			if(Lcmd!=NULL){printErrorCode(100); continue;}//if parameter is exceed, print error code
			if(LOAD())//call Load method
			{
				printSuccess("LOAD");//if Method success, print success code 
			}
			else
			{
				printErrorCode(100);//if Method fail, print Error code
			}
		}
		else if(strcmp(tmp,"VLOAD")== 0)//if tmp is "VLOAD"
		{
			char* VLcmd = strtok(NULL," ");
			if(VLcmd!=NULL){printErrorCode(200); continue;}//if parameter is exceed, print error code
			if(VLOAD())//call VLOAD method
			{
				printSuccess("VLOAD");//if Method success, print succenss code 
			}
			else
			{
				printErrorCode(200);//if method fail, print error code
			}
		}
		else if(strcmp(tmp,"ADD")== 0)//if tmp is "ADD"
		{
			/*setting datas needed Add method */
			char* name = strtok(NULL," ");
			if(name==NULL) {printErrorCode(300); continue;}//if name's a wrong command, print error code
			char* Vname = strtok(NULL," ");
			if(Vname==NULL) {printErrorCode(300); continue;}//if name of vaccine's a wrong command, print error code
			char* age = strtok(NULL," ");
			if(age==NULL) {printErrorCode(300); continue;}//if age's a wrong command, print error code
			char* location = strtok(NULL," ");
			if(location==NULL) {printErrorCode(300); continue;}//if location's a wrong command, print error code
			char* Acmd= strtok(NULL," ");
			if(Acmd!=NULL){printErrorCode(300); continue;}//if parameter is exceed, print error code
			if(CheckNum(age)==false)//if age is not number
			{
				printErrorCode(300);//print error code
				continue;
			}
			if(!ADD(name,Vname,atoi(age),location))//call ADD method
			{
				printErrorCode(300);//if method fail, print error code
			}

		}
		else if(strcmp(tmp,"SEARCH_BP")== 0)//if tmp is "SEARCH_BP"
		{
			char* cmd1= strtok(NULL," ");
			if(cmd1==NULL){printErrorCode(400); continue;}//If the data is wrong, the error code is output
			char* cmd2= strtok(NULL," ");
			char* cmd3 = strtok(NULL," ");
			if(cmd3!=NULL){printErrorCode(400); continue;}//if parameter is exceed, print error code
			if(cmd1!=NULL && cmd2!=NULL)
			{
				if(!SEARCH_BP(cmd1,cmd2))//calling a SEARCH_BP method
				{
					printErrorCode(400);//print error code
				}
			}
			else if(cmd1!=NULL&& cmd2==NULL)//if it it two command data 
			{
				if(!SEARCH_BP(cmd1))//Calling a SEARCH_BP method to explore the range
				{
					printErrorCode(400);//print Error code
				}

			}
			else
			{
				printErrorCode(400);//print Error code
			}
		}
		else if(strcmp(tmp,"SEARCH_AVL")== 0)//tmp is "SEARCH_AVL"
		{
			char* name = strtok(NULL," ");
			char* SAcmd = strtok(NULL," ");
			if(SAcmd!=NULL){printErrorCode(500); continue;}//if parameter is exceed, print error code
			if(name==NULL)//if it is wrong command, print error code
			{
				printErrorCode(500);
			}
			else if(!SEARCH_AVL(name))//calling SEARCH_AVL method 
			{
				printErrorCode(500);//if method fails, print error code
			}
		}
		else if(strcmp(tmp,"VPRINT")== 0)//tmp is "VPRINT"
		{
			char* cmd = strtok(NULL," ");
			char* VPcmd = strtok(NULL," ");
			if(VPcmd!=NULL){printErrorCode(600); continue;}//if parameter is exceed, print error code
			if(cmd==NULL)//if it wrong command, print error code
			{
				printErrorCode(600);
			}
			else if(!VPRINT(cmd))//calling SEARCH_AVL method
			{
				printErrorCode(600);//if method fails, print error code
			}
		}
		else if(strcmp(tmp,"PRINT_BP")== 0)//if tmp is "PRINT_BP"
		{
			char* PBcmd = strtok(NULL," ");
			if(PBcmd!=NULL){printErrorCode(700); continue;}//if parameter is exceed, print error code
			if(bp->isEmpty()==true)//if B+ tree is Empty, print error code
			{
				printErrorCode(700);
			}
			else
			{
				bp->Print();//print all Data in tree
			}
		}
		else if(strcmp(tmp,"EXIT")== 0)//tmp is "EXIT"
		{
			delete bp;//delete B+ tree and all Data of B+ tree
			delete avl;//delete AVL tree and all Data of AVL tree
			Print_vector.clear();//clear Vector
			fin.close();//file close
			flog.close();
			printSuccess("EXIT");//print success code
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
		bp->Insert(VData);//insert Vaccine data in tree
	}
	return true;

}

bool Manager::VLOAD() {
	if(avl->isEmpty()==true)//if AVL tree is Empty, return false
	{
		return false;
	}
	if(Print_vector.empty()==false)//if Vector is not Empty, clear Vector
	{
		Print_vector.clear();
	}
	avl->GetVector(Print_vector);//Load all data of AVL tree in Vector
	return true;
}

bool Manager::ADD(char* name, char* Vname, int age, char* location) {//insert data B+ tree and AVL tree or update Vaccine time
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
		if(VNode->GetVaccineName().compare("Janssen")==0)//if Vaccine is "Janssen", insert data in AVL tree
		{
			avl->Insert(VNode);
		}
		bp->Insert(VNode);//insert data in B+ tree
	}
	else
	{
		VaccinationData* v = tmpNode->getDataMap()->find(name)->second;
		if(v->GetVaccineName().compare("Janssen")==0)//if Vaccine name is janssen
		{
			if(v->GetTimes()<1)
			{
				v->SetTimesInc();//increas Vaccint time
				avl->Insert(v);//insert data to complete vaccine
			}
		}
		else//if Vaccine name is not janssen
		{
			if(v->GetTimes()==0)//if vaccine time is zero, increase vaccine time
			{
				v->SetTimesInc();
			}
			else if(v->GetTimes()==1)//if vaccine time is one, increase vaccine time and insert data in AVL tree
			{
				v->SetTimesInc();
				avl->Insert(v);
			}
		}
	}
	/*print Data information to ADD*/
    fout << "========== " << "ADD" << " ==========" << endl;
    fout << name<<" "<<Vname<<" "<<age<<" "<<location<<endl;
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

bool Manager::SEARCH_BP(string name) {//Find the data in the tree with name
	if(bp->isEmpty()==true)//if tree is empty, return false
	{
		return false;
	}
	BpTreeNode* tmpNode = bp->searchDataNode(name);//tmpnode that has name information in B+ tree
	if(tmpNode==nullptr)//if it not exist Data
	{
		return false;
	}
	for(auto it=tmpNode->getDataMap()->begin();it!=tmpNode->getDataMap()->end();it++)//searching tmpnode
	{
		if(name.compare(it->first)==0)
		{
			VaccinationData* v=it->second;
			ofstream fout;
			fout.open("log.txt", ofstream::app);
			fout << "========== " << "SEARCH_BP" << " ==========" << endl;
    		fout << v->GetUserName()<<" "<<v->GetVaccineName()<<" "<<v->GetTimes()<<" "<<v->GetAge()<<" "<<v->GetLocationName()<<endl;//print information of Data to fine 
    		fout << "============================" << endl << endl;
			fout.close();
			return true;
		}
	}
	return false;
}

bool Manager::SEARCH_BP(string start, string end) {//print Node's VaccineData in charactor's range
	if(bp->isEmpty()==true)//if tree is empty, return false
	{
		return false;
	}
	if(start[1]!='\0'||end[1]!='\0')//if start and end are not Alphabat
	{
		return false;
	}
	bp->SearchRange(start,end);//Call SearchRange Method in BpTree class
	return true;
}

bool Manager::SEARCH_AVL(string name) {//Find the data in the tree with name
	VaccinationData* v = avl->Search(name);//v that has name information in AVL tree
	if(avl->isEmpty()==true)//if avl is Empty, return false
	{
		return false;
	}
	if(v==nullptr)//if can't find data, return false
	{
		return false;
	}
	ofstream fout;
	fout.open("log.txt", ofstream::app);
    fout << "========== " << "PRINT_AVL" << " ==========" << endl;
    fout << v->GetUserName()<<" "<<v->GetVaccineName()<<" "<<v->GetTimes()<<" "<<v->GetAge()<<" "<<v->GetLocationName()<<endl;//print information of data to find
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

bool Compare(VaccinationData* vac1, VaccinationData* vac2) {//Method for vector to sort
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
			return name1 < name2;//name: Climbing order
		}
		else
		{
			return vac1->GetAge()<vac2->GetAge();//Age: Climbing order
		}
	}
	else
	{
		return Vname1<Vname2;//Vaccine name: Climbing order
	}
}

bool Compare2(VaccinationData* vac1, VaccinationData* vac2) {//Method for vector to sort
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
			return name1 < name2;//name: Climbing order
		}
		else
		{
			return vac1->GetAge() > vac2->GetAge();//Age: decending order
		}
	}
	else
	{
		return Lname1<Lname2;//Location name: Climbing order
	}
}

bool Manager::VPRINT(string type_) {//print all Data of Vector
	if(avl->isEmpty()==true)//if AVL tree is empty, return false
	{
		return false;
	}
	if(Print_vector.empty()==true)//if Print_vector is empty, return false
	{
		return false;
	}
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	if(type_.compare("A")==0)//if type_ is "A", print Data according to the rules
	{
		fout << "========== " << "VPRINT A" << " ==========" << endl;
		sort(Print_vector.begin(), Print_vector.end(),Compare);//sort data of Vector according to the rules
		for(int i=0;i<Print_vector.size();i++)//print data of vector 
		{
			fout<<Print_vector[i]->GetUserName()<<" "<<Print_vector[i]->GetVaccineName()<<" "<<Print_vector[i]->GetTimes()<<" "<<Print_vector[i]->GetAge()<<" "<<Print_vector[i]->GetLocationName()<<endl;
		}
	}
	else if(type_.compare("B")==0)//if type_ is "B", print Data according to the rules
	{
		fout << "========== " << "VPRINT B" << " ==========" << endl;
		sort(Print_vector.begin(), Print_vector.end(),Compare2);//sort data of Vector according to the rules
		for(int i=0;i<Print_vector.size();i++)//print data of vector 
		{
			fout<<Print_vector[i]->GetUserName()<<" "<<Print_vector[i]->GetVaccineName()<<" "<<Print_vector[i]->GetTimes()<<" "<<Print_vector[i]->GetAge()<<" "<<Print_vector[i]->GetLocationName()<<endl;
		}		
	}
    fout << "============================" << endl << endl;
	fout.close();
	return true;
}

void Manager::printErrorCode(int n) {//Method for print error code
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	fout << "========== ERROR ==========" <<endl;
	fout << n << endl;
	fout << "===========================" << endl << endl;
	fout.close();
}

void Manager::printSuccess(char* act)//Method for print success code
{
	ofstream fout;
	fout.open("log.txt", ofstream::app);
    fout << "========== " << act << " ==========" << endl;
    fout << "Success" << endl;
    fout << "============================" << endl << endl;
	fout.close();
}

bool Manager::CheckNum(char* str){//Method check wrong data
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

