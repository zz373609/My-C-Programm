/*******************************************************************
	This class, Date, is designed for the storage of dates.
	It expects to receive all dates in the m/d/y format, and it 
	outputs them in the same format. There are no restrictions on
	the year, but if the momth entered falls outside the normal 
	bounds a bad_month exception is thrown. The input operator also
	checks the day entered against a list of permissable days in each
	month, and throws a bad_day exception if the day is outside 
	acceptable bounds. There is no mechanism for leap years so all
	Februaries are allowed 29 days. A full set of comparison operators
	is included with the class.
		John Dolan			September 2005
			OHIO UNIVERSITY SCHOOL OF EECS
	Added to the date class: The ability to store a string saying
	what is to be connected with the date. The string can be by 
	passing a zero to the constructor.
		John Dolan			Spring 2013
			OHIO UNIVERSITY SCHOOL OF EECS
******************************************************************/


#include <iostream>
#include <ctype.h>

#ifndef DATE
#define DATE
// an exception if the date entered is invalid for the month
class bad_day{
    public:
	bad_day(){monthnum=daynum=0;}
	bad_day(int m, int d)
		{monthnum = m, daynum=d;}
	void msg(){std::cerr<<monthnum<<" has no day "<<daynum<<std::endl;}
    private:
	int monthnum, daynum;
};

// an exception for an invalid month number
class bad_month{
    public:
	bad_month(){monthnum = 0;}
	bad_month(int m){monthnum = m;}
	void msg(){std::cerr<<monthnum<<" is an invalid month number.\n";}
    private:
	int monthnum;
};

// a simple class for holding dates
class Date{
    public:
	Date(bool nameset=1);
	Date(int d,int m,int y);

    // outputs the date
	friend std::ostream& operator <<(std::ostream& outs, Date d);

    //inputs the date
	friend std::istream& operator >>(std::istream& ins, Date& d);

/**************************************************
        COMPARSION OPERATORS
**************************************************/
	friend bool operator > (const Date& d1, const Date& d2);

	friend bool operator < (const Date& d1, const Date& d2);

	friend bool operator == (const Date& d1, const Date& d2);

	friend bool operator != (const Date& d1, const Date& d2);
	
	friend bool operator <= (const Date& d1, const Date& d2);

	friend bool operator >= (const Date& d1, const Date& d2);
	
	std::string get_name()const;
	
	void toggle_name_on();
	
	void set_name(std::string nname);

private:
   int day;
   int month;
   int year;
   int daysallowed[13];
   std::string name;
   bool nameon;
};

#endif


