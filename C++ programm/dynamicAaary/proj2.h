//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The information of birthday
// 
//  Date    :  2013/7/14
#ifndef PROJ2_H
#define PROJ2_H
#include<iostream>
#include"date.h"

class arry{

public:
arry();
~arry();
arry(const arry& n);
void operator = (const arry&n);
std::size_t get_used();
std::size_t get_current();
void insert(Date& item);
void display(std::ostream&ous);
void attach(Date& item);
void insert_before(Date& itme);
void start_before();
void search_by_date();
void remove_current(std::size_t index);
void remove();
void start();
bool is_item();
void advance();
void filein(std::istream& ins);

private:
Date* ptr;
std::size_t capacity;
std::size_t used;
std::size_t current;
void resize();
};

void meau();
#endif