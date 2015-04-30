/**************************************************************************
	Implementation file for the class Swatch.
	    John Dolan			January 2004
****************************************************************************/
#include "swatches.h"
#include <iomanip>
#include <cstdlib>
#include <cstdio>
using namespace std;

	// CONSTRUCTORS
Swatch::Swatch(){
    color=0;
    red=green=blue=0;
    width=0;
    length=0;
}
Swatch::Swatch(unsigned long n_color, int n_width, int n_length){
    color=n_color;
    red = n_color/TWO_COLOR;
    blue = n_color%ONE_COLOR;
    green = (n_color/ONE_COLOR)%ONE_COLOR;
    width=n_width;
    length=n_length;
}
	// ACCESSOR FUNCTIONS
//This function returns the color as a number which is how it is 
//actually stored
unsigned long Swatch::get_color(){
     return color;
}

//This function returns a string version of the color number in standard
// RGB format
std::string Swatch::color_string(){
    char a_c_string[10]; 
    sprintf(a_c_string,"%x",color);
    std::string tmp(a_c_string);
    int leading = 6 - tmp.length();
    if(leading <= 0) return tmp;
    else{
	std::string padding;
	for(int i=0; i<leading; ++i){
	    padding += '0';
	}
	padding += tmp;
	return padding;
	}
}

//Return amount of red in swatch
unsigned long Swatch::get_red(){
	return red;
}

//Return amount of green in a swatch
unsigned long Swatch::get_green(){
	return green;
}

//Return amount of blue in a swatch
unsigned long Swatch::get_blue(){
	return blue;
}

// Return width of the swatch
int Swatch::get_width(){
    return width;
}

// Returns length of the swatch
int Swatch::get_length(){
    return length;
}

	// MODIFICATION FUNCTIONS
// Sets color to value of the argument
void Swatch::set_color(unsigned long n_color){
    color = n_color;
    red = n_color/TWO_COLOR;
    blue = n_color%ONE_COLOR;
    green = (n_color/ONE_COLOR)%ONE_COLOR;

}

// Sets color to value created when string is converted to a hex number
void Swatch::set_color(std::string n_color){
      //The strol function will work with any base from 2 to 36.
      //The 16 here denotes that we are converting from a 
      //hexadecimal representation.
    color = strtol(n_color.c_str(), (char **)NULL, 16);
    red = color/TWO_COLOR;
    blue = color%ONE_COLOR;
    green = (color/ONE_COLOR)%ONE_COLOR;

}

// Sets width to value of the argument
void Swatch::set_width(int n_width){
    width=n_width;
}

// Sets length to value of argument
void Swatch::set_length(int n_length){
    length=n_length;
}



std::ostream& operator <<(std::ostream& outs,const Swatch& sw){
    char a_c_string[10];
    sprintf(a_c_string,"%x",sw.color);
    std::string tmp(a_c_string);
    int leading = 6 - tmp.length();
    if(leading <= 0) outs<<tmp;
    else{
        std::string padding;
        for(int i=0; i<leading; ++i){
            padding += '0';
        }
        padding += tmp;
        outs<<padding;
        }
    outs<<"  "<<sw.width<<"  "<<sw.length;
    return outs;
}

std::istream& operator >>(std::istream& ins, Swatch& sw){

	ins>>hex>>sw.color>>dec>>sw.width>>sw.length;
	sw.red = sw.color/sw.TWO_COLOR;
    	sw.blue = sw.color%sw.ONE_COLOR;
    	sw.green = (sw.color/sw.ONE_COLOR)%sw.ONE_COLOR;

	return ins;
}

