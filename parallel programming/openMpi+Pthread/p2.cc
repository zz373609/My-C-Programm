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
#include <pthread.h>
#include <list>
#define THREADS 8
using namespace std;


int factorial(int N){
	cout<<N<<endl;
    int factorial = 1;
    for(int M=2;M<=N;M++)
        factorial*=M;
    return factorial;
}

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

vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it, vector<int> start_permutation, int num_permutations);

struct tsparg {
    vector<list<pair<int,double> > > * adj_list;
    double * total_dist;
    bool *found_it;
    vector<int> start_permutation;
    int num_permutations;
};
void* Minimum_TSP_tour_pthread(void*);

vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it) {
  int n = adj_list.size();
  vector<int> perm;
  perm.resize(n);
  bool t_found = false;
  tsparg tsp_args[THREADS];
  double min_dist;
  //int c = 0;
  int threadno;
  
  pthread_t pthreads[THREADS];
  
  vector<int> opt, permsp[THREADS];
  vector<int>*  optimals[THREADS];
  int runs[THREADS], total_runs = factorial(n);
  perm.resize(n);
  double total_distances[THREADS];
  bool found_array[THREADS];
 
  for (size_t i=0;i<n;i++) {
    perm[i] = i;
  }
  cout<<"preparing parallel\n";
  //setup for parallel for
  for(threadno=0;threadno<THREADS;threadno++){
      runs[threadno] = (total_runs * (threadno+1))/THREADS-(total_runs*threadno)/THREADS;
      permsp[threadno] = perm;
      total_distances[threadno] = total_dist;
      found_array[threadno]= false;
	tsp_args[threadno].adj_list = &adj_list;
	tsp_args[threadno].total_dist = &total_distances[threadno];
	tsp_args[threadno].found_it = &found_array[threadno];
	tsp_args[threadno].start_permutation = perm;
	tsp_args[threadno].num_permutations = runs[threadno];
      if ( threadno <THREADS-1)
      for(int run_number = 0 ; run_number <runs[threadno];run_number++){
            next_permutation(perm.begin(),perm.end());
      }
      
  }
  //for()
  //sumary of parallel results
  for(threadno=0;threadno<THREADS;threadno++)
        pthread_create(&pthreads[threadno],NULL,Minimum_TSP_tour_pthread,(void*)&tsp_args[threadno]);

  bool found = false;
  double min_distance;
  int min_distance_position;
  for(threadno=0;threadno<THREADS;threadno++){
  	pthread_join(pthreads[threadno],(void**)&optimals[threadno]);
    if(found_array[threadno]){

        if ( ! found){
          min_distance = total_distances[threadno];
          min_distance_position = threadno;
          found=true;
        }
        else if    (  total_distances[threadno] <min_distance){
          min_distance = total_distances[threadno];
          min_distance_position = threadno;
        }
    }
  }
  found_it = found;
  if(found){
      total_dist = total_distances[min_distance_position];
      return *optimals[min_distance_position];
  }
  return opt;
  
}
void* Minimum_TSP_tour_pthread(void* param) {
    tsparg * ta = (tsparg*)param;
    vector<int> * optimal = new vector<int>;
    *optimal = Minimum_TSP_tour(*ta->adj_list, *ta->total_dist,*ta->found_it, ta->start_permutation, ta->num_permutations);
    return (void*) optimal;
}

vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it, vector<int> start_permutation, int num_permutations) {
  int n = adj_list.size();
  vector<int> perm;
  vector<int> opt;
  //perm.resize(n);
  perm = start_permutation;
 
  bool t_found = false;
  double min_dist;
  //int c = 0;
  for(int count=0;count<num_permutations;count++) {
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
    //c++;
    //if (c%100000 == 0) cout << c << endl;
    next_permutation(perm.begin(),perm.end());
  } 
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
