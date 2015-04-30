//***************************
//Name: Zhiqiang Zhang
//Date: 7/21/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: main.cc
//***************************
#include<iostream>
#include<fstream>
#include "node.h"
#include "course.h"
#include "container.h"
using namespace std;

int main(){

int check;
char choice;
course s1;
contain c1;
std::string course_name;
ifstream fin,fin1;
ofstream fout,fout1;

fin.open("back_up.dat");  //to open a backup file
c1.filein(fin);
fin.close();

fin1.open("name.dat");
c1.name_filein(fin1);
fin1.close();

meau();
do{
cout<<endl<<"Please Enter the choice from meau > ";
cin>>check;
if(check==1){  //to change name
c1.change_name(cin);
}
else if(check==2){
do{
cout<<"Please Enter the information of new class > "<<endl;
cin>>s1;  //to add new course
c1.insert_course(s1);
cout<<"Want to enter one more class?   (y/n)> ";
cin>>choice;
cout<<endl;
}while(choice=='y'||choice=='Y');
}
else if(check==3){
char junk;  //to drop a course
cout<<"Please Enter the class name you want to drop > ";
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,course_name);
c1.remove(course_name);
cout<<endl;
}
else if(check==4){
cout<<endl<<endl;  //output the whole list including the student's name to the screen
c1.output_name(cout);
cout<<endl;
c1.show_list(cout);
cout<<endl<<endl;
}
else if(check==5)
{  //show the total credit hours
double total_hours;
total_hours = c1.total_hours();
cout<<"Your total hours of classes are > "<<total_hours<<endl<<endl;
}
else if(check==6){
double gpa; //show the gpa
gpa = c1.GPA();
cout<<"Your current GPA is > "<<gpa<<endl<<endl;
}
else if(check==7){
contain c2(c1);
contain c3;  //testing the copy constructor and the assignment operator
c3 = c1;
int c;
cout<<"Which copy you want either copy constructor(1) or assigment operator(2) > ";
cin>>c;
if(c=1){
cout<<endl<<endl;
c2.show_list(cout);  
char junk;
cout<<"Please Enter the class name you want to drop from the copy > ";
if(cin.peek()=='\n')
cin.get(junk);  //drop the copy from the list
getline(cin,course_name);
c2.remove(course_name);
cout<<endl;
c2.show_list(cout);
cout<<endl;   //to show the copy list after deleting a course
cout<<endl<<endl;
}
else{
cout<<endl<<endl;
c3.show_list(cout);
char junk;
cout<<"Please Enter the class name you want to drop > ";
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,course_name);
c3.remove(course_name);
cout<<endl;
c3.show_list(cout);
cout<<endl;
cout<<endl<<endl;
} 
}
else if(check == 8){
fout.open("back_up.dat");  //save a backup file
c1.show_list(fout);
fout.close();
fout1.open("name.dat");
c1.output_name(fout1);
fout1.close();
}
meau();
}while(check!=9);
	
return 0;
}

