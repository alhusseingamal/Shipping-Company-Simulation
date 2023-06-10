#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
using namespace std;

//Assume our familiar Node class added to it an int data member called priority
// with setters and getters for it

// the higher the value of priority, the higher the priority
template<typename T>

class PriorityQueueNode{

    T Item;
    
    int priority;
    
    PriorityQueueNode<T>* next;

public:

    PriorityQueueNode(){next=nullptr;}

    PriorityQueueNode(T it){Item=it; next=nullptr;}
    
    PriorityQueueNode(T it, int p){Item=it; priority=p; next=nullptr;}
    
    void setItem(T &it){Item = it;}
    
    T getItem() const {return Item;};
    
    void setPriority(const int p){priority = p;}
    
    int getPriority()const{return priority;}
    
    PriorityQueueNode<T>* getNext() const {return next;}  
    
    void setNext(PriorityQueueNode<T>* ptr){next = ptr;}
    
    ~PriorityQueueNode(){next = nullptr;}

};

template<class T>

class PriorityQueue
{
    PriorityQueueNode<T>*front;
    
    PriorityQueueNode<T>*rear;
    
    int Count=0;
public:
    
    PriorityQueue(){front=nullptr;rear=nullptr;}
    
    ~PriorityQueue(){}
    
    bool isEmpty(){return front == nullptr;}
    
    bool enqueue(const T&item, const int p){
    
        PriorityQueueNode<T>*newPriorityQueueNode = new PriorityQueueNode<T>(item,p);

        if(!newPriorityQueueNode) return false; // in case compiler fails to allocate, which is very unlikely
        
        if(isEmpty()){
        
            front = newPriorityQueueNode;
            
            rear = newPriorityQueueNode;
            
            Count++;
            
            return true;
        }
        
        PriorityQueueNode<T>*ptr = front;
        
        while(ptr->getNext() && ptr->getNext()->getPriority() >= newPriorityQueueNode->getPriority())
            ptr=ptr->getNext();
            
        if(ptr == front && ptr->getPriority() < newPriorityQueueNode->getPriority()){
            
            newPriorityQueueNode->setNext(front);
            
            front = newPriorityQueueNode;
            
            Count++;
            
            return true;
        }
        
        newPriorityQueueNode->setNext(ptr->getNext());
        
        ptr->setNext(newPriorityQueueNode);
        
        Count++;
        
        return true;        
    }
    bool dequeue(T&item){
        
        if(isEmpty()) return false;
        
        item=front->getItem();
        
        PriorityQueueNode<T>*tmp=front;
        
        if(rear==front) rear=nullptr;
        
        front=front->getNext();
        
        delete tmp;
        
        Count--;
        
        return true;
    }
    
      T peek(){
        if(isEmpty()) return nullptr;
        return front->getItem();
    }
    
    bool enqueueFront(const T&item){
        
        PriorityQueueNode<T>*newPriorityQueueNode = new PriorityQueueNode<T>(item); 
        
        if(!newPriorityQueueNode) return false;
        
        if(front) newPriorityQueueNode->setNext(front);
        
        front = newPriorityQueueNode;
        
        if(!rear) rear = newPriorityQueueNode;
        
        return true;
    }
    
    void printPriQueue(){
        
        PriorityQueueNode<T>*ptr=front;
        
        while(ptr){
            cout<<*(ptr->getItem());// remember to ask about that; this print function assumes that item is always a pointer
            if(ptr->getNext()!=nullptr)cout<<",";
            ptr=ptr->getNext();
        }
    }

int getCount()const{return Count;}

};


#endif // PRIORITYQUEUE_H
