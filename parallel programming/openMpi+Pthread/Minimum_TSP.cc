//***************************************************************
// File: Minimum TSP.cc
// Author: David W. Juedes
// Purpose: This code finds the optimal traveling salesman (person) tour
// in a graph with weighted edges.
//****************************************************************
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
using namespace std;


double distance(vector<list<pair<int,double> > >&adj_list,
		vector<int> &tour, bool &valid) {
  // Tests whether the tour is valid
  // Returns the total distance

  int start = tour[0];
  double distance  =0;
  valid = true;
  for (int i=1;i<tour.size();i++) {
    bool found = false;
    // Is there an edge from tour[i-1] to tour[i]
    for (list<pair<int,double> >::iterator p = adj_list[tour[i-1]].begin();
	 p!=adj_list[tour[i-1]].end();++p) {
      if (p->first == tour[i]) {
	found = true;
	distance += p->second;
	break;
      }
    }
    if (!found) valid = false;
  }
  bool found = false;
  // Is there an edge from tour[i-1] to tour[i]
  for (list<pair<int,double> >::iterator p = adj_list[tour[tour.size()-1]].begin();
       p!=adj_list[tour[tour.size()-1]].end();++p) {
    if (p->first == tour[0]) {
      found = true;
      distance += p->second;
      break;
    }
  }
  if (!found) valid = false;
  return distance;
}


vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it) {
  int n = adj_list.size();
  vector<int> perm;
  vector<int> opt;
  perm.resize(n);
  for (size_t i=0;i<n;i++) {
    perm[i] = i;
  }
  bool t_found = false;
  double min_dist;
  int c = 0;
  do{
    bool found;
    double dist;
    dist = distance(adj_list,perm,found);
    if (!t_found) {
      if (found) {
	min_dist = dist;
	t_found = true;
	opt = perm;
      }
    } else {
      if ((found)&&(dist < min_dist)) {
	min_dist = dist;
	t_found = true;
	opt = perm;
      }
    }
    //cout << "Here" << endl;
    //for (int i=0;i<n;i++) {
    //  cout << perm[i] << " ";
    //}
    //cout << endl;
    c++;
    //if (c%100000 == 0) 
    cout << c << endl;
    
  }while(next_permutation(perm.begin(),perm.end()));
  found_it = t_found;
  total_dist = min_dist;
  return opt;
}

int main() {
  int n;
  cin >> n;
  
  string line;
  getline(cin,line); // Get the newline
  vector<list<pair<int,double> > > adj_list;
  adj_list.resize(n);

  while (!cin.eof()) {
    getline(cin,line);
    if (!cin.fail()) {
      istringstream in(line);

      int j;
      in >> j;
      char c;
      in >> c;
      assert(c==':');
      while (!in.eof()) {
	int i;
	double w;
	in >> i;
	in >> w;
	if (!in.fail()) {
	  adj_list[j].push_back(make_pair(i,w));
	}
      }
    }
  }
  vector<int> opt;
  bool found;
  double opt_dist;
  cout << "Done Reading the Graph" << endl;
  opt = Minimum_TSP_tour(adj_list,opt_dist,found);
  if (found) {
    cout << "Optimum TSP Tour length = " << opt_dist << endl;
    cout << "Tour = ";
    for (int i=0;i<opt.size();i++) {
      cout << opt[i] << " ";
    }
    cout << endl;
  } else {
    cout << "No Hamiltonian Tour" << endl;
  }
}
