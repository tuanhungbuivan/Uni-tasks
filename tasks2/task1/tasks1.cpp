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


int main()
{
     Stack<int> stack1;

     stack1.add(5);
     stack1.add(6);
     stack1.add(7);
     stack1.add(9);
     stack1.add(11);

     stack1.printlist();

     cout<<"Number of elements: ";
     cout<<stack1.getcounts()<<endl;

     cout<<"Size of the list in bytes: ";
     cout<<stack1.getsize()<<endl;

     cout<<"Return a number from the top: ";
     cout<<stack1.getfromtop()<<endl;

     cout<<"Return a number from the top: ";
     cout<<stack1.getfromtop()<<endl;

}
