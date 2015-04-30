/*
name: zhiqiang zhang
class: cs4100
date: 3/17/2015
*/
#include <iostream>
#include "pasor.h"

int main(){
	pasor pa;
	string input;
	cout<<"Enter the expression you want > ";
	getline(cin,input);
	while(input!="exit"){
		pa.set_everything(input);
		cout<<pa.expr()<<endl;
		cout<<pa.x<<endl<<pa.y<<endl<<pa.z<<endl;
		cout<<"Enter the expression you want > ";
		getline(cin,input);
	}
return 0 ;
}
