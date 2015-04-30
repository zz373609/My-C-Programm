//***************************
//Name: Zhiqiang Zhang
//Date: 7/27/2013
//Class:CS2401
//E-mail:zz373609@ohio.edu
//Description: colorful program
//***************************
#include<iostream>
#include<fstream>
#include"dlist.h"
using namespace std;


int main(){
dlist<Swatch> color1,color3;
dlist<Swatch>::iterator it;
ifstream fin;
ofstream fout;
Swatch temp;
int mid;
int move;

fin.open("swatches.txt");
while(fin>>temp){
if( temp.get_red() > temp.get_blue() && temp.get_red() > temp.get_green())
color1.dlist_insert_front(temp);
else if( temp.get_green() > temp.get_red() && temp.get_green() > temp.get_blue())
color1.dlist_insert_back(temp);
else if(temp.get_blue() > temp.get_red() && temp.get_blue() > temp.get_green()){
mid = color1.get_used()/2;
it = color1.start();
move = 0;
while(move!= mid){
move++;
++it;
}
color1.dlist_insert_after(it, temp);
}
}

fout.open("output.txt");
//original list
for(it = color1.start();it!=color1.end(); it++){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;

//backwards original list
for(it = color1.r_start();it!=color1.r_end(); it--){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;

//copy constructor list
dlist<Swatch> color2(color1);
for(it = color2.start();it!=color2.end(); it++){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;


//assigment operator list
color3 = color1;
for(it = color3.start();it!=color3.end(); it++){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;


//remove front,back, and centor list
color2.dlist_remove_front();
color2.dlist_remove_back();
mid = color1.get_used()/2;
it = color2.start();
move = 0;
while(move!= mid){
move++;
++it;
}
color2.dlist_remove_it(it);
for(it = color2.start();it!=color2.end(); it++){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;

//dsetroy original list
dlist<Swatch>::iterator ite = color1.r_start();
dlist<Swatch>::iterator itb = color1.start();
while(ite != itb){
	ite = color1.r_start();
	itb = color1.start();
	fout<<*itb<<endl;
	++itb;
	color1.dlist_remove_front();
	fout<<*ite<<endl;
	--ite;
	color1.dlist_remove_back();
}
fout<<endl<<endl;

//backwards copy list after removing
for(it = color2.r_start();it!=color2.r_end(); it--){
	fout<<*(it)<<endl;
	}
fout<<endl<<endl<<endl;
fout.close();
return 0;
}