#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

class Scanner {
 public:
  int current_token(istream &in, string& token) {
    token = tok_str;
    return tok;
  }
  void get_next(istream &in) {
    tok = next_token(in,tok_str);
  }
  private:
    int tok;
    string tok_str;
    
  int next_token(istream &in, string &token) {
    //
    token = "";
    char c;
    while (isspace(in.peek())) {
      in.get(c);
    }
    if (in.fail()) {
      if (in.eof()) {
	return 0;
      }
    }
    string t;
    if (isalnum(in.peek())) {
	// MAJORITY, AND, OR, NOT, or integer
      while (isalnum(in.peek())) {
	in.get(c);
	t+=c;
      }
      token = t;
      return 1;
    }
    
    if (in.peek()==')') {
      in.get(c);
      return c;
    }
    if (in.peek()=='(') {
      in.get(c);
      return c;
    }
    if (in.fail()) {
      return 0;
    }
    cout << in.peek() << endl;
    return -1;
  }

};
	
