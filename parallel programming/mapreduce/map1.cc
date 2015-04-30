//************************************
//Zhiqiang Zhang
//zz373609@ohio.edu
//4/27/2014
//This is the first map of the assignment
//************************************
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

int main(int argc, char *argv[]){
string l;
string line;
ifstream fin;
fin.open(argv[1]);
map <int,int> user_rat;
while(!fin.eof()){       //read data
	getline(fin,l);
	int m;
	double rat;
	char r;
	istringstream fi(l);
	fi>>m;
	user_rat[m] = 1;
}
fin.close();
while(!cin.eof()){
	getline(cin,line);
		if(!cin.fail()){
			int user;
			double rating;
			int movie;
			char c;
			istringstream in(line);      //read data
			in >> user;
			in >> c;
			in >> c;
			in >> movie;
			in >> c;
			in >> c;
			in >> rating;
			if(user_rat[movie])
			cout<<user<<"\t"<<movie<<"\t"<<rating<<endl;
		}
	}
	return (0);
}

