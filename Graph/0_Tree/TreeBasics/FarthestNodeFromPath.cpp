using namespace std;
#include<bits/stdc++.h>
#define ll long long

// total vertices of tree
const int mxN = 1000;
vector<int> G[mxN];
int n;

// returns {distance, node} pair of farthest node from path 'v'.
// returns {-1,-1} if no such node is present.
pair<int,int> bfs(vector<int> v){
	
	vector<int> dp(n,-1);
	queue<int> Q;
	for(int z : v) dp[z] = 0, Q.push(z);
 
	while(!Q.empty()){
		int node = Q.front();
		Q.pop();
		for(auto z : G[node]){
			if(dp[z] == -1){
				dp[z] = dp[node] + 1;
				Q.push(z);
			}
		}
	}
	pair<int,int> res = {-1,-1};
	for(int i=0; i<n; i++){
		if(dp[i] > res.first)
			res = {dp[i],i};
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	return 0;
}
