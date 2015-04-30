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
 int check(vector<vector<int> > v,int row, int col, int q, int m){
 int max = 1;
if((row+m)<=v[row].size()){
for(int i = row;i<row+m;i++)
	max*=v[col][i];
	max=max%q;
}
return max;
}

 int check1(vector<vector<int> > v,int row, int col, int q, int m){
  int max = 1;
if((col+m)<=v.size()){
for(int j = col;j<col+m;j++)
	max*=v[j][row];
	max=max%q;
}
return max;
}

//right_up
 int check2(vector<vector<int> > v,int row, int col, int q, int m){
  int max = 1;
if((row+m)<=v[row].size()&&(col-m)>=0){
for(int j = col,i = row;j>col-m&&i<row+m;j--,i++)
	max*=v[j][i];
	max=max%q;
}
return max;
}

//right_down
 int check3(vector<vector<int> > v,int row, int col, int q, int m){
  int max = 1;
if((row+m)<=v[row].size()&&(col+m)<=v.size()){
for(int j = col,i = row;j<col+m&&i<row+m;j++,i++)
	max*=v[j][i];
	max=max%q;
}

return max;
}

 
 
int max_Q(vector<vector<int> >&v,int q, int m,int&max){
int row, col;
int a,b,c,d;
col = v.size();
row = v[0].size();
for(int j = 0; j<col;j++)
	for(int i = 0;i<row;i++){
	
			a = check(v,i,j,q,m);
			b = check1(v,i,j,q,m);
			c = check2(v,i,j,q,m);
			d = check3(v,i,j,q,m);
			
			if(a>max)
			max = a;
			if(b>max)
			max = b;
			if(c>max)
			max = c;
			if(d>max)
			max = d;		

	}
	cout<<max<<endl;
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
 	return 0;
}
  
