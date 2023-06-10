#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"
using namespace std;

template <class T>

class LinkedList{
    
    Node<T>*head;
    
    int Count=0;//list size
    
public:
  LinkedList():head(nullptr){}

  void print(){
    if(!head) return;// to be removed later
    Node<T>* ptr=head;
    while(ptr){
        cout<<*(ptr->getItem());// assumes element is always pointer, should be edited later
        if(ptr->getNext()!=nullptr)cout<<",";
        ptr=ptr->getNext();
    }
}

Node<T>* getHead(){
    return head;
}

int getCount()const{return Count;}

bool isEmpty(){
    
    if(head == nullptr) return true;
    
    return false;
}

Node<T>* traverse(){
    
    Node<T>* ptr = head;
    
    if(ptr)
        while(ptr->getNext()) 
            ptr = ptr->getNext();
    return ptr; // returns the ptr pointing to the last element in the list
}

void Remove(T& it){
    Node<T>* ptr = head;
    
    if(ptr->getItem()==it){ // first check if head is the target node
        Node<T>*tmp = ptr;
        head=ptr->getNext();
        delete tmp;
        Count--;
        return;
    }
    while(ptr->getNext() && ptr->getNext()->getItem()!=it){
        ptr=ptr->getNext();
    }
    Node<T>*tmp = ptr->getNext();
    ptr->setNext(ptr->getNext()->getNext());
    delete tmp;
    Count--;
}

T getEntry(int pos){
    Node<T>*ptr=head;
    for(int i=1;i<=Count;i++){
        if(pos==i) return ptr->getItem();
        ptr=ptr->getNext();
    }
    return nullptr;// msh 3arf dah leh msh mtl3 error bs sybo delwa2ty talma shayl l warning
}

void insertLast(const T& it){
    
    
    Node<T>*newNode = new Node<T>(it);
    
    Node<T>*ptr = traverse();
    
    if(ptr) ptr->setNext(newNode);
    
    else{head = newNode;}
    
    Count++;
}

void insertFirst(const T& it){
    
    Node<T>*newNode = new Node<T>(it);
    
    newNode->setNext(head);
    
    head = newNode;
    
    Count++;
}

void RemoveLast(){
    Node<T>*ptr=head;
    while(ptr->getNext()->getNext()){ // as long as the next element has no next, then it is not the last
        ptr=ptr->getNext();
    }
    // at this point ptr is pointing to the elem whose next elem has no next elem.,that is the 2nd to last elem.
    delete ptr->getNext();
    ptr->setNext(nullptr);
    Count--;
}

bool RemoveFirst(T&it){ // removes the first element in the list, and returns it
    if(this->getCount() == 0) return false;
    it = head->getItem();
    Node<T>*tmp = head; // fekrt l shma3a
    head = head->getNext();
    delete tmp;
    Count--;
    return true;
}

  void DeleteALL(){
      Node<T>*ptr=head;
      while(ptr){
        ptr=head->getNext();
        delete head;
        head=ptr;
      }
  }  
  
};
#endif // LINKEDLIST_H



