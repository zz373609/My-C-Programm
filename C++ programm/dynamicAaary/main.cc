//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The information of birthday
// 
//  Date    :  2013/7/14
#include<iostream>
#include"proj2.h"
#include<fstream>
#include<cstring>
using namespace std;

int main(){
arry a1,a3;
Date d1;
ifstream fin;
ofstream fout;
std::string filename;
int check;
char choice;


cout<<"Enter the exit file name, otherwise enter the new flie name > ";
char junk;
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,filename);

fin.open((char*)filename.c_str());

if(fin.fail())
{
fout.open((char*)filename.c_str());
fout.close();
}
a1.filein(fin);
fin.close();
meau();
do{
cout<<endl<<"Please Enter the choice  from meau > ";
cin>>check;
if(check==1){
do{
cout<<"Please Enter the information of new friend > "<<endl;
cin>>d1;
a1.insert(d1);
cout<<"Want to enter one more person ?   (y/n)> ";
cin>>choice;
}while(choice=='y'&&choice=='y');

}
else if(check==2){
cout<<endl<<"There are all of information about all of people in you list>"<<endl<<endl;
a1.display(cout);
cout<<endl;
}
else if(check==3){
a1.search_by_date();
cout<<endl;
}
else if(check==4){
a1.remove();
cout<<endl;
}
else if(check==5)
{
arry a2(a1);
a3 = a1;
cout<<"The output of copy constructor > "<<endl;
a2.display(cout);
cout<<endl;
cout<<"The output of assignment operator > "<<endl;
a3.display(cout);
cout<<endl;
}
else if(check==6){
fout.open(filename.c_str());
a1.display(fout);
fout.close();
}
else if(check==7)
cout<<"Thank for finding the birthday next time"<<endl;
meau();
}while(check!=7);

return 0;

}