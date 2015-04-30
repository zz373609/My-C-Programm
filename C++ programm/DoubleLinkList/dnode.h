//***************************
//Name: Zhiqiang Zhang
//Date: 7/27/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: colorful program
//***************************
#ifndef DNODE_H
#define DNODE_H
#include<iostream>

template<class T>
class dnode{
public:
dnode(const T& init_data = T(),dnode* init_link = NULL, dnode* init_link1 = NULL)
{data_filed = init_data;previous_link_filed=init_link;next_link_filed=init_link1;}
T data(){return data_filed;}
dnode* previous_link(){return previous_link_filed;}
dnode* next_link(){return next_link_filed;}
void set_data(T& new_data){data_filed = new_data;}
void set_previous_link(dnode* newlink){previous_link_filed = newlink;}
void set_next_link(dnode* newlink){next_link_filed = newlink;}
private:
T data_filed;
dnode* previous_link_filed;
dnode* next_link_filed;
};
#endif