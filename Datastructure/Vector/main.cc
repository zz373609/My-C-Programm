#include <iostream>
#include "Wordoku.cc"
#include <cassert>
using namespace std;


int main() {
  Wordoku obj;
  int i=1;
  while (!cin.eof()) {
    string letters;
    cin >> letters;
    //cout << letters << endl;

    
    if (!cin.fail()) {
      assert(letters.length()==9);
      vector<string> board;
      for (int j=0;j<9;j++) {
	string t;
	cin >> t;
	board.push_back(t);
      }
      bool res;
      cin >> res;
      //cout << res << endl;
      if (obj.valid(board,letters)==res) {
	cout << "Test " << i << " passed" << endl;
      } else {
	cout << "Test " << i << " failed" << endl;
      }
      i++;
    } 
  }
}

    
    
