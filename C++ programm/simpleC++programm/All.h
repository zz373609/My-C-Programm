//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The colloction of DVD
// 
//  Date    :  2013/7/8
#ifndef ALL_H
#define ALL_H
#include"DVD.h"


class All{
static const size_t SIZE=1000;

public:
All();
int get_used();
void insert(std::istream&ins);
void display(std::ostream& ous);
void remove();
void search_by_title();
void sort_by_title();
void sort_by_year();
void display_by_rating(std::ostream& ous);
void load_file(std::istream& ins);


private:
int used;
DVD dvd[SIZE];
};

void meau();
#endif
