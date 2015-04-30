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
#define REALLY_OPTIMIZE
//#define PARTIAL_OPTIMIZE
#define UNFOUND_DIST 1000000000
using namespace std;
double ** distances;
//double minimum_dist = UNFOUND_DIST;


// hi there how are you?

void find_best2(int * tour, int start, int length,int * optimal,double cost_so_far, double & minimum_so_far){
   
   // with this optimization it runs too fast to measure compute time on any of our tests
   
#ifdef REALLY_OPTIMIZE
    if( cost_so_far > minimum_so_far)
        return;
#else
#ifdef PARTIAL_OPTIMIZE
    if( cost_so_far >= UNFOUND_DIST)
        return;
#endif
#endif
    

    if(start == length){  //on the last node
        double total_cost = cost_so_far +distances[tour[start-1]][tour[0]];
        if (total_cost <minimum_so_far){
                    minimum_so_far=total_cost;
            cout<<"new minimum: "<<minimum_so_far<<endl;

            for(int n=0;n<length;n++)
                optimal[n]=tour[n];
        
        }
        return;
        
    }

    double dist, min=UNFOUND_DIST;
    int temp= tour[start];
    for(int n=start;n<length;n++){
            tour[start]=tour[n];
            tour[n]=temp;
            find_best2(tour,start+1,length,optimal,distances[tour[start-1]][tour[start]]+cost_so_far,minimum_so_far);
            tour[n]=tour[start];
    }
    tour[start]=temp;

       
}



vector<int> parallel_find_best2_inner(int firsttwo_start, int firsttwo_end,int length,double & best , bool & found){
    double min=UNFOUND_DIST;
    int * tour = new int[length];
    int * optimal = new int[length];
    int n,firsttwo;
    for(firsttwo = firsttwo_start ; firsttwo <firsttwo_end;firsttwo++){
        int second = firsttwo %(length-1)+1;
        int third = firsttwo /(length-1)+1;
        if (second == third)
            continue;

        for(n=0;n<length;n++)
            tour[n]=n;
            
        tour[1]=second;
        tour[second]=1;
        tour[1]=second;
        tour[2]=third;
        tour[third]=2;
        find_best2(tour,3,length,optimal,distances[0][second]+distances[second][third],min);
        if(best >min)
            best = min;
    }
    delete tour;
    
    
    vector<int> vi;
    vi.resize(length);
    for(n=0;n<length;n++)
        vi[n]=optimal[n];
    delete optimal;
    if ( best >= UNFOUND_DIST)
        found = false;
    else
        found = true;
    return vi;
}
//vector<int> parallel_find_best2_inner(int firsttwo_start, int firsttwo_end,int length,double & best , bool & found)
struct pthread_findbest2_data{
    int firsttwo_start;
    int firsttwo_end;
    int length;
    double * best;
    bool * found;
};

void * pthread_findbest2(void* input){
    pthread_findbest2_data * pdat = (pthread_findbest2_data *)input;
    vector<int> * i = new vector<int>;
    *i=parallel_find_best2_inner(pdat->firsttwo_start, pdat->firsttwo_end,pdat->length,*pdat->best , *pdat->found);
    return i;
}


vector<int> parallel_find_best2(int length,double & best ,int first, bool & found){
  //  int divs = length*(length-1);
    double best_array[NUM_THREADS];
    bool  found_array[NUM_THREADS];
vector<int>  results[NUM_THREADS];
  pthread_t pthreads[NUM_THREADS];

    int last_pair = (length-1)*(length-1);
    int starts[NUM_THREADS], ends[NUM_THREADS];
    starts[0]=0;
    ends[NUM_THREADS-1]=last_pair;
    int n;
            pthread_findbest2_data  pthread_data[NUM_THREADS];
    for( n=0;n<NUM_THREADS;n++){
        best_array[n]= UNFOUND_DIST;
        found_array[n]=false;
        pthread_data[n].firsttwo_start = (n*last_pair)/NUM_THREADS;
        pthread_data[n].firsttwo_end   = ((n+1)*last_pair)/NUM_THREADS;
        pthread_data[n].length = length;
        pthread_data[n].best = &best_array[n];
        pthread_data[n].found = & found_array[n];
//        results[n]=*(vector<int>*)pthread_findbest2((void*)&pthread_data[n]);
        pthread_create(&pthreads[n],NULL,pthread_findbest2,(void*)&pthread_data[n] );
    }
    for(n=0;n<NUM_THREADS;n++){
        void ** ret_vec = new void*;
        pthread_join (pthreads[n],ret_vec);
        results[n] = *(vector<int>*)*ret_vec;
        
    }
    best = UNFOUND_DIST;
    int bestrun=0;
    for(n=0;n<NUM_THREADS;n++){
        if(best_array[n] <=best){
            best = best_array[n];
            found=found_array[n];
            bestrun=n;
        }
    }
    return results[bestrun];
    
    
}

vector<int> find_best2_wrapper(int length,double & best ,int first, bool & found){
    double min=UNFOUND_DIST;
    int * tour = new int[length];
    int * optimal = new int[length];
    int n;
    for(n=0;n<length;n++)
        tour[n]=n;
        
        tour[first]=0;
        tour[0]=first;
    find_best2(tour,1,length,optimal,0.0,min);
    best = min;
    delete tour;
    
    
    vector<int> vi;
    vi.resize(length);
    for(n=0;n<length;n++)
        vi[n]=optimal[n];
    delete optimal;
    if ( best >= UNFOUND_DIST)
        found = false;
    else
        found = true;
    return vi;
}

int main() {
  int n,j,k,length;
  cin >> n;
  length=n;
  string line;
  getline(cin,line); // Get the newline
  vector<list<pair<int,double> > > adj_list;
  int first=-1;
  adj_list.resize(n);
    distances = new double*[n];
    for(j=0;j<n;j++){
        distances[j] = new double[n];
        for(k=0;k<n;k++)
            distances[j][k]=UNFOUND_DIST;
    }
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
        if(first == -1)
            first = j;
      adj_list[j].push_back(make_pair(i,w));
      distances[j][i]=w;
      distances[i][j]=w;
    }
      }
    }
  }
  
  vector<int> opt;
  bool found;
  double opt_dist;
  cout << "Done Reading the Graph" << endl;
 // opt = Minimum_TSP_tour(adj_list,opt_dist,found);
    opt = parallel_find_best2(length,opt_dist,first,found);
   // found=true;
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