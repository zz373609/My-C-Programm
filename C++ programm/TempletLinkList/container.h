//***************************
//Name: Zhiqiang Zhang
//Date: 7/21/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: container.h
//***************************
#ifndef CONTAINER_H
#define CONTAINER_H
#include<iostream>
#include"node.h"


class contain{

public:
contain(); //consturtor
~contain(); //big3
contain(const contain& other);
void operator = (const contain&n);
node* copy_list(const node* original); //the copy function to copy the list
void set_name(std::string n);
std::string get_name();
void change_name(std::istream & ins);  //the function the change the name and enter the name 
void insert_front(course& add); //this function is to enter the information to the beginning of the list
void insert_back(course& add);//this function is to enter the information to end of the list
void insert_course(course& v1); //this function is to check the head and find the place to enter the information to the list
void remove(std::string& rm_course);//remove the information of the list
void show_list(std::ostream& ous);//output the course information
void output_name(std::ostream& ous);//output the student name
double total_hours();//get the total hors
double GPA();//get the gpa
void filein(std::istream& ins);//filein the course information
void name_filein(std::istream& ins);//filein the name 
private:
std::string name;
node* head;
};

void meau();
#endif