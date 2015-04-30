/*
name: zhiqiang zhang
class: cs4100
date: 3/17/2015
*/
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cctype>

#include "pasor.h"

const char* pasor::NUM = "0123456789";
	//constructor
	pasor::pasor(){
		pasor_str = "";
		size = 0;
		pso_ = 0;
		token = "";
		x = 0;
		y = 0;
		z = 0;

	}
	//read the input
	void pasor::set_everything(string input){
		pasor_str = input;
		size = input.length();
		pso_ = 0;
		//go_to_next();
	}
	//get the string of input
	string pasor::get_pasor(){
		return pasor_str;

	}
	//get the size of input 
	int pasor::get_pasor_size(){
		return size;
	}
	//go to the next char of input
	
	//<expr> = <term>|<term>"+"<expr>|<variable> "=" <exper>
	int pasor::expr(){
		int result;
		if((pasor_str[pso_]=='x'||pasor_str[pso_]=='y'||pasor_str[pso_]=='z')&&(pasor_str[pso_+1]=='=')){
					int& tem = variable();
						pso_++;
						tem = expr();
						result = tem;
				
		}else{
				result = term();
				if(pasor_str[pso_] == '+'){
					pso_++;
					result = result + expr();
				}
			}
			return result;
	}
	//<term> = <factor> | <term> "*" <factor>
	int pasor::term(){
		int result;
		result = factor();

		if(pasor_str[pso_] == '*'){
			pso_++;
			result = result*term();
		}
		return result;
	}
	//<factor> = <constant> | <variable> | "(" <expr> ")"
	int pasor::factor(){
		string get_string;
		int result;
		if (pasor_str[pso_]=='('){
			pso_++;
			result = expr();
			if(pasor_str[pso_]==')'){
				pso_++;
			}
		}
		else if(pasor_str[pso_]=='x'||pasor_str[pso_]=='y'||pasor_str[pso_]=='z'){
					int& tem = variable();
						result = tem;
		}
		else{
			get_string = constant();
			istringstream buffer(get_string);
			buffer>>result;
		}
		return result;
	}

	int& pasor::variable(){
		if(pasor_str[pso_]=='x')
		  {
		    pso_++;
		    return x;
		  }else if(pasor_str[pso_]=='y')
		  {
		    pso_++;
		    return y;
		  }
		  else if(pasor_str[pso_]=='z')
		  {
		    pso_++;
		    return z;
		  }
		}


	//<constant> = <digit> | <digit><constant>
	string pasor::constant(){
		string get_num;
		get_num = digit();
		while((pasor_str[pso_]=='0'||pasor_str[pso_]=='1'||pasor_str[pso_]=='2' ||pasor_str[pso_]=='3'||pasor_str[pso_]=='4'||pasor_str[pso_]=='5' ||pasor_str[pso_]=='6'||pasor_str[pso_]=='7'||pasor_str[pso_]=='8' ||pasor_str[pso_]=='9')&&(pso_<size))
	  	{
	  	 get_num=get_num+digit();
	  	}
		return get_num;
	}


	//<digit> = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
	string pasor::digit(){
			pso_++;
  			stringstream ss;
  			string s;
  			ss << pasor_str[pso_-1];
  			ss >> s;
  			return s;

	}

















