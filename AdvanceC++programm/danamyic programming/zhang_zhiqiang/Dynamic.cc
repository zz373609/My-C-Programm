#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;

/*find the min about two variable*/
int min(int x, int y);
/*find the min about three variable*/
int smallest(int x, int y, int z);
/*read file about the data in two vector*/
void read_file(string file, vector<int>& u, vector<int>& v);
/*make the matrix optimal value for each about the dynamic programming*/
void make_table(vector<int>&u, vector<int>&v, vector< vector<int> > &D);
/*recessively find the solution*/
void find_path(int x, int y, vector< vector<int> >&path,vector<int>&u, vector<int>&v);

int main(int argc, char *argv[]){

	vector<int> ulist;
	vector<int> vlist;
	
	ulist.push_back(0);
	vlist.push_back(0);
	read_file(argv[1],ulist,vlist);
	
	vector< vector<int> > Dlist(ulist.size(),vector<int>(vlist.size()));
	make_table(ulist,vlist,Dlist);
	
	int end_u = ulist.size()-1;
	int end_v = vlist.size()-1;
	find_path(end_u,end_v,Dlist,ulist,vlist);
	cout<<"("<<ulist[end_u]<<","<<vlist[end_v]<<")"<<" ";
	cout<<endl;
	cout<<Dlist[ulist.size()-1][vlist.size()-1]<<endl;

return 0;
}


/*function to find the smallest from three number*/
int min(int x, int y){
	if(x<y)
	 return x;
	 else
	 	return y;

}

int smallest(int x, int y, int z){
	return min(min(x,y),z);
}

/*read the numbers from the file*/
void read_file(string file, vector<int>& u, vector<int>& v){
	ifstream input;
	
	input.open(file.c_str());
	int temp;
	while (input.peek() != '\n')
	{
		input >> temp;
		u.push_back(temp);
	}
	if(input.peek() == '\n'){
		input.ignore();
	}
		while (input.peek() != '\n')
	{
		input >> temp;
		v.push_back(temp);
	}
	
	input.close();
}

/*make the dynamic table*/
void make_table(vector<int>&u, vector<int>&v, vector< vector<int> > &D){
	D[0][0] = 0;
	
	for(int i = 1; i < u.size(); i++)
		for(int j = 1; j < v.size(); j++){
			if(i == 1&&j==1){
				D[i][j] = abs(u[i]-v[j]) + D[0][0];
			}
			else if(i == 1&&j !=1){
				D[i][j] = abs(u[i]-v[j]) + D[i][j-1];
			}
			else if(i != 1&& j ==1){
				D[i][j] = abs(u[i]-v[j]) + D[i-1][j];
			}
			else{
				D[i][j] = abs(u[i]-v[j])+smallest(D[i-1][j],D[i][j-1],D[i-1][j-1]);
		}
	}

}

/*give the path of minimal path*/ 
void find_path(int x, int y, vector< vector<int> >&path,vector<int>&u, vector<int>&v){
	int track;
	if(x<=1&&y<=1)
		return;
		else{
			if(x == 1&&y ==1){
				cout<<"("<<u[x]<<","<<v[y]<<")"<<" ";
			}
			else if(x == 1&&y != 1){
				 y = y-1;
				cout<<"("<<u[x]<<","<<v[y]<<")"<<" ";
			}
			else if(x !=1 && y==1){
				x = x-1;
				cout<<"("<<u[x]<<","<<v[y]<<")"<<" ";
			}
			else{
		track = smallest(path[x-1][y],path[x][y-1],path[x-1][y-1]);
		if(path[x-1][y] == track)
			x = x-1;
			else if(path[x][y-1] == track)
				y = y-1;
				else{
					x = x-1;
					y = y-1;
				}
		find_path(x,y,path,u,v);
		cout<<"("<<u[x]<<","<<v[y]<<")"<<" ";
		}
	}
		
}

