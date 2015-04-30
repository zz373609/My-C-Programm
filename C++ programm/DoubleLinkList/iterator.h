//***************************
//Name: Zhiqiang Zhang
//Date: 7/27/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: colorful program
//***************************
#ifndef ITERATOR_H
#define ITERATOR_H
#include"dlist.h"

template<class T>
class dlist;

template<class T>
class node_iterator{
public:
friend class dlist<T>;
node_iterator(dnode<T>* init = NULL){current = init;}
bool operator != (const node_iterator other){return current != other.current;}const
bool operator == (node_iterator other){return current == other.current;}const
T operator *(){return current->data();}const 
node_iterator operator ++(){
current = current->next_link();
return *this;
}
node_iterator operator ++(int){
node_iterator orignal(*this);
current = current->next_link();
return orignal;
}
node_iterator operator --(){
current = current->previous_link();
return *this;
}
node_iterator operator --(int){
node_iterator orignal(*this);
current = current->previous_link();
return orignal;
}
dnode<T>* get_it(){return current;}
private:
dnode<T>* current;
};
#endif