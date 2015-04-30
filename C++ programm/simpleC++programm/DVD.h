//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The colloction of DVD
// 
//  Date    :  2013/7/8
#ifndef DVD_H
#define DVD_H
#include <iostream>
#include <string>

class DVD{

public:
DVD();
void set_title(std::string t);
void set_year(int y);
void set_running_time(std::string r);
void set_movie_type(std::string m);
void set_rating(std::string r);
std::string get_title()const;
int get_year()const;
std::string get_running_time()const;
std::string get_movie_type()const;
std::string get_rating()const;
void input(std::istream& ins);
void output(std::ostream& ous)const;



private:
std::string title;
int year;
std::string running_time;
std::string movie_type;
std::string rating;
};

std::istream& operator >> (std::istream& ins,DVD& d1);
std::ostream& operator << (std::ostream& ous,const DVD& d1);

#endif
