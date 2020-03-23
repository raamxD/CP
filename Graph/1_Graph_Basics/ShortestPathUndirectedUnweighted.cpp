using namespace std;
#include<bits/stdc++.h>
#define ll long long

const int mxN = 1e5;
vector<int> adj[mxN];

vector<int> bfs(int u, int n){
    vector<int> res(n, INT_MAX);
    res[u] = 0;
    queue<int> Q;
    Q.push(u);
    while(!Q.empty()){
        int node = Q.front();
        Q.pop();
        for(int i : adj[node]){
            if(res[i] == INT_MAX){
                res[i] = res[node] + 1;
                Q.push(i);
            }
        }
    }
    return res;
}

int main(){
        
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
	int n,m;
    cin >> n >> m;
    
    for(int i = 0; i < m; ++i){
        int u,v;
        cin >> u >> v;
        --u;--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    cout << "Shortest distance from Node 1 : ";
	vector<int> d1 = bfs(0,n);
	for(int i = 0; i < n; ++i)
		cout << "[" << i+1 << ", " << d1[i] << "] ";
	
	cout << "\nShortest distance from Node " << n << " : ";
	vector<int> dn = bfs(n-1,n);
	for(int i = 0; i < n; ++i)
		cout << "[" << i+1 << ", " << dn[i] << "] ";
}

/*
INPUT : 

6 9
1 2
1 6
2 3
2 6
3 4
3 5
3 6
4 5
5 6

OUTPUT : 

Shortest distance from Node 1 : [1, 0] [2, 1] [3, 2] [4, 3] [5, 2] [6, 1] 
Shortest distance from Node 6 : [1, 1] [2, 1] [3, 1] [4, 2] [5, 1] [6, 0] 

*/