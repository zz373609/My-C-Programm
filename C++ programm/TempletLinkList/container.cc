//***************************
//Name: Zhiqiang Zhang
//Date: 7/21/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: container.cc
//***************************
#include<iostream>
#include"container.h"
using namespace std;

contain::contain(){  //constructor
name = "";
head = NULL;
}

contain::~contain(){  //destructor
node* rm;
while(head!=NULL){
rm = head;
head = head->link();
delete rm;
}
}

node* contain::copy_list(const node* original){  //copy function to copy a new list
if(original==NULL)
return NULL;
node* newlist;
const node* cursor;
node* creat;
newlist = new node(original->data());
creat = newlist;
cursor = original->link();
while(cursor!=NULL){
creat->set_link(new node(cursor->data()));
creat = creat->link();
cursor= cursor->link();
}
return newlist;
}


contain::contain(const contain& other){   //copy constructor
head = copy_list(other.head);
}

void contain::operator = (const contain&other){
if(this==&other)    //assignment operator
return;
else{
node* rm;
while(head!=NULL){
rm = head;
head = head->link();
delete rm;
}
head = copy_list(other.head);
}

}


void contain::set_name(std::string n){
name = n;
}

std::string contain::get_name(){
return name;
}

void contain::change_name(std::istream & ins){
 if(ins==cin)    //this function is to enter the name and change the name
  {
 char junk;
  cout<<"Please enter your current name > ";
  if(cin.peek()=='\n')
  cin.get(junk);
  getline(ins,name);
 }
 else
 getline(ins,name);
}

void contain::insert_front(course& add){
if(head == NULL){    //insert the information in the beginning of the list
head = new node;
head->set_data(add);
head->set_link(NULL);
}
else{
node* temp = new node;
temp->set_data(add);
temp->set_link(head);
head = temp;
}

}
void contain::insert_back(course& add){
node* corsor;  //insert the information in the end of the list
node* temp = new node;
for(corsor=head;corsor->link()!=NULL;corsor=corsor->link());
corsor->set_link(temp);
temp->set_data(add);
temp->set_link(NULL);

}




void contain::insert_course(course& v1){
if(head==NULL)
insert_front(v1);
else{
if(v1<head->data()){    //insert function
insert_front(v1);
return;
}
}
node* corsor=head;
while(corsor->link()!=NULL){
if(corsor->link()->data()<v1)
corsor = corsor->link();
else{
node* temp = new node;
temp->set_data(v1);
temp->set_link(corsor->link());
corsor->set_link(temp);
return;
}
}
if(corsor->data()<v1)
{
insert_back(v1);
return;
}
}


void contain::show_list(std::ostream& ous){
if(ous==cout){
for(node*corsor = head;corsor!=NULL;corsor=corsor->link())    //output the list but not include the name
ous<<corsor->data()<<endl;
}
else{
for(node*corsor = head;corsor!=NULL;corsor=corsor->link())
ous<<corsor->data();
}
}


void contain::output_name(std::ostream& ous){
ous<<name<<endl;   //output the name but not include the course information
}


void contain::remove(std::string& rm_course){
node* corsor;
node* rm;
for(corsor = head;corsor!=NULL;corsor=corsor->link()){   //this function is to drop the class of list
if(corsor->data().get_course_number() == rm_course){
if(head->data().get_course_number()==rm_course){
rm = head;
head = head->link();
delete rm;
}
else{
node* corsor1;
node* pre;
corsor1 = head;
while(corsor1!=NULL&&corsor1->data().get_course_number()!=rm_course){
pre = corsor1;
corsor1 = corsor1->link();
}
pre->set_link(corsor1->link());
delete corsor1;
}
}
}
}

double contain::total_hours(){  //return total hours
double sum = 0;
for(node*corsor=head;corsor!=NULL;corsor=corsor->link()){
sum = sum + corsor->data().get_hours();
}
return sum;
}



double contain::GPA(){
double sum1 = 0;   //return gpa
double sum2 = 0;
double gpa;
for(node*corsor=head;corsor!=NULL;corsor=corsor->link()){
sum1 = sum1 + (corsor->data().get_number_grade())*(corsor->data().get_hours());
sum2 = sum2 + corsor->data().get_hours();
}
gpa = sum1/sum2;
return gpa;
}

void contain::filein(std::istream& ins){
course c1;   //this function is to filein the course information
while(ins>>c1)
insert_course(c1);
}
void contain::name_filein(std::istream& ins){  //this function is to filein the name 
change_name(ins);
}


void meau(){
cout<<"1.Change your name/Enter the new name"<<endl;
cout<<"2.Add addition course on your list"<<endl;
cout<<"3.Remove the course from your list"<<endl;
cout<<"4.Show all your class information"<<endl;
cout<<"5.Caculate the total hours of your classes"<<endl;
cout<<"6.Check your GPA"<<endl;
cout<<"7.Creat a copy of your class information"<<endl;
cout<<"8.Back up your information"<<endl;
cout<<"9.Quit"<<endl<<endl;
}
