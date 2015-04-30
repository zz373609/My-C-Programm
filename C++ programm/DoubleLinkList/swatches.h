/**************************************************************************
	The header file for a class called Swatches, which stores
	the color and dimensions of a color swatch. The color is stored
	as a single hexadecimal number which is actually a composite of 
	three hex numbers representing the intensity of Red, Green and 
	Blue respecitively. The dimensions are intergers for width and 
	height which can be interpreted into whatever unit is relevant 
	for the application.
	A set of accessor and modification functions are provided for 
	for the private variables, and the color is available as either 
	a number a string.
	    John Dolan				January 2004
************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#ifndef SWATCH_H
#define SWATCH_H

class Swatch{
    public:
	static const unsigned long ONE_COLOR = 256;
	static const unsigned long TWO_COLOR = 256*256;
	// CONSTRUCTORS
	Swatch();
	Swatch(unsigned long n_color, int n_width, int n_height);
	// ACCESSOR FUNCTIONS
	unsigned long get_color();
	std::string color_string();
	unsigned long get_red();
	unsigned long get_green();
	unsigned long get_blue();
	int get_width();
	int get_length();
	// MODIFICATION FUNCTIONS
	void set_color(unsigned long n_color);
	void set_color(std::string n_color);
	void set_width(int n_width);
	void set_length(int n_length);
	// FRIENDS
	friend std::ostream& operator <<(std::ostream& outs, const Swatch& sw);
	friend std::istream& operator >>(std::istream& ins, Swatch& sw);
    private:
	unsigned long color;
	unsigned long red, green, blue;
	int width;
	int length;
};
#endif


