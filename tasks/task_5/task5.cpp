#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

class Tree
{
private:
     std::string name;
     std::vector<std::shared_ptr<Tree>> children;
public:
     Tree(const std::string &name):name(name) { }

     std::shared_ptr<Tree> AddSub(const std::string &name)
     {
          std::shared_ptr<Tree> node=std::make_shared<Tree>(name);
          children.push_back(node);
          return node;
     }
     void print(int nest, bool ok,std::string prefix = "")const
     {
          std::cout<<std::string(nest,'\t');
          if(ok) std::cout<<prefix<<" ";
          std::cout<<name<<std::endl;

          for(int i=0;i<children.size();i++){
               std::string new_prefix = prefix + std::to_string(i + 1) + '.';
               children[i]->print(nest, ok, new_prefix);
          }
     }
     int GetSubCount()
     {
          int countsub=0;
          for(const std::shared_ptr<Tree> node:children) countsub++;
          return countsub;
     }
     int GetAllSubCount()const
     {
          int getallsubcount=0;
          for(const std::shared_ptr<Tree> node:children){
               int countsub = node->GetAllSubCount()+1;
               getallsubcount+=countsub;

          }
          return getallsubcount;

     }
     void Del(int nest)
     {
          children.erase(children.begin()+nest);
     }
};

int main()
{
     std::shared_ptr<Tree> root=std::make_shared<Tree>("tree name");
     std::shared_ptr<Tree> galaz1 = root->AddSub("galaz 1");
     std::shared_ptr<Tree> galaz2 = root->AddSub("galaz 2");
     std::shared_ptr<Tree> galaz3 = root->AddSub("galaz 3");
     std::shared_ptr<Tree> galaz1_1 = galaz1->AddSub("galaz 1.1");
     std::shared_ptr<Tree> galaz2_1 = galaz2->AddSub("galaz 2.1");
     std::shared_ptr<Tree> galaz2_2 = galaz2->AddSub("galaz 2.2");
     std::shared_ptr<Tree> galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.2");
     root->print(0,true);
     std::cout<<std::endl;

     uint32_t rootChildrenCnt = root->GetSubCount(); // result shall be 3
     uint32_t galaz1childrenCount = galaz1->GetSubCount(); // result shall be 1
     uint32_t countOfAllChildren = root->GetAllSubCount(); // result shall be 7 (recursive children counting)
     std::cout<<"root children: "<<rootChildrenCnt<<std::endl;
     std::cout<<"galaz1 children: "<<galaz1childrenCount<<std::endl;
     std::cout<<"countOfAllChildren: "<<countOfAllChildren<<std::endl;

     std::cout<<std::endl;
     root->Del(1); // will remove galaz_2 with all it's children (recursive), so in a result only galaz_1 and galaz_3 will stay
     root->print(0,true);
     std::cout<<std::endl;

     uint32_t rootChildrenCnt_v2 = root->GetSubCount(); // result shall be 2
     uint32_t countOfAllChildren_v2 = root->GetAllSubCount(); // result shall be 3 (recursive children counting)
     std::cout<<"root children: "<<rootChildrenCnt_v2<<std::endl;
     std::cout<<"countOfAllChildren: "<<countOfAllChildren_v2<<std::endl;
     std::cout<<std::endl;
     return 0;
}
