//***************************************************
//Name: 	Zhiqiang Zhang
//Date:		8/5/2013
//Class:    cs2401sum
//Description: animal class
//***************************************************
#include<iostream>
#include<fstream>
#include<list>
#include<stack>
#include"animal.h"
using namespace std;


int main(){
list<Animal *> a1;         //animal list
list<Animal *>::iterator it;      //iterator
char choose;
int choice;
ifstream fin;
ofstream fout;
int check_file;
int Main_Enter;



fin.open("Animal.dat");


while(fin>>check_file)        //load file, check_file is the variable to divide the data
{
	if(check_file ==1)					
	{
		Animal* temp = new bear;
		temp->input(fin);
		a1.push_back(temp);
	}
	
	else if(check_file ==2)
	{
		Animal* temp = new panda;
		temp->input(fin);
		a1.push_back(temp);
	}

	else if(check_file ==3)
	{
		Animal* temp = new moneky;
		temp->input(fin);
		a1.push_back(temp);
	}

	else if(check_file ==4)
	{
		Animal* temp = new tiger;
		temp->input(fin);
		a1.push_back(temp);
	}

	else if(check_file ==5)
	{
		Animal* temp = new eleph;
		temp->input(fin);
		a1.push_back(temp);
		}

}

	fout.open("Animal.dat");

do{

main_meau();                             //the main menu is called here
cout<<"Please enter the Main Choice > ";
cin>>Main_Enter;

if(Main_Enter == 1)
{
do{

	meau();
	cout<<"Please Enter the Animal you want > ";
	cin>>choice;

	if(choice == 1)
	{
		Animal* temp = new bear;
		temp->input(cin);
		a1.push_back(temp);
	}

	else if(choice == 2)
	{
		Animal* temp = new panda;
		temp->input(cin);
		a1.push_back(temp);
	}

	else if(choice == 3)
	{
		Animal* temp = new moneky;
		temp->input(cin);
		a1.push_back(temp);
	}

	else if(choice == 4)
	{
		Animal* temp = new tiger;
		temp->input(cin);
		a1.push_back(temp);
	}

	else if(choice == 5)
	{
		Animal* temp = new eleph;
		temp->input(cin);
		a1.push_back(temp);
	}

	else
	cout<<"Wrong input";

	cout<<"Do you want to other Animal > (Y/N)";
	cin>>choose;

}while(choose=='Y'||choose=='y');

}

	else if(Main_Enter==2)
	{
	for(it = a1.begin();it != a1.end(); it++){
	(*it)->output(cout);
	 }
	}

	else if(Main_Enter == 3)
	{
      for(it = a1.begin();it != a1.end(); it++){
      (*it)->output(fout);
      }
    }


}while(Main_Enter != 4);

fin.close();
fout.close();


return 0;
}