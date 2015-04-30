//**************************************************
//
//	Anthony George
//	ag823209@ohio.edu
//	CS 361
//	5/10/12
//
//	Desc:	Header file for CastlesandKnights class
//		as well as Castle class. Implementation
//		found in CastlesandKnights.cc
//
//**************************************************
#include <iostream>     //for cout
#include <vector>       //for vector
#include <utility>      //for pair
using namespace std;

class Castle {
  public:
  Castle(){knights = 0; dragons = 0;}
  friend class CastlesandKnights;
  private:
    int knights;
    int dragons;
};

class CastlesandKnights {
  public:
    CastlesandKnights(){s_knights=0; drag_knights=0; cas_knights=0;}
    int castle_count(vector<string> &image);
    int knight_count(vector<string> &image);
    int safe_knights(vector<string> &image);
    int knights_in_castles(vector<string> &image);
    int knights_in_castles_w_dragons(vector<string> &image);

  private:
    void read(vector<string> &image);

    void add_wall(int row, int col, vector<string> &image);
    bool wall_found(int row, int col);

    bool corner_found(int row, int col);
    bool is_corner(int row, int col, vector<string> &image);

    void invade(int row, int col, Castle &cas, vector<string> &image);
    bool space_found(int row, int col);

    vector<Castle> castles;
    vector<pair<int,int> > wall;
    vector<pair<int,int> > inside;
    Castle courtyard;
    int s_knights;
    int drag_knights;
    int cas_knights;
};
