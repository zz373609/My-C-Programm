#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include <omp.h>
#define THREADS 4
using namespace std;


int factorial(int N){
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



vector<int> Minimum_TSP_tour(vector<list<pair<int,double> > >&adj_list, double &total_dist, bool &found_it) {
  int n = adj_list.size();
  vector<int> perm;
  perm.resize(n);
  bool t_found = false;
  double min_dist;
  //int c = 0;
  int threadno;
  
  
  
  vector<int> opt, optimals[THREADS], permsp[THREADS];
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
      for(int run_number = 0 ; run_number <runs[threadno];run_number++){
            next_permutation(perm.begin(),perm.end());
      }
      
  }
  cout<<"running parallel\n";
  //parallelizable for
  #pragma omp parallel for

  for(threadno = 0 ; threadno<THREADS;threadno++){
  	cout <<"thread no: "<<threadno<<endl;
      optimals[threadno] = Minimum_TSP_tour(adj_list,total_distances[threadno],found_array[threadno],permsp[threadno],runs[threadno]);
      
  }
  cout <<"combining\n";
  //for()
  //sumary of parallel results
  bool found = false;
  double min_distance;
  int min_distance_position;
  for(threadno=0;threadno<THREADS;threadno++){
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
      return optimals[min_distance_position];
  }
  return opt;
  
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