#include <bits/stdc++.h>
using namespace std;
int findfather(int x,vector<int>&unionsets){
if(x==unionsets[x]){return x;}
else{return unionsets[x]=findfather(unionsets[x],unionsets);}
}
void unions(int x,int y,vector<int>&unionsets){
    int fx=findfather(x,unionsets);
    int fy=findfather(y,unionsets);
unionsets[fx]=fy;
}
struct edge{
    int x;
	int y;
	int weight;
    operator<(const edge& other)const{
        return weight<other.weight;
    }
};
int main(){
int n;
cin>>n;
    vector<edge>picture;
for(int i=1;i<=n;i++){
for(int j=1;j<=n;j++){
    int temp;
    cin>>temp;
        if(i<j){picture.push_back({i,j,temp});
    }
}
}
vector<int>fortext(n-1,0);
    vector<int>unionsets(n+1,0);
    int answer=0;
    for(int i=1;i<=n;i++){
unionsets[i]=i;}
    sort(picture.begin(),picture.end());
    for(edge u:picture){
if(findfather(u.x,unionsets)==findfather(u.y,unionsets)){continue;}
else{answer+=u.weight;fortext.push_back(u.weight);unions(u.x,u.y,unionsets);}
    }
    cout<<answer;
    for(int i=0;i<=n-2;i++){
		cout<<fortext[i]<<endl;
	}
    return 0;
}
