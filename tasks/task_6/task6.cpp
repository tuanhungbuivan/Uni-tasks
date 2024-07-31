#include <iostream>
#include <vector>

using namespace std;

void reverse_output(vector<string> arr,int n)
{
     cout<<arr[n-1]<<",";
     n--;
     if(n>0) reverse_output(arr,n);
}

int main()
{
     vector<string> arr{"a","b","c","d","e","f","g","h","i","j"};

     reverse_output(arr,arr.size());
}
