/***********************************************************************
	The implementation file for the date class including the 
	implementation of overloaded insertion and extraction and
	comparison operators.
	John Dolan			September 2005
		OHIO UNIVERSITY SCHOOL OF EECS
*************************************************************************/

#include "date.h"

using namespace std;
// default constructor
Date::Date(bool nameset){
	day=month=year=0;         
    // permissable days for each month are loaded into an array
	 daysallowed[0] = 0;
         daysallowed[1] = 31;
         daysallowed[2] = 29;
         daysallowed[3] = 31;
         daysallowed[4] = 30;
         daysallowed[5] = 31;
         daysallowed[6] = 30;
         daysallowed[7] = 31;
         daysallowed[8] = 31;
         daysallowed[9] = 30;
         daysallowed[10] = 31;
         daysallowed[11] = 30;
         daysallowed[12] = 31;

	nameon=nameset;}

// constructor that takes three arguments
Date::Date(int d,int m, int y):day(d),month(m),year(y)
	{

    // permissable days for each month are loaded into an array
	 daysallowed[0] = 0;
	 daysallowed[1] = 31;
	 daysallowed[2] = 29;
	 daysallowed[3] = 31;
	 daysallowed[4] = 30;
	 daysallowed[5] = 31;
	 daysallowed[6] = 30;
	 daysallowed[7] = 31;
	 daysallowed[8] = 31;
	 daysallowed[9] = 30;
	 daysallowed[10] = 31;
	 daysallowed[11] = 30;
	 daysallowed[12] = 31;}

// output operator, overloaded as a friend function
ostream& operator <<(ostream& outs, Date d){
    outs<<d.month<<'/'<<d.day<<'/'<<d.year;
    if(d.nameon)outs<<endl<<d.name;
    return outs;
}

// input operator, overloaded as a friend
istream& operator >>(istream& ins, Date& d){
   bool flag = false;
   string junk;

   ins>>d.month;
// if an invalid month is detected throw a bad_month
       if(d.month < 1 || d.month > 12){
		getline(ins,junk); // eat the rest of the line
		throw (bad_month(d.month));
	}
// if the read has failed because of eof exit funtion
   if(ins.eof()) return ins;

   if(ins.peek() == '/') ins.ignore();
   ins>>d.day;
// if an invalid day is detected throw a bad_day
	if(d.day < 1  || d.day > d.daysallowed[d.month]){
		getline(ins,junk); // eat the rest of the line
		throw (bad_day(d.month, d.day));
	}
  if(ins.eof()) return ins;
  if(ins.peek() == '/') ins.ignore();

   ins>>d.year;
   if(d.nameon){
	if(ins==cin) cout<<"Name: ";
	if(ins.peek() == '\n') ins.ignore();
	getline(ins, d.name);
   }
   return ins;
}

// return whether or not d1 is greater than d2
bool operator > (const Date& d1, const Date& d2){
      	if(d1.year != d2.year)
	  return (d1.year > d2.year);
	else if(d1.month != d2.month)
	  return(d1.month > d2.month);
 	else
	  return (d1.day > d2.day);
}

// return whether or not d1 is less than d2
bool operator < (const Date& d1, const Date& d2){
        if(d1.year != d2.year)
          return (d1.year < d2.year);
        else if(d1.month != d2.month)
          return(d1.month < d2.month); 
        else
          return (d1.day < d2.day);
}

// return whether or not d1 equals d2
bool operator == (const Date& d1, const Date& d2){
	return(d1.year == d2.year && d1.month == d2.month &&
	       d1.day == d2.day);
}

// return whether or not d1 is not equal to d2
bool operator != (const Date& d1, const Date& d2){
        return(!(d1.year == d2.year && d1.month == d2.month &&
               d1.day == d2.day));

}

// return whether or not d1 is less than or equal to d2
bool operator <= (const Date& d1, const Date& d2){
	return (d1 == d2 || d1 < d2);
}

// return whether or not d1 is greater than or equal to d2
bool operator >= (const Date& d1, const Date& d2){
        return (d1 == d2 || d1 > d2);
}

std::string Date::get_name()const
	{return name;}

void Date::toggle_name_on()
	{nameon=!nameon;}

void Date::set_name(std::string nname)
	{if(nameon) 
	    name = nname;
	 else 
	    cout<<"Name facility is turned off.\n";
	}


