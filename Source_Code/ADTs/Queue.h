#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include"Node.h"
using namespace std;

template <class T>
class Queue{
    Node<T>*front;
    
    Node<T>*rear;
    
    int Count=0;

public:
    Queue(){
        
        front=nullptr;
        
        rear=nullptr;
    }

    ~Queue(){}

    bool isEmpty(){
        return front == NULL;
    }

    bool enqueue(const T&item){
        
        Node<T>*newNode = new Node<T>(item);
        
        if(!newNode) return false;//in case compiler failed to allocate memory for newNode ptr
        
        if(rear) rear->setNext(newNode);
        
        rear=newNode;
        
        if(!front) front = newNode;
        
        Count++;
        
        return true;
    }
    
    bool dequeue(T&item){
        
        if(isEmpty()) return false;
        
        item = front->getItem();
        
        Node<T>*tmp = front;
        
        if(rear == front) rear = nullptr; // rear = rear->getNext(); should be equivalent here; returns nullptr too
        
        front = front->getNext();
        
        delete tmp;
        
        Count--;
        
        return true;
        
    }
    
    T peek(){
        
        if(isEmpty()) return static_cast<T>(NULL);
        
        return front->getItem();
    }

    void printQueue(){
        Node<T>*ptr=front;

        while(ptr){

            cout<<*(ptr->getItem());// remember to ask about that; this print function assumes that item is always a pointer

            if(ptr->getNext() != nullptr) cout << ",";

            ptr=ptr->getNext();
        }
    }
    
    int getCount()const{return Count;}
};


#endif // QUEUE_H
