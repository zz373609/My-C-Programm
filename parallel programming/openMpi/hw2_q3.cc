	

/*********************************************************************
Brian Fong 
CS4000 - Homework 2
Problem 3

*Use call by reference
*Prevent Integer Overflow
*#pragma omp parallel for later

*takes about 00:00.02 
             00:00.01

**For compiling: g++ <filename.cc> -fopenmp
*********************************************************************/

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

//If we call by reference on these values, it will be quicker
//To start traversing the data, we must check the values
 int check(vector<vector<int> >&v,int &row, int &col, int &q, int &m){
 int max;
 
//Since there are Eight Directions dir(8), 0 to 7
//Holds sums of the directionals
 vector<int> dir(8);
 max = 0;

 for(int i = 0;i<dir.size();i++)
 dir[i]=1;

//Dir[2]: Up
if(col-m>=0){
for(int j = col;j>col-m;j--)
  dir[0]=dir[0]*v[j][row];
  dir[0]=dir[0]%q;
}

//Dir[3]: Down
if((col+m)<=v.size()){
for(int j = col;j<col+m;j++)
  dir[1]=dir[1]*v[j][row];
  dir[1]=dir[1]%q;
}

//Dir[0]: Right
if((row+m)<=v[row].size()){
for(int i = row;i<row+m;i++)
  dir[2]=dir[2]*v[col][i];
  dir[2]=dir[2]%q;
}

//Dir[1]: Left
if((row-m)>=0){
for(int i = row;i>row-m;i--)
  dir[3]=dir[3]*v[col][i];
  dir[3]=dir[3]%q;
}

//Dir[4]: Up-Right
if((row+m)<=v[row].size()&&(col-m)>=0){
for(int j = col,i = row;j>col-m&&i<row+m;j--,i++)
	dir[4]=dir[4]*v[j][i];
	dir[4]=dir[4]%q;
}

//Dir[5]: Down-Left 
if((row-m)>=0&&(col+m)<=v.size()){
for(int j = col,i = row;i>row-m&&j<col+m;j++,i--)
  dir[5]=dir[5]*v[j][i];
  dir[5]=dir[5]%q;
}

//Dir[6]: Up-Left
if((row-m)>=0&&(col-m)>=0){
for(int j = col,i = row;j>col-m&&i>row-m;j--,i--)
  dir[6]=dir[6]*v[j][i];
  dir[6]=dir[6]%q;
}

//Dir[7]: Down-Right
if((row+m)<=v[row].size()&&(col+m)<=v.size()){
for(int j = col,i = row;j<col+m&&i<row+m;j++,i++)
	dir[7]=dir[7]*v[j][i];
	dir[7]=dir[7]%q;
}
 
//Checks all of dir[n]
//  makes max = the greatest in dir[n]
for(int i = 0; i < dir.size(); i++){
	if(dir[i]>max)
	max = dir[i];
}

return max;
}

//Finds max of (q%m), prevents integer overflow
//also, using call by reference makes it quicker
void product_Max(vector<vector<int> > &v,int &q, int &m, int &max){
//int max = 0;
  //for #pragma, we have to get our thread numbers
  int sum = 0;
  int limit;
  int thread_num = omp_get_thread_num();
  int thread_total = omp_get_num_threads();

int row;
int col;
int p;
   row = v[0].size();
   col = v.size();

if((thread_num+1)==thread_total){
  limit = col;} else{
  limit=(col/thread_total)*(thread_num+1);
}

for(int j = (col/thread_total)*(thread_num); j<limit; j++)
	for(int i = 0;i<row;i++){
			p = check(v,i,j,q,m);
			if(p>sum)
			sum = p;		
	}

//make it so only one core can run this at a time
#pragma omp critical
	if(sum>max)
    max=sum;
}
 
 int main() {
  int max;
  int q;
  int m;
  int ans;

  vector<vector<int> > M;
  
  m = read_m(cin);
  q = read_q(cin);
  string line;
  
  getline(cin,line);
  assert(line == "");

  M = read_M(cin);
  cout << M.size() << endl;
  
//Multithread
  #pragma omp parallel
  product_Max(M,q,m,max);
  //ans = product_Max(M,q,m);
 	cout<<ans;
  cout<<endl;
 	return 0;
}
