//***************************
//Name: Zhiqiang Zhang
//Date: 7/27/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: colorful program
//***************************
#ifndef DLIST_H
#define DLIST_H
#include<iostream>
#include"dnode.h"
#include"swatches.h"
#include"iterator.h"



template <class T>
class dlist{
public:
typedef node_iterator<T> iterator;
dlist();//constructor
~dlist();//destructor
dlist(const dlist<T>& other);//copy constructor
void operator = (const dlist<T>*& other);//asssgment operator
void dlist_insert_front(T& entry);//insert color from front
void dlist_insert_back(T& entry);//insert color from back
void dlist_insert_before(iterator it, T& entry);//insert color by iterator, and insert color before it
void dlist_insert_after(iterator it, T& entry);//insert color by iterator, and insert color after it
void dlist_remove_front();//remove color from front
void dlist_remove_back();//remove color from back
void dlist_remove_it(iterator it);//remove color with current iterator
iterator start() {return iterator(head);}//start at head
iterator r_start(){return iterator(tail);}//start at tail
iterator r_end(){return iterator(NULL);}//end by NULL
iterator end(){return iterator(NULL);}//end by NULL
int get_used(){return used;}//return the node used

private:
dnode<T>* head;
dnode<T>* tail;
int used;

};

#include"dlist.template"
#endif