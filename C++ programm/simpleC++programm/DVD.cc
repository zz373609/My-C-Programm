//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The colloction of DVD
// 
//  Date    :  2013/7/8
#include"DVD.h"
#include<iostream>
using namespace std;

DVD::DVD(){
title = "";
year = 0;
running_time = "";
movie_type = "";
rating = "";
}

void DVD::set_title(std::string t){
	title = t;
}

void DVD::set_year(int y){
	year = y;
}

void DVD::set_running_time(std::string r){
	running_time = r;
}

void DVD::set_movie_type(std::string m){
movie_type = m;
}

void DVD::set_rating(std::string r){
rating = r;
}

std::string DVD::get_title()const{
return title;
}

int DVD::get_year()const{
return year;
}

std::string DVD::get_running_time()const{
return running_time;
}

std::string DVD::get_movie_type()const{
return movie_type;
}

std::string DVD::get_rating()const{
return rating;
}

void DVD::input(std::istream& ins){
char junk;
if(ins == cin)
{
if(cin.peek()=='\n')
cin.get(junk);
cout<<"please Enter the title of movie > ";
getline(ins,title);
cout<<"please Enter the year of movie  > ";
ins>>year;
if(cin.peek()=='\n')
cin.get(junk);
cout<<"please Enter the running time   > ";
getline(ins,running_time);
cout<<"please Enter the movie_type     > ";
getline(ins,movie_type);
cout<<"please Enter the rating         > ";
getline(ins,rating);
}

else
ins>>title>>year>>running_time>>movie_type>>rating;
}

void DVD::output(std::ostream& ous)const{
if(ous==cout)
{
ous<<"The title of movie is            > "<<title<<endl;
ous<<"The year of movie is             > "<<year<<endl;
ous<<"The running time of movie is     > "<<running_time<<endl;
ous<<"The movie type is                > "<<movie_type<<endl;
ous<<"The rating of movie is           > "<<rating<<endl<<endl<<endl;
}

else
ous<<title<<endl<<year<<endl<<running_time<<endl<<movie_type<<endl<<rating<<endl;
}


std::istream& operator >> (std::istream& ins,DVD& d1){
d1.input(ins);
return (ins);
}
std::ostream& operator << (std::ostream& ous,const DVD& d1){
d1.output(ous);
return (ous);
}



