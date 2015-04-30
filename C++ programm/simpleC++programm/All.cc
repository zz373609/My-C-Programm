//  Name    :  Zhang Zhiqiang
//  Email   :  zz373609@ohio.edu
//
//  Class   :  CS2401 sum
//
//  Discripation: The colloction of DVD
// 
//  Date    :  2013/7/8
#include "All.h"
#include<iostream>
using namespace std;
/*constractor*/
All::All(){
for(int i=0;i<SIZE; i++)
{
dvd[i].set_title("");
dvd[i].set_year(0);
dvd[i].set_running_time("");
dvd[i].set_movie_type("");
dvd[i].set_rating("");
}
used = 0;
}

int All::get_used(){
return used;
}

/*The void function insert is for inserting new dvd*/
void All::insert(std::istream& ins){
char choice;
do{
if(used<SIZE)
{
ins>>dvd[used];
used++;
cout<<"Want to add one more movie (y/n)> ";
cin>>choice;
}
}while(choice == 'y');
}

/*The function is for dispalying all dvd*/
void All::display(std::ostream& ous){
for(int i =0;i < used;i++)
ous<<dvd[i];
}

/*The function is for dispalying all dvd by rating*/
void All::display_by_rating(std::ostream& ous){
std::string ra;
bool done = true;
char junk;
cout<<"ratings have "<<"G"<<" "<<"PG-13"<<" "<<"R"<<" "<<"X"<<endl;
cout<<"Please Enter the rating you want to dispaly > ";
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,ra);
for(int i = 0;i<used;i++){
if(dvd[i].get_rating()==ra){
ous<<dvd[i];
done = false;
}
}
if(done)
cout<<"There are no movie belong to this rating  "<<endl;
}

/*The function is for removing dvd you do not want*/
void All::remove(){
std::string rm;
char junk;
cout<<"Please enter the movie name you want to remove > ";
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,rm);
bool done = true;
for(int i= 0; i<used;i++){
if(rm == dvd[i].get_title()){
dvd[i]=dvd[used-1];
used--;
done = false;
}

}
if(done)
cout<<"You may have already removed this movie"<<endl<<endl;

}

/*The function is for searching your favoriate dvd*/
void All::search_by_title(){
std::string sr;
char junk;
cout<<"Please enter the movie name you want to find > ";
getline(cin,sr);
if(cin.peek()=='\n')
cin.get(junk);
getline(cin,sr);
bool done = true;
for(int i =1;i<used;i++){
if(sr == dvd[i].get_title()){
cout<<dvd[i];
done = false;
}
}
if(done)
cout<<"There is no this movie"<<endl<<endl;
}


/*The function is for sorting the dvds by title*/
void All::sort_by_title(){
bool done = true;
DVD temp;
while(done){
done = false;
for(int i = 0;i<used-1;i++)
{
if(dvd[i].get_title()>dvd[i+1].get_title())
{
temp=dvd[i];
dvd[i]=dvd[i+1];
dvd[i+1]= temp;
done = true;
}
}
}
}


/*The function is for sorting the dvds by year*/
void All::sort_by_year(){
bool done = true;
DVD temp;
while(done){
done = false;
for(int i = 0;i<used-1;i++)
{
if(dvd[i].get_year()>dvd[i+1].get_year())
{
temp=dvd[i];
dvd[i]=dvd[i+1];
dvd[i+1]= temp;
done = true;
}
}
}
}

/*The function is for loading dvd from file*/
void All::load_file(std::istream& ins){
while(ins>>dvd[used]&&used<SIZE){
used++;
}
}
/*This function is meau for user to enter*/
void meau(){
cout<<endl;
cout<<"1.Insert the new movie"<<endl;
cout<<"2.Remove the movie you dislike"<<endl;
cout<<"3.Search the movie you want to watch"<<endl;
cout<<"4.Sort the movies by title"<<endl;
cout<<"5.Sort the movies by years"<<endl;
cout<<"6.Display all movie "<<endl;
cout<<"7.Dispaly all movie by rating"<<endl;
cout<<"8.Back up the movie in the file"<<endl;
cout<<"9.End of the program"<<endl;
cout<<endl;
}







