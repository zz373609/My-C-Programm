//***************************************************
//Name: 	Zhiqiang Zhang
//Date:		8/9/2013
//Class:    cs2401sum
//Description: game othello :pice class
//***************************************************
#ifndef PICE_H
#define PICE_H
#include<iostream>
namespace main_savitch_14
{


class pice{
public:
//constructer for borad
pice(){
	for(int i = 1;i<9;i++)
		for(int j = 1;j<9;j++){
			p[i][j] = -1;
		}
			p[4][4]=1;
			p[4][5]=2;
			p[5][4]=2;
			p[5][5]=1;
			int i = 0;
	for(int j =0;j<10;j++)
			p[i][j] = 0;
			int j =0;
	for(int i = 0;i<10;i++)
			p[i][j]	=0;
			 j =9;
	for(int i = 0;i<10;i++)
			p[i][j]=0;
			 i =9;
	for(int j =0;j<10;j++)
			p[i][j]=0;
}
//return the index
int get_w(){
	return w;
}
//return the index
int get_h(){
	return h;
}
//return the vule of arry
int get_pice(int i,int j){
	return p[i][j];
}
//flip the pice
void flip(int i,int j,int k){
	p[i][j] = k;
}


private:
static const size_t h = 10;
static const size_t w = 10;
int p[w][h];
};
}

#endif