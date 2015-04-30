#include <iostream>
#include <vector>
#include <string>

#include "CastlesandKnights.h"

using namespace std;


int main() {

  vector<string> image;


  int max_len = 0;
  string line;
  while (!cin.eof()) {
    getline(cin,line);
    if (!cin.fail()) {
      if (line.length()>max_len) {max_len = line.length();}
      
      image.push_back(line);
    }
  }
  for (size_t i=0;i<image.size();i++) {
    if (image[i].length()<max_len) {
      for (size_t j=image[i].length(); j<max_len;j++) {
	image[i]+=' ';
      }
    }
    cout << image[i] << endl;
  }
  CastlesandKnights obj;

  cout << "Number of Castles = " << obj.castle_count(image) << endl;
  cout << "Number of Knights = " << obj.knight_count(image) << endl;
  cout << "Number of Safe Knights = " << obj.safe_knights(image) << endl;
  cout << "Number of Knights in Castles= " << obj.knights_in_castles(image) << endl;
  cout << "Number of Knights in Castles w Dragons= " << obj.knights_in_castles_w_dragons(image) << endl;
 
  

}
