//name: zhiqiang zhang
//email: zz373609@ohio.edu
//description : first parallel progarm
//date: 2014/2/6

#include<iostream>
#include<omp.h>
using namespace std;

void one(){
#pragma omp critical
	{
		cout<<"Hello form thread "<<omp_get_thread_num()<<endl;
		cout<<"This is <Zhiqiang Zhang>'s first parallel program"<<endl;
		cout<<"There are currently "<<omp_get_num_threads()<<" threads running"<<endl<<endl;
	}


}


int main(){
#pragma omp parallel
one();
return 0;
}