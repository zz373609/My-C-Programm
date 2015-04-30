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
 
int diagona1(vector<vector<int> >&a, int m, int q,int column,int row)
{

	int large=0;
	vector<int> temp(4);
	if(row+m<=a.size())
	{
			temp[0]=1;
			for(int j=0;j<m;j++)
			{
				temp[0]*=a[row+j][column];
			}
			temp[0]=temp[0]%q;
	} 
	

	if(column+m<=a.size())
	{
			temp[1]=1;
			for(int j=0;j<m;j++)
			{
				temp[1]*=a[row][column+j];
			}
			temp[1]=temp[1]%q;
	}

	

		if(m+column<=a.size()&&m+row<=a.size())
		{
			temp[2]=1;
			for(int z=0;z<m;z++)
			{
				temp[2]*=a[row+z][column+z];
			}
			temp[2]=temp[2]%q;
		}
	
		
		if(row+m<=a.size()&&column-m>=0)
		{
			temp[3]=1;
	
			for(int z=0;z<m;z++)
			{
				temp[3]*=a[column-z][row+z];
			}
			temp[3]=temp[3]%q;
		}
	for(int i = 0; i < temp.size(); i++)
	{
	if(temp[i]>large)
	large = temp[i];
	}
	return large;
}


void find(vector<vector<int> >&a,int m,int q,int&big)
{
  int temp=0;
  int size=a.size();  
  
  int get_num = omp_get_thread_num();
  int get_threads = omp_get_num_threads();
  int limit;
  if((get_num+1)==get_threads)
  {
  	limit= size;
  }
  else 
  {
  	limit=(size/get_threads)*(get_num+1);
  } 
 
  for(int i=(size/get_threads)*(get_num); i<limit;i++)
  {
  	for(int j=(size/get_threads)*(get_num);j<limit;j++)
  	{
  		 #pragma omp critical
  		 if(diagona1(a, m, q,j,i)>=big)
  		 {
  			big=diagona1(a, m, q,j,i);
  		 }
  	}
  }
}



int main()
{
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
  #pragma omp parallel
  find(M,m,q,large);
  cout<<"Largest is "<<large<<endl;
  return 0;
}
  
