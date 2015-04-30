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
 
int row(vector<vector<int> >&a, int m, int q,int column,int row)
{

	int large=0;
	int temp=0;
	if(row+m<=a.size())
	{
			temp=1;
		
			for(int j=0;j<m;j++)
			{
				temp*=a[row+j][column];
			}
			temp=temp%q;
	} 
	return temp;
	
}
int column(vector<vector<int> >&a, int m, int q,int column,int row)
{

	int large=0;
	int temp=0;
	if(column+m<=a.size())
	{
			temp=1;
	  
			for(int j=0;j<m;j++)
			{
				temp*=a[row][column+j];
			}
			temp=temp%q;
	}
	return temp;
}
	
int diagona1(vector<vector<int> >&a, int m, int q,int column,int row)
{

	int large=0;
	int temp=0;;
		if(m+column<=a.size()&&m+row<=a.size())
		{
			temp=1;
	
			for(int z=0;z<m;z++)
			{
				temp*=a[row+z][column+z];
			}
			temp=temp%q;
		}
		return temp;
}
int diagona2(vector<vector<int> >&a, int m, int q,int column,int row)
{

	int large=0;
	int temp=0;
		if(row+m<=a.size()&&column-m>=0)
		{
			temp=1;

			for(int z=0;z<m;z++)
			{
				temp*=a[column-z][row+z];
			}
			temp=temp%q;
		}
	return temp;
}

void find(vector<vector<int> >&a,int m,int q,int&big)
{


 	for(int i=0; i<a.size();i++)
 	 {
 	 
  		for(int j=0; j<a.size();j++)
   		{
   		   
   		   
   		   int r =row(a, m, q,j,i);
   		   int b =column(a, m, q,j,i);
   		   int c =diagona1(a, m, q,j,i);
   		   int d =diagona2(a, m, q,j,i);
   		 
   		   if(big<=r)
			big=r;

			if(big<=b)
			big=b;

			if(big<=c)
			big=c;

			if(big<=d)
			big=d;
		}
  		
  	}
}


int main() {
  int q;
  int m;
  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");
  M = read_M(cin);
  cout << M.size() << endl;
  int large=0;
  find(M,m,q,large);
  cout<<"Largest is "<<large<<endl;
  return 0;
}
  
