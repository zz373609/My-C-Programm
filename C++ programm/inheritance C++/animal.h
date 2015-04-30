//***************************************************
//Name: 	Zhiqiang Zhang
//Date:		8/5/2013
//Class:    cs2401sum
//Description: animal class
//***************************************************
#ifndef ANIMAL_H
#define ANIMAL_H
#include<iostream>
using namespace std;

class Animal{

public:
	Animal(){animal_age = 0,adress="",material="",food="";} 
	virtual void input(istream& ins) = 0;
	virtual void output(ostream& ous) = 0;    //virtual member functions




protected:
	int animal_age;     //private variables
	std::string adress;
	std::string material;
	std::string food;
};

class bear : public Animal{

void input(istream& ins){                    //input function for bear class
	if(ins == cin){
		char junk;
		if(cin.peek()=='\n');
			cin.get(junk);
			cout<<"Please enter the animal_age          		>";
			ins>>animal_age;
			cout<<"Please enter the house adress 				>";
		
		if(cin.peek()=='\n');
			cin.get(junk);
			getline(ins,adress);
			cout<<"Please enter the material of house 			>";
			getline(ins,material);
			cout<<"Please enter the offering food for animla	>";
			getline(ins,food);
			cout<<"please enter the house size of animal 		>";
			ins>>house_size;
			cout<<"please enter the house type for animal		>";
		if(cin.peek()=='\n');
			cin.get(junk);
			getline(ins,house_type);
}
else
ins>>animal_age>>adress>>material>>food>>house_size>>house_type;
}

void output(ostream &ous){       //output function
	int check = 1;
	if(ous==cout){
		cout<<endl;
		cout<<"The age of animal 			>"<<animal_age<<endl;
		cout<<"The adress of animal			>"<<adress<<endl;
		cout<<"The material of house		>"<<material<<endl;
		cout<<"The food of animal 			>"<<food<<endl;
		cout<<"The house size 				>"<<house_size<<endl;
		cout<<"Teh house type 				>"<<house_type<<endl;
}
else{
	ous<<check<<endl;
	ous<<animal_age<<endl<<adress<<endl<<material<<endl<<food<<endl<<house_size<<endl<<house_type<<endl;
 }
}
private:
	int house_size;
	std::string house_type;
};


class panda : public Animal{        //panda class
void input(istream& ins){
	if(ins == cin){
	char junk;
	if(cin.peek()=='\n');
	cin.get(junk);
	cout<<"Please enter the animal_age          		>";
	ins>>animal_age;
	cout<<"Please enter the house adress 				>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,adress);
	cout<<"Please enter the material of house 			>";
	getline(ins,material);
	cout<<"Please enter the offering food for animla	>";
	getline(ins,food);
	cout<<"Please enter the food szie for animal 		>";
	ins>>food_size;
	cout<<"please enter the outside time of animal		>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,outside_time);
}
else{
ins>>animal_age>>adress>>material>>food>>food_size>>outside_time;
}
}

void output(ostream &ous){
	int check = 2;
	if(ous==cout){
		cout<<endl;
		cout<<"The age of animal 			>"<<animal_age<<endl;
		cout<<"The adress of animal			>"<<adress<<endl;
		cout<<"The material of house		>"<<material<<endl;
		cout<<"The food of animal 			>"<<food<<endl;
		cout<<"The food size 				>"<<food_size<<endl;
		cout<<"The outside_time 			>"<<outside_time<<endl;
}
else{
ous<<check<<endl;
ous<<animal_age<<endl<<adress<<endl<<material<<endl<<food<<endl<<food_size<<endl<<outside_time<<endl;
}
}

private:
	int food_size;
	std::string outside_time;
};

class moneky : public Animal{        //monkey class
void input(istream& ins){
	if(ins == cin){
	char junk;
	if(cin.peek()=='\n');
	cin.get(junk);
	cout<<"Please enter the animal_age          		>";
	ins>>animal_age;
	cout<<"Please enter the house adress 				>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,adress);
	cout<<"Please enter the material of house 			>";
	getline(ins,material);
	cout<<"Please enter the offering food for animla	>";
	getline(ins,food);
	cout<<"please enter the training hours for animal	>";
	ins>>trainning_hours;
	cout<<"please enter the shows for animal 			>";

	if(cin.peek()=='\n');
		cin.get(junk);
		getline(ins,shows);
}
else{
ins>>animal_age>>adress>>material>>food>>trainning_hours>>shows;
}
}

void output(ostream &ous){
int check = 3;
if(ous==cout){
	cout<<endl;
	cout<<"The age of animal 			>"<<animal_age<<endl;
	cout<<"The adress of animal			>"<<adress<<endl;
	cout<<"The material of house			>"<<material<<endl;
	cout<<"The food of animal 			>"<<food<<endl;
	cout<<"The trainning hours			>"<<trainning_hours<<endl;
	cout<<"The shows 				>"<<shows<<endl;
}
else{
	ous<<check<<endl;
	ous<<animal_age<<endl<<adress<<endl<<material<<endl<<food<<endl<<trainning_hours<<endl<<shows<<endl;
}
}
private:

	int trainning_hours;
	std::string shows;
};

class tiger : public Animal{     //tiger class
void input(istream& ins){
	if(ins == cin){
	char junk;
	if(cin.peek()=='\n');
	cin.get(junk);
	cout<<"Please enter the animal_age          		>";
	ins>>animal_age;
	cout<<"Please enter the house adress 				>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,adress);
	cout<<"Please enter the material of house 			>";
	getline(ins,material);
	cout<<"Please enter the offering food for animla	>";
	getline(ins,food);
	cout<<"please enter the house_size for animla 		>";
	ins>>house_size;
	cout<<"please enter the number of tigers 			>";
	
	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,number_of_tiger);
}
else{
ins>>animal_age>>adress>>material>>food>>house_size>>number_of_tiger;
}
}


void output(ostream &ous){
int check = 4;
if(ous==cout){
	cout<<endl;
	cout<<"The age of animal 			>"<<animal_age<<endl;
	cout<<"The adress of animal			>"<<adress<<endl;
	cout<<"The material of house			>"<<material<<endl;
	cout<<"The food of animal 			>"<<food<<endl;
	cout<<"The house size 				>"<<house_size<<endl;
	cout<<"The number of tiger			>"<<number_of_tiger<<endl;
}
else{
ous<<check<<endl;
ous<<animal_age<<endl<<adress<<endl<<material<<endl<<food<<endl<<house_size<<endl<<number_of_tiger<<endl;
}
}
private:
	int house_size;
	std::string number_of_tiger;
};

class eleph : public Animal{                  //eleph class
void input(istream& ins){
if(ins == cin){
char junk;
	if(cin.peek()=='\n');
	cin.get(junk);
	cout<<"Please enter the animal_age          		>";
	ins>>animal_age;
	cout<<"Please enter the house adress 				>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,adress);
	cout<<"Please enter the material of house 			>";
	getline(ins,material);
	cout<<"Please enter the offering food for animla	>";
	getline(ins,food);
	cout<<"please enter the house size of animal		>";
	ins>>house_size;
	cout<<"please enter the water offer for animal		>";

	if(cin.peek()=='\n');
	cin.get(junk);
	getline(ins,water_offer);
}
else{
ins>>animal_age>>adress>>material>>food>>house_size>>water_offer;
}
}


void output(ostream &ous){
int check = 5;
if(ous==cout){
	cout<<endl;
	cout<<"The age of animal 			>"<<animal_age<<endl;
	cout<<"The adress of animal			>"<<adress<<endl;
	cout<<"The material of house			>"<<material<<endl;
	cout<<"The food of animal 			>"<<food<<endl;
	cout<<"The house_size 				>"<<house_size<<endl;
	cout<<"The water offer				>"<<water_offer<<endl;
}
else{
ous<<check<<endl;
ous<<animal_age<<endl<<adress<<endl<<material<<endl<<food<<endl<<house_size<<endl<<water_offer<<endl;
}
}
private:
	int house_size;
	std::string water_offer;
};


void meau(){              //animal menu
cout<<"1.Bear"<<endl;
cout<<"2.Panda"<<endl;
cout<<"3.Monkey"<<endl;
cout<<"4.Tiger"<<endl;
cout<<"5.Elephent"<<endl;

}

void main_meau(){                   //main menu
cout<<"1.Enter the Animal house"<<endl;
cout<<"2.Output the Animal house information"<<endl;
cout<<"3.Backup the information"<<endl;
cout<<"4.Quit"<<endl;
}



#endif