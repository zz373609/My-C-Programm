//name: zhiqiang zhang
//email: zz373609@ohio.edu
//description : parallel code whit omp parallel for
//date: 2014/2/6

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

//*******************************************************************
// Function: int check()
// Parameters: vector<vector<int> > v,int row, int col, int q, int m
// Return value: max
// Purpose: find the largest modules at this position
//*******************************************************************

 int check(vector<vector<int> >&v,int&row, int&col, int&q, int&m){
 int max = 0;
 int a,b,c,d;
 a = 1;
 b = 1;
 c = 1;
 d = 1;
 
//right
if((row+m)<=v[row].size()){
for(int i = row;i<row+m;i++){
	a*=v[col][i];
	a=a%q;
	}
}

//down
if((col+m)<=v.size()){
for(int j = col;j<col+m;j++){
	b*=v[j][row];
	b=b%q;
	}
}

//right_up
if((row+m)<=v[row].size()&&(col-m)>=0){
for(int j = col,i = row;j>col-m&&i<row+m;j--,i++){ 
	c*=v[j][i];
	c=c%q;
	}
}

//right_down
if((row+m)<=v[row].size()&&(col+m)<=v.size()){
for(int j = col,i = row;j<col+m&&i<row+m;j++,i++){
	d*=v[j][i];
	d=d%q;
	}
}

		if(a>max)
			max = a;
		if(b>max)
			max = b;
		if(c>max)
			max = c;
		if(d>max)
			max = d;

 

return max;
 
}

//*******************************************************************
// Function: void max_Q
// Parameters: vector<vector<int> > v,int q, int m,int max
// Return value: none
// Purpose: find the largest modules at this matrix 
//*******************************************************************
void max_Q(vector<vector<int> >&v,int&q, int&m,int&max){
int row, col;
int max1 = 0;
int max2 = 0;
col = v.size();
row = v[0].size();
#pragma omp parallel for
for(int j = 0; j<col-m+1;j++)
	for(int i = 0;i<row;i++){
	int c;
			c = check(v,i,j,q,m);
			#pragma omp critical
			if(c>max)
			max = c;		
	}
#pragma omp parallel for
for(int i = 0;i<row-m+1;i++)
	for(int j = col-m+1; j<col;j++){
	int b;
			b = check(v,i,j,q,m);
			#pragma omp critical
			if(b>max)
			max = b;		
	}

	
}
 

 
int main() {
  int q;
  int m;
  int answer = 0;
  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");

  M = read_M(cin);
  cout << M.size() << endl;
  	max_Q(M,q,m,answer);
 	cout<<answer<<endl;
 	return 0;
}
