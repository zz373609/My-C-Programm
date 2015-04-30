/***********************************************************************8
	This class stores the three essential features of a completed 
	college course: the course number, the grade received, and the 
	credit hours for the course. The get_number_grade will return the 
	numeric equivalent of a letter grade as used in the standard 4 
	point system.
		John Dolan	School of EECS		Summer 2013
************************************************************************/

#include<iostream>
#include<string>
#ifndef COURSE_H
#define COURSE_H

class course{
    public:
	course();
	// Input and output functions
	void input(std::istream& ins);
	void output(std::ostream& outs)const;
	// accessor functions
	std::string get_course_number()const{
	    return course_number;
	}
	std::string get_grade()const{
	    return grade;
	}
	double get_hours()const{
	    return hours;
    	}
	double get_number_grade()const;
	// mutator function
	void set_course(std::string num, std::string grad, double hrs);

	//COMPARISON OPERATORS - ORDERS LISTS BY THEIR COURSE NUMBERS
	bool operator < (const course& c)const{return course_number < c.course_number;}
        bool operator <= (const course& c)const{return course_number <= c.course_number;}
        bool operator > (const course& c)const{return course_number > c.course_number;}
        bool operator >= (const course& c)const{return course_number >= c.course_number;}
        bool operator == (const course& c)const{return course_number == c.course_number;}
        bool operator != (const course& c)const{return course_number != c.course_number;}

    private:
	void upper_course();
	std::string course_number;
	std::string grade;
	double hours;
};

std::istream& operator >>(std::istream& ins, course& c);
std::ostream& operator <<(std::ostream& outs, const course& c);

#endif
