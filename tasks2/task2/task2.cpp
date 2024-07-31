#include <iostream>

using namespace std;

template <class T> class Node
{

public:
     T data;
     Node *next = NULL;
};


template <class T> class Stack
{
public:
     void printlist();
     void add(T data);
     int getcounts();
     T getfromtop();
     int getsize();

     Node< T > *head, *tail;

     Stack()
     {
          head = NULL;
          tail = NULL;
     }
};

template <class T>
void Stack< T >::add( T data )
{
     Node <T> *p = new Node<T>;
     p->data = data;

     if(head == NULL){
          head = p;
          tail = head;
     }else{
          p->next = NULL;
          tail->next = p;
          tail = tail->next;
     }
}

template <class T>
void Stack< T >::printlist()
{
     Node<T> *current;

     current = head;
     cout<<"Inserted elements: ";
     if ( current == NULL ) return;
     while(current != NULL){
          cout<<current->data<<" ";
          current = current->next;
     }
     cout<<endl;
}

template <class T>
T Stack< T >::getfromtop()
{
     Node<T> *current = head;

     if ( current == NULL ) return;

     int count1 = getcounts();

     if(count1 == 1)
     {
          T data1 = current->data;

          delete head;
          head = NULL;
          tail = NULL;

          return data1;
     }else{
          while(current->next->next != NULL ) current = current->next;

          T data1 = current->next->data;
          current->next = NULL;
          delete tail;
          tail = current;

          return data1;
     }

}


template <class T>
int Stack< T >::getcounts()
{
     Node<T> *current;

     current = head;
     int counts = 0;

     while(current != NULL){
          counts++;
          current = current->next;
     }

     return counts;
}

template <class T>
int Stack< T >::getsize()
{
     Node<T> *current;
     current = head;

     int sizeinbytes=0;
     while(current != NULL){
          sizeinbytes += sizeof(current);
          current = current->next;
     }
     return sizeinbytes;
}

template <class T>
class Inher : public Stack<T>
{
public:

     T* getfrombottom()
     {
          int count1 = this->getcounts();
          if(this->head == NULL) cout<<"List is empty"<<endl;

          Node<T> *current = this->head;

          if(count1 == 1)
          {
               T data = current->data;
               delete this->head;
               this->head = NULL;
               this->tail = NULL;

               return data;
          }else{
               T data = current->data;

               this->head = current->next;
               delete current;

               return data;
          }
     }

     T* getfromanywhere(unsigned int x)
     {
          Node<T> *current = this->head;
          if(this->head == NULL) cout<<"List is empty"<<endl;

          int counts = this->getcounts();

          if(x>counst-1) return nullptr;

          if(x == 0)
          {
               T data = current->data;
               this->head = current->next;
               delete current;
               return data;

          }else if(x == counts-1){

               while(current->next->next != NULL ) current = current->next;

               T data1 = current->next->data;
               
               current->next = NULL;
               delete this->tail;
               this->tail = current;

               return data1;

          }else{

               for(int i=0;current != NULL && i < x-1; i++) current = current->next;

               T data = current->next->data;

               Node<T> *next = current->next->next;
               delete current->next;

               current->next = next;

               return data;
          }
     }

     void addmiddle(T data,int x)
     {
          Node<T> *new_ele = new Node<T>();
          new_ele->data = data;
          new_ele->next = NULL;

          if(x == 0)
          {
               new_ele->next = this->head;
               this->head = new_ele;
               this->tail = this->head;
          }else{
               Node<T> *temp = this->head;

               while(--x > 0) temp = temp->next;

               new_ele->next = temp->next;
               temp->next = new_ele;

          }
     }

};

int main()
{
     Inher<int> inher;

     inher.add(5);
     inher.add(6);
     inher.add(7);
     inher.add(9);
     inher.add(11);

     inher.printlist();

     int x;
     cout<<"Choose a position from 0 to "<<inher.getcounts()-1<<" you want to return: ";
     cin>>x;

     if(x>inher.getcounts()-1) cout<<"The number is to big"<<endl;
     else if(x<0) cout<<"The number is invalid"<<endl;
     else{
          cout<<"The number from position "<<x<<" is: ";
          cout<<inher.getfromanywhere(x)<<endl;
     }
     inher.printlist();

     int y;
     cout<<"Choose a position from 0 to "<<inher.getcounts()-1<<" you want to insert a data: ";
     cin>>y;

     if(y>inher.getcounts()) cout<<"The number is to big"<<endl;
     else if(y<0) cout<<"The number is invalid"<<endl;
     else inher.addmiddle(15,y);
     inher.printlist();

     cout<<"Return a number from the bottom: ";
     cout<<inher.getfrombottom()<<endl;
     inher.printlist();

}
