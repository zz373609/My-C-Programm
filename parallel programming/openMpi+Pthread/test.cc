#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int main(){
vector<int> te(3);
std::queue<vector<int> > myq;

for(int i = 0;i<te.size();i++)
{
te[i] = i;
}
int i = 0;
do{

myq.push(te);

}while(next_permutation(te.begin(),te.end()));
//while(!myq.empty()){
std::cout<<myq[1]<<endl;
//cout<<"good";
//myq.pop();
//}


return 0;


}