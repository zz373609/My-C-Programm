//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401
//
//  Discripation: The colloction of DVD
// 
//  Date    :  2013/7/8
#include<iostream>
#include<fstream>
#include<cstring>
#include"DVD.h"
#include"All.h"
using namespace std;

int main(){
All a;
int check;
ifstream fin;
ofstream fout;
string filename;

cout<<"Enter the exit file name, otherwise enter the new flie name > ";
char junk;
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,filename);
fin.open(filename.c_str());
if(fin.fail())
{
fout.open(filename.c_str());
fout.close();
}
a1.filein(fin);
fin.close();
meau();
do{
cout<<endl<<"Please Enter the choice  from meau > ";
cin>>check;
if(check==1)
a.insert(cin);
else if(check==2)
a.remove();
else if(check==3)
a.search_by_title();
else if(check==4)
a.sort_by_title();
else if(check==5)
a.sort_by_year();
else if(check==6)
a.display(cout);
else if(check==7)
a.display_by_rating(cout);
else if(check==8){
fout.open(filename.c_str());
a.display(fout);
fout.close();
}
else if(check==9)
cout<<"Thank using this nice program";
meau();
}while(check!=9);


return 0;
};
