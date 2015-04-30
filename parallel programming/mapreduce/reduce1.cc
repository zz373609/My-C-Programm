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


//To calculate 
double top(double r_u,double r){
return 25 - pow ((r-r_u),2);
}



int main(int argc, char *argv[]){
string l;
double sum = 0;
int count;
int last_user = 0;
int user;
int movie;
double u_rating;
string line;
double rating;
char c;
map <int,double> user_rat;

ifstream fin;
fin.open(argv[1]);
while(!fin.eof()){
	getline(fin,l);
	istringstream fi(l);
	char r;
		int u_movie;
		double u_rating;
		fi>>u_movie;
		fi>>r;
		fi>>r;
		fi>>u_rating;
		user_rat[u_movie] = u_rating;
}
fin.close();

while(!cin.eof()){
	getline(cin,line);
	if(!cin.fail()){
	istringstream in(line);
	in >> user;
	in >> movie;
	in >> rating;
	u_rating = user_rat[movie];
		if(last_user==0){
			last_user = user;
			sum = sum + top(u_rating,rating);
			count = 1;
		}
		else{
			if(last_user!=user){
			cout<<last_user<<"\t"<<(sum/count)<<endl;
			last_user = user;
			sum = 0;
			sum = sum + top(u_rating,rating);
			count = 1;
			}
			else{
				sum = sum + top(u_rating,rating);
				count++;
				}
			}
		}
	}

		if(last_user>0)
				cout<<last_user<<"\t"<<(sum/count)<<endl;

return 0;

}
