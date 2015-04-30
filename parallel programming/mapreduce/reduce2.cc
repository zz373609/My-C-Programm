//************************************
//Zhiqiang Zhang
//zz373609@ohio.edu
//4/27/2014
//This is the first reduce of the assignment
//************************************
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <map>
using namespace std;

double top_rating(double&dui,double&rating){
return dui*rating;
}


int main(int argc, char *argv[]){
string data1;
map<int,double> du;
double top_movie;
double current_top;
int moive;
int user;
double rating;
double dui;
string line;
int count;
double sum = 0;
int last_movie = 0;
ifstream fin;
fin.open(argv[1]);
while(!fin.eof()){
	getline(fin,data1);
	istringstream fi(data1);
	int u;
	double d;
	fi>>u;
	fi>>d;
	du[u] = d;
}
fin.close();
	while(!cin.eof()){
		getline(cin,line);
		if(!cin.fail()){
			istringstream in(line);
			in>>moive;
			in>>user;
			in>>rating;
			if(last_movie==0){
				sum = sum + top_rating(du[user],rating);
				last_movie = moive;
				count = 1;
			}
			else{
				if(last_movie!=moive){
					current_top = sum/count;
					cout<<last_movie<<"\t"<<current_top<<endl;
						last_movie = moive;
						sum = 0;
						sum = sum + top_rating(du[user],rating);
						count = 1;
				}
				else{
					sum = sum + top_rating(du[user],rating);
					count++;
				}
			}
		}	
	}
				if(last_movie>0){
				cout<<last_movie<<"\t"<<current_top<<endl;
				}


return 0;
}
