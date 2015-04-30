//***********************************************************************
// File: recommend.cc
// Command Line Arguments: File Name containing movieid/rating scores
//                         File Name containing movie database
//                         Number of Movies to see
//***********************************************************************

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc,char *argv[]) {
  ifstream in1;
  ifstream in2;
  in1.open(argv[1]);
  in2.open(argv[2]);
  int n;
  n=atoi(argv[3]);
  
  vector<pair<double,int> > movie_ratings;
  while(!in1.eof()) {
    double d1;
    int i1;
    in1 >> i1;
    in1 >> d1;
    if (!in1.fail()) {
      movie_ratings.push_back(make_pair(d1,i1));
    }
  }
  map<int,string> movie_titles;
  while (!in2.eof()) {
    int movieid;
    string title;
    string line;
    getline(in2,line);
    if (!in2.fail()) {
      istringstream in3(line);
      in3 >> movieid;
      char c;
      in3 >> c;
      in3 >> c;
      getline(in3,title,':');
      //      cout << "***" << movieid << " " << title << endl;
      movie_titles[movieid]=title;
    }
  }
  sort(movie_ratings.begin(),movie_ratings.end());
  for (int i=movie_ratings.size()-1; (i>=movie_ratings.size()-n) && (i>=0);i--) {
    cout << movie_ratings.size()-i << ".)" << movie_titles[movie_ratings[i].second] << " " << movie_ratings[i].first << endl;
  }
}
  
