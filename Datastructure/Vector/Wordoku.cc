//*******************************************************************
//
// File Name:	Wordoku.cc
//
// Author:		Zhiqiang Zhang
//
// Email:		zz373609@ohio.edu
//
// Description:	To detemin whether the wordoku is works 
//
// Date: 		9/6/2013
//
//*******************************************************************
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;



class Wordoku {

public:
//******************************************************************
//
// Function: vaild
//
// Purpose:  the function to return the ture of false for wordoku
//
// Parameters:	const vector<string> &wordoku_board, const string &letters
//
// Member/Global Variables: None
//
// Pre Conditions:	read letters using in wordoku, and load wordoku in vector
//
// Post Conditions:	return if this wordoku is ture or false
//
// Calls:main.cc
//
//******************************************************************
bool valid(const vector<string> &wordoku_board, const string &letters){
//the vriables will be used in rest of code
int value = 0;
int check = 0;
int clum = 0;
int row = 0;
int first = 0;
int second = 3;
int third = 6;
int checks1 = 0;
int checks2 = 0;
int checks3 = 0;

//the total value of leeters
	for(int i = 0; i<9; i++)
		value = value + int(letters[i]);



//clum check
	while(clum<9){
		for(int j = 0;j<9;j++)
			check = check + int(wordoku_board[clum].at(j));
				if((check - value)!=0)
					return false;
						check = 0;
						clum++;
}


//row check
	while(row<9){
		for(int k= 0; k < 9;k++)
			check = check + int(wordoku_board[k].at(row));
				if((check - value)!=0)
					return false;
						check = 0;
						row++;
}

//3X3 squ to check
//the row 0 to 2
while(first<3){
for(int l = 0;l<3;l++)
checks1 = checks1 + int(wordoku_board[first].at(l));

for(int l1 = 3;l1<6;l1++)
checks2 = checks2 + int(wordoku_board[first].at(l1));

for(int l2 = 6;l2<9;l2++)
checks3 = checks3 + int(wordoku_board[first].at(l2));
first++;
}
	if(((checks1-value)!=0)||((checks2-value)!=0)||((checks3-value)!=0))
		return false;

//the row 3 to 5		
checks1 = 0;
checks2 = 0;
checks3 = 0;

while(second<6){
for(int l = 0;l<3;l++)
checks1 = checks1 + int(wordoku_board[second].at(l));

for(int l1 = 3;l1<6;l1++)
checks2 = checks2 + int(wordoku_board[second].at(l1));

for(int l2 = 6;l2<9;l2++)
checks3 = checks3 + int(wordoku_board[second].at(l2));
second++;
}

	if(((checks1-value)!=0)||((checks2-value)!=0)||((checks3-value)!=0))
		return false;
		
//the row 6 to 8
checks1 = 0;
checks2 = 0;
checks3 = 0;

while(third<9){
for(int l = 0;l<3;l++)
checks1 = checks1 + int(wordoku_board[third].at(l));

for(int l1 = 3;l1<6;l1++)
checks2 = checks2 + int(wordoku_board[third].at(l1));

for(int l2 = 6;l2<9;l2++)
checks3 = checks3 + int(wordoku_board[third].at(l2));
third++;
}

	if(((checks1-value)!=0)||((checks2-value)!=0)||((checks3-value)!=0))
		return false;
return true;
}

};
