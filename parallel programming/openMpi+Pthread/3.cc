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
#include <pthread.h>
#define NUM_THREADS 4
using namespace std;


vector<list<pair<int,double> > >adj_list; 
vector<int> opt;
bool t_found = false;
double min_dist;


struct dist_args{
    vector<int> new_perm;
    bool found;

};


double distance(vector<int> &tour, bool &valid) {
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


void* Minimum_TSP_tour(void*args) {
  int threadno = *(int*)args;
  int n = adj_list.size();
  vector<int> perm;
  perm.resize(n);
  for (size_t i=0;i<n;i++) {
    perm[i] = i;
  }
  int perm_number = 0;
  do{
  	if(perm_number%NUM_THREADS == threadno){// if its our threads turn to calculate
        bool found;
        double dist;
        dist = distance(perm,found);
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
	            opt =perm;
            }
        }
  	}
    perm_number++;
  }  while (next_permutation(perm.begin(),perm.end()));
  return NULL;
}

int main() {
  int n;
  cin >> n;
  
  string line;
  getline(cin,line); // Get the newline
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
  //bool found;
  //double opt_dist;
  cout << "Done Reading the Graph" << endl;
  
  pthread_t THREADS[NUM_THREADS];
  int threadnos[NUM_THREADS];
  for(n=0;n<NUM_THREADS;n++){
      threadnos[n]=n;
        pthread_create(&THREADS[n],NULL,Minimum_TSP_tour,(void*)&threadnos[n]);
  }
  void * a;
  for(n=0;n<NUM_THREADS;n++)
    pthread_join (THREADS[n],&a);
  
  
  if (t_found) {
    cout << "Optimum TSP Tour length = " <<  min_dist << endl;
    cout << "Tour = ";
    for (int i=0;i<opt.size();i++) {
      cout << opt[i] << " ";
    }
    cout << endl;
  } else {
    cout << "No Hamiltonian Tour" << endl;
  }
}
