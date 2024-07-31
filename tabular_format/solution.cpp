#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#define n 13
// 1235 2 33533 4 5 6 7 8 9 10 11 12 1


void divider(int K,int maxl)
{
     string row = "+";
     for(int i=0;i<K;i++){
          for(int j=0;j<maxl;j++){
               row+="-";
          }
          row+="+";
     }
     cout<<row;
}

void printnums(int K,vector<int> A,int maxl,int b)
{
     string s[n];
     for(int i=0+(K*b);i<K*(b+1);i++){
          stringstream ss;
          ss<<A[i];
          string str = ss.str();
          s[i] = str;
     }
     string row = "|";
     for(int i=0;i<K;i++){
          int l = maxl - s[i+K*b].length();
          string c="";
          for(int j=0;j<l;j++){
               c=c+" ";
          }
          c = c + s[i+K*b];
          row = row + c;
          row+="|";
     }
     cout<<row;
}

void printnumsRES(int K,vector<int> A,int maxl)
{
     string s[n];
     for(int i=n-K;i<n;i++){
          stringstream ss;
          ss<<A[i];
          string str = ss.str();
          s[i] = str;
     }
     string row = "|";
     for(int i=0;i<K;i++){
          int l = maxl - s[i+n-K].length();
          string c="";
          for(int j=0;j<l;j++){
               c=c+" ";
          }
          c = c + s[i+n-K];
          row = row + c;
          row+="|";
     }
     cout<<row;
}

void solution(vector<int> &A, int K)
{
     int sa = A.size();
     int findmax=INT_MIN;
     for(int i=0;i<n;i++){
          if(findmax<A[i]) findmax=A[i];
     }
     stringstream ss;
     ss<<findmax;
     string str = ss.str();

     int maxl = str.length();

     int rows = sa/K;
     int rows_left = sa%K;

     for(int i=0;i<rows;i++){
          divider(K,maxl);
          cout<<endl;
          printnums(K,A,maxl,i);
          cout<<endl;
     }
     if(rows_left == 0){
          divider(K,maxl);
     }else{
          divider(K,maxl);
          cout<<endl;
          printnumsRES(rows_left,A,maxl);
          cout<<endl;
          divider(rows_left,maxl);
     }
}


int main()
{
     vector<int> A;

     int numbers;
     int K;

     cout<<"Insert a number of rows you want in the tabular: ";
     cin>>K;

     cout<<endl;
     for(int i=0;i<n;i++){
          cin>>numbers;
          A.push_back(numbers);
     }

     solution(A,K);
}
