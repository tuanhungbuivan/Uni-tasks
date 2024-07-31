#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Tree
{
private:
     ofstream ofs;
public:
     string name ;
     vector<Tree*> children;

     Tree(const string &name):name(name) { }

     ~Tree()
     {
          for(const Tree* node:children)
          {
               delete node;
          }
     };

     Tree* AddSub(const string &name)
     {
          Tree *node= new Tree(name);
          children.push_back(node);
          return node;
     }

     void print(int nest)const
     {
          cout<<string(nest,'\t')<<name<<endl;
          ++nest;
          for(const Tree *node:children) node->print(nest);
     }

     uint32_t GetSubCount()
	{
          return this->children.size();
	}

	uint32_t GetAllSubCount() const
	{
          uint32_t getall = 0;
          for(const Tree* node:children)
          {
               uint32_t countsub = node->GetAllSubCount()+1;
               getall+=countsub;
          }
          return getall;
	}

	void Del(int nest)
	{
	     delete children[nest];
          children.erase(children.begin()+nest);
	}

	void print1(int nest, bool ok,string prefix = "")const
     {
          cout<<std::string(nest,'\t');
          if(ok) cout<<prefix<<"";
          cout<<name<<endl;

          for(int i=0;i<children.size();i++){
               string new_prefix = prefix + to_string(i + 1) + '.';
               children[i]->print1(nest+1, ok, new_prefix);
          }
     }
     //task 4
     ofstream& save(ofstream &ofs, int nest) 
     {
          ofs<<string(nest,'\t')<<name<<endl;
          ++nest;
          for(Tree *node:children) node->save(ofs, nest);

          return ofs;
     }

     void savetomyfile(string filename)
     {
          ofs.open(filename,ios::out);
          if(ofs.is_open())
          {
               save(ofs, 0);
          }
     }
};

int main()
{
     Tree* root = new Tree("tree name");
     Tree* galaz1 = root->AddSub("galaz 1"); // this function creates a child Tree object and returns pointer to it
     Tree* galaz2 = root->AddSub("galaz 2");
     Tree* galaz3 = root->AddSub("galaz 3");
     Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");
     Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");
     Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");
     Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.2");
     // after execution
     root->print(0);
     cout<<endl;
     root->print1(0,true);
     cout<<endl;

     root->savetomyfile("serialize2.txt");

     uint32_t rootChildrenCnt = root->GetSubCount(); // result shall be 3
     uint32_t galaz1childrenCount = galaz1->GetSubCount(); // result shall be 1
     uint32_t countOfAllChildren = root->GetAllSubCount(); // result shall be 7 (recursive children counting)
     cout<<"rootChildrenCnt :"<<rootChildrenCnt<<endl;
     cout<<"galaz1childrenCount :"<<galaz1childrenCount<<endl;
     cout<<"countOfAllChildren :"<<countOfAllChildren<<endl;

     root->Del(1); // will remove galaz_2 with all it's children (recursive), so in a result only galaz_1 and galaz_3 will stay
     root->print(0);
     cout<<endl;
     root->print1(0,true);
     cout<<endl;

     uint32_t rootChildrenCnt_v2 = root->GetSubCount(); // result shall be 2
     uint32_t countOfAllChildren_v2 = root->GetAllSubCount(); // result shall be 3 (recursive children counting)
     std::cout<<"root children: "<<rootChildrenCnt_v2<<std::endl;
     std::cout<<"countOfAllChildren: "<<countOfAllChildren_v2<<std::endl;
     cout<<endl;



     delete(root);  // deleting root shall remove all children (recursive) and clean memory
     root = NULL;

     cout<<"lol"<<endl;
}
