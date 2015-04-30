//****************************************************
//
//	Anthony George
//	ag823209@ohio.edu
//	CS 361
//	5/10/12
//
//	Desc:	Dragons have come to kill the knights. We must
//		discover various details about their location,
//		though, we will not be helping them.
//
//		Implementation file for CastlesandKnights class
//		as well as Castle class.
//		Maps are stored as graphs in a vector of strings.
//		This program will take in a map and compute some
//		graphical details about it.
//
//****************************************************
#include "CastlesandKnights.h"
#include <iostream>

void CastlesandKnights::invade(int row, int col, Castle &cas, vector<string> &image){
  if(image[row][col] == '#') return;
  if(space_found(row,col)) return;
  if(image[row][col] == 'K') cas.knights++;
  if(image[row][col] == 'D') cas.dragons++;

  pair<int,int> space(row,col);
  inside.push_back(space);

  int width = image[0].length();
  int height = image.size();
  if(row + 1 < height) invade(row+1,col,cas,image); 
  if(col + 1 < width) invade(row,col+1,cas,image);
  if(row) invade(row-1,col,cas,image);
  if(col) invade(row,col-1,cas,image);
}

void CastlesandKnights::read(vector<string> &image) {
  int width = image[0].length();
  int height = image.size();
  for(int col = 0; col < width; col++){
    for(int row = 0; row < height; row++){
       if(image[row][col] == '#'
          && (col + 1 < width) && (row + 1 < height)
          && is_corner(row,col,image)
          && !wall_found(row,col)){
         Castle cas;
         castles.push_back(cas);
         add_wall(row,col,image);
         invade(row+1,col+1,cas,image);
         if(cas.dragons) drag_knights += cas.knights;
         else s_knights += cas.knights;
         cas_knights+=cas.knights;
       }
    }
  }
  int row, col;
  for(col = 0; col < width; col++){
    for(row = 0; (row < height) && (image[row][col] != ' '); row++);
  }
  invade(row,col,courtyard,image);
}

void CastlesandKnights::add_wall(int row, int col, vector<string> &image){
  if(image[row][col] != '#') return;
  if(wall_found(row,col)) return;
  pair<int,int> n_wall(row,col);
  wall.push_back(n_wall);

  int width = image[0].length();
  int height = image.size();
  if(row + 1 < height) add_wall(row+1,col,image);
  if(col + 1 < width) add_wall(row,col+1,image);
  if(row) add_wall(row-1,col,image);
  if(col) add_wall(row,col-1,image);

}

bool CastlesandKnights::wall_found(int row, int col){
  for(vector<pair<int,int> >::iterator q = wall.begin(); q != wall.end(); ++q){
    if(q->first == row && q->second == col) return true;
  }
  return false;
}

bool CastlesandKnights::space_found(int row, int col){
  if(inside.empty()) return false;
  for(vector<pair<int,int> >::iterator p = inside.begin(); p != inside.end(); ++p){
    if(p->first == row && p->second == col) return true;
  }
  return false;
}


//pre-condition: image[row][col] is not a character on the the south or 
//east edge of the map
bool CastlesandKnights::is_corner(int row, int col, vector<string> &image){
  return image[row+1][col] == '#'
         && image[row][col+1] == '#'
         && image[row+1][col+1] == ' ';
}

int CastlesandKnights::castle_count(vector<string> &image){
  if(castles.empty()) read(image);
  if(castles.empty()) return 0;
  int sum = 0;
  for(vector<Castle>::iterator p = castles.begin(); p != castles.end(); ++p){
    sum++;
  }
  return sum;
}

int CastlesandKnights::knight_count(vector<string> &image){
  if(castles.empty()) read(image);
  int sum = 0;
  sum += cas_knights;
  sum += courtyard.knights;
  return sum;
}

int CastlesandKnights::safe_knights(vector<string> &image){
  if(castles.empty()) read(image);
  int sum = 0;
  sum += s_knights;
  if(!courtyard.dragons){
    sum += courtyard.knights;
  }
  return sum;
}

int CastlesandKnights::knights_in_castles(vector<string> &image){
  if(castles.empty()) read(image);
  return cas_knights;
}

int CastlesandKnights::knights_in_castles_w_dragons(vector<string> &image){
  if(castles.empty()) read(image);
  return drag_knights;
}
