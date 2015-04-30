//************************************
//Zhiqiang Zhang
//zz373609@ohio.edu
//4/27/2014
//This is the second map of the assignment
//************************************
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;


int main(int argc, char *argv[]){
string data1;
string data2;
ifstream fin1;
ifstream fin2;
map<int,int> user_rating;
map<int,int> reduce1;
fin1.open(argv[1]);
fin2.open(argv[2]);
while(!fin1.eof()){
	getline(fin1,data1);
	int um;
	istringstream fi(data1);
	fi>>um;
	reduce1[um] = 1;
}
while(!fin2.eof()){
	getline(fin2,data2);
	int m;
	istringstream fi(data2);
	fi>>m;
	user_rating[m]=1;
}
fin1.close();
fin2.close();

string line;
while(!cin.eof()){
	getline(cin,line);
		if(!cin.fail()){
			int user;
			double rating;
			int movie;
			char c;
			istringstream in(line);
			in >> user;
			in >> c;
			in >> c;
			in >> movie;
			in >> c;
			in >> c;
			in >> rating;
			if(reduce1[user]&&(user_rating[movie]!=1))
			cout<<movie<<"\t"<<user<<"\t"<<rating<<endl;
		}
	}

return 0;
}