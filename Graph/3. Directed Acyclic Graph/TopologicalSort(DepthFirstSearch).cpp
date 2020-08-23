/*
	Source to study : https://www.geeksforgeeks.org/topological-sorting/?ref=rp
    
   Aim   :  To Find any of the Topological Ordering of the given DAG (Graph needs to be an acyclic). 
    
   Time Complexity   :  O(V + E)
	
	Note : 	In order to find the topological-sorting of the given graph,
				following DFS based solution assumes graph to be DAG. 
*/

#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

const int mxN = 1005;
vector<int> adj[mxN];

struct topologicalSort{
	
	int n;
	vector<int> *adj;
	vector<bool> used;
	vector<int> toposort;
	
	topologicalSort(int _n, vector<int> *_adj){
		n = _n;
		adj = _adj;
		used.assign(n, 0);
	}
	
	void dfs(int u){
		used[u] = 1;
		for(auto &v :  adj[u]){
			if(!used[v]){
				dfs(v);
			}
		}
		toposort.push_back(u);
	}
	
	vector<int> getTopoOrdering(){
		for(int i = 0; i < n; ++i){
			if(!used[i]){
				dfs(i);
			}
		}
		reverse(begin(toposort), end(toposort));
		return toposort;
	}
};

int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		--u; --v;
		adj[u].push_back(v);
	}
	topologicalSort T(n, adj);
	vector<int> t = T.getTopoOrdering();
	cout << "TopoOrdering for given DAG : ";
	for(auto i : t){
		cout << i + 1 << " ";
	}
}
