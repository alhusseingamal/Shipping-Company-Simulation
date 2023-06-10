#ifndef NODE_H
#define NODE_H

template<typename T>

class Node{
    
  T Item;

  Node<T>* next; // a pointer to the next node

public:

    Node(){next=nullptr;}

    Node(T it){Item=it; next=nullptr;}

    void setItem(T &it){Item = it;}

    T getItem() const {return Item;};

    Node<T>* getNext() const {return next;} // const func since it is not allowed to edit anything inside

    void setNext(Node<T>* ptr){next = ptr;}

    ~Node(){next = nullptr;} // the safe practice is to always set pointers to null when not used
};

#endif // NODE_H