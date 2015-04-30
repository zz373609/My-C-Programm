#include<iostream>
#include<stdlib.h>
#include<vector>
#include<fstream>
using namespace std;

int main(){
ofstream fout;
vector<vector<int> > v(1000,vector<int>(1000));
int a,b;
a = 500;
b = 1000;

fout.open("ex.dat");

for(int i = 0;i<v.size();i++)
	for(int j = 0;j<v[0].size();j++)
	v[i][j]=(2*(rand()%10)-1);
	
fout<<a<<" "<<b<<endl;

for(int i = 0;i<v.size();i++){
	for(int j = 0;j<v[0].size();j++){
		fout<<v[i][j]<<" ";
			}
		fout<<endl;	
	}
	
fout.close();
cout<<"done"<<endl;
return 0;

}
