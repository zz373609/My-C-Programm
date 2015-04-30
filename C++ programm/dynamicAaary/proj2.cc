//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The information of birthday
// 
//  Date    :  2013/7/14
#include<iostream>
#include"date.h"
#include"proj2.h"
using namespace std;

//constructor
arry::arry(){
ptr = new Date [5];
used = 0;
capacity = 5;
current = 0;
}

//destructor
arry::~arry(){
delete [] ptr;
}
//copy constructor
arry::arry(const arry& n){
ptr = new Date[n.capacity];
capacity = n.capacity;
used = n.used;
current = n.current;
copy(n.ptr,n.ptr+used,ptr);
}

//assingment operator
void arry::operator = (const arry&n){
Date* temp;
if(this == &n)
{
cout<<"self assignment";
}
if(n.capacity != capacity){
temp = new Date[capacity];
delete [] ptr;
ptr = temp;
capacity = n.capacity;
}
used = n.used;
current = n.current;
copy(n.ptr,n.ptr+used,ptr);
}

std::size_t arry::get_used(){
return used;
}
std::size_t arry::get_current(){
return current;
}



//insert function
void arry::insert(Date& item){
if(ptr==NULL){
ptr[used] = item;
used++;
}
else{
resize();
insert_before(item);
}
}

//attach function for insert from after
void arry::attach(Date& item){
start();
for(int i = 0;i <used;i++){
if(item>ptr[i])
advance();
}
for(std::size_t i = used; i!= current; i--)
ptr[i] = ptr[i-1];
ptr[current] =item;
used++;
}

//insert from before
void arry::insert_before(Date& item){
start_before();
for(int i = 0;i <used;i++){
if(item>ptr[i])
advance();
}
for(std::size_t i = used; i!= current-1; i--)
ptr[i] = ptr[i-1];
ptr[current-1] =item;
used++;
}

//search function
void arry::search_by_date(){
Date d1(0);
bool done = true;
cout<<"Please Enter the your friend's date you want to find > "<<endl;
cin>>d1;
cout<<endl;
for(start();is_item();advance())
if(d1==ptr[get_current()]){
cout<<"The birth day you want to find is > "<<endl<<ptr[get_current()]<<endl;
done = false;
}
if(done)
cout<<"You may not add this person in the list"<<endl;
}

//remove by current index
void arry::remove_current(std::size_t index){
for(std::size_t i = get_current();i!=used;i++)
ptr[i] = ptr[i+1];
used--;
}

//remove current date
void arry::remove(){
Date d1(0);
bool done = true;
cout<<"Please Enter the date of your friend you hate > "<<endl;
cin>>d1;
cout<<endl;
for(start();is_item();advance())
if(d1==ptr[get_current()]){
remove_current(get_current());
done = false;
}
if(done)
cout<<"There is not friedn you hate"<<endl;
}

//display all of date
void arry::display(std::ostream& ous){
for(start();is_item();advance())
ous<<ptr[get_current()]<<endl;
}


void arry::start(){
current = 0;
}

void arry::start_before(){
current = 1;
}

bool arry::is_item(){
return (current < used);
}
void arry::advance(){
current++;
}

//resize dynamic arry
void arry::resize(){
Date* temp = new Date[capacity+5];
for(start();is_item();advance())
temp[current] = ptr[current];
capacity = capacity+5;
delete []ptr;
ptr = temp;
}

//insert in file
void arry::filein(std::istream& ins){
Date temp;
while(ins>>temp)
insert(temp);
}

void meau(){
cout<<"1.Insert the birthday of your firends"<<endl;
cout<<"2.Display the birthday of your firens"<<endl;
cout<<"3.Search the birthday of your firend"<<endl;
cout<<"4.Remove the firend's birthday you want to delet"<<endl;
cout<<"5.Testing the assignment and copy constructor"<<endl;
cout<<"6.Back_up the date "<<endl;
cout<<"7.Quit"<<endl;
}


