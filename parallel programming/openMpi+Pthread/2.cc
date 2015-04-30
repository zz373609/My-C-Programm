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


vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it,int offset) {
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
  
  do {
      if(c%NUM_THREADS == offset ){
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
      if ((found)&&((dist < min_dist) ||( dist == min_dist && perm[0] < opt[0]    ))) {
	min_dist = dist;
	t_found = true;
	opt = perm;
      }
    }
      }
      c++;
    //cout << "Here" << endl;
    //for (int i=0;i<n;i++) {
    //  cout << perm[i] << " ";
    //}
    //cout << endl;
    //c++;
    //if (c%100000 == 0) cout << c << endl;

  }  while (next_permutation(perm.begin(),perm.end()));
  found_it = t_found;
  total_dist = min_dist
;
  return opt;
}

struct  Minimum_TSP_tour_args{
 vector<list<pair<int,double> > >* adj_list;
 double *total_dist;
 bool * found_it;
 int offset;
 };
 
 void* Minimum_TSP_tour_pt(void* va1){
     Minimum_TSP_tour_args * margs  = (Minimum_TSP_tour_args*)va1;
     vector<int> * vi = new vector<int>;
     *vi=Minimum_TSP_tour(*margs->adj_list,*margs->total_dist,*margs->found_it,margs->offset);
     return (void*)vi;
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
  vector<int> opt[NUM_THREADS];
  bool found;
  double opt_dist;
  cout << "Done Reading the Graph" << endl;
double opt_dists[NUM_THREADS];
    Minimum_TSP_tour_args tspargs[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
  for( n = 0 ; n < NUM_THREADS;n++){
        tspargs[n].adj_list=&adj_list;
        tspargs[n].total_dist = &opt_dists[n];
        tspargs[n].found_it = &found;
        tspargs[n].offset=n;
  
          //opt[n]=*(vector<int>*)Minimum_TSP_tour((void*)&tspargs[n]);
        pthread_create(&threads[n],NULL,Minimum_TSP_tour_pt,(void*)&tspargs[n]);
  }
  for(n=0;n<NUM_THREADS;n++){
  	void ** v = new void*;
  	pthread_join(threads[n],v);
	opt[n] = *(vector<int>*)*v;
	}
vector<int> opts= opt[0];
    double minimum=opt_dists[0];
    for(n=1;n<NUM_THREADS;n++){
        if(opt_dists[n]<minimum || (opt_dists[n] == minimum&& (opt[n])[0] < opts[0] )){
            opts=opt[n];
            minimum=opt_dists[n];
        }
    }

  if (found) {
    cout << "Optimum TSP Tour length = " << minimum << endl;
    cout << "Tour = ";
    for (int i=0;i<opts.size();i++) {
      cout << opts[i] << " ";
    }
    cout << endl;
  } else {
    cout << "No Hamiltonian Tour" << endl;
  }
}
