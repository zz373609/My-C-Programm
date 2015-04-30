//********************************************************
//File:read_data.cc
//Author: David W. Juedes
//
//Purpose: This example program reads the data for homework #2
// It reads m q
// and then, a n x n matrix of integers 
// This code is not elegant, but it is sufficient for the
// purpose of this class.
//***********************************************************
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <omp.h>
using namespace std;


//***************************************************************
// Function read_q(istream &in) 
// Parameters: istream in --- 
// Return value: q
// Purpose: Read the value q (the modulus for the assigment)
//****************************************************************
int read_q(istream &in) {
  int q;
  in >> q;
  return q;
}
//***************************************************************
// Function read_m(istream &in) 
// Parameters: istream in --- 
// Return value: m
// Purpose: Read the value m (the number of values in the product)
//****************************************************************
int read_m(istream &in) {
  int m;
  in >> m;
  return m;
}
//***************************************************************
// Function read_M(istream &in) 
// Parameters: istream in --- 
// Return value: vector<vector<int> > M
// Purpose: Read the value M, the matrix, which exists to the end of the 
// input.
// Assumption: each row of the matrix is stored on a line by itself.
//****************************************************************
vector<vector<int> > read_M(istream &in) {
  string line;
  vector<vector<int> > M;
  while (!in.eof()) {
    getline(in,line);
    if (!in.fail()) {
      istringstream in1(line);
      vector<int> row;
      while (!in1.eof()) {
	int x;
	in1 >> x;
	if (!in1.fail()) {
	  row.push_back(x);
	}
      }
      M.push_back(row);
    }
  }


  return M;
}
//********************* 
//check the each line
//*********************
 int check(vector<vector<int> >&v,int &row, int &col, int &q, int &m){
 int max;
 vector<int> p(4);
 max = 0;
 for(int i = 0;i<p.size();i++)
 p[i]=1;
 
//right
if((row+m)<=v[row].size()){
for(int i = row;i<row+m;i++)
	p[0]*=v[col][i];
	p[0]=p[0]%q;
}

//down
if((col+m)<=v.size()){
for(int j = col;j<col+m;j++)
	p[1]*=v[j][row];
	p[1]=p[1]%q;
}

//right_up
if((row+m)<=v[row].size()&&(col-m)>=0){
for(int j = col,i = row;j>col-m&&i<row+m;j--,i++)
	p[2]*=v[j][i];
	p[2]=p[2]%q;
}

//right_down
if((row+m)<=v[row].size()&&(col+m)<=v.size()){
for(int j = col,i = row;j<col+m&&i<row+m;j++,i++)
	p[3]*=v[j][i];
	p[3]=p[3]%q;
}

for(int i = 0; i < p.size(); i++){
	if(p[i]>max)
	max = p[i];
}

return max;
 
}
 
void max_Q(vector<vector<int> > &v,int&q, int&m,int&max){
int row, col;
int c;
int max2 = 0;
col = v.size();
row = v[0].size();
int get_num = omp_get_thread_num();
int total_thread = omp_get_num_threads();
int limit;
if((get_num+1)==total_thread){
limit = col;
}
else{
limit = (col/total_thread)*(get_num+1);
}
for(int j = (col/total_thread)*(get_num); j<limit;j++)
	for(int i = 0;i<row;i++){
	#pragma omp critical
			c = check(v,i,j,q,m);
			if(c>max) 
			max = c;
	}
	//#pragma omp critical
		//max=max2;
		
}
 

 
int main() {
  int q;
  int m;
  int answer;
  int max = 0;
  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");

  M = read_M(cin);
  cout << M.size() << endl;
  #pragma omp parallel
  max_Q(M,q,m,max);
  cout<<max<<endl;
 	return 0;
}
