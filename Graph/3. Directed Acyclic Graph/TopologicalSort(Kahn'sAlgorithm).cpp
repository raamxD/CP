/* 
	Source to study : https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
    
   Aim   :  To Find any of the Topological Ordering of the given DAG.
				If the given graph is not a DAG, return empty vector else return any of the topo ordering.
    
   Time Complexity   :  O(V + E)
	
	Note : Kahn's Algorithm also check if the given graph is DAG and doesn't contain cycle.
			If it contains cycle, it returns an empty vector.
*/

#include <bits/stdc++.h>
using namespace std;

struct KahnsAlgorithm{
	
	int n;
	vector<int> *adj;
	vector<int> indegree;
	vector<int> toposort;
	
	KahnsAlgorithm(int _n, vector<int> *_adj){
		n = _n;
		adj = _adj;
		indegree.assign(n, 0);
		for(int i = 0; i < n; ++i){
			for(auto u : adj[i]){
				indegree[u]++;
			}
		}
	}
	// Returns one of the topological ordering of DAG, if exist.
	// if not (when cycle is present), returns empty vector
	vector<int> getTopoOrdering(){
		queue<int> Q;
		for(int i = 0; i < n; ++i){
			if(!indegree[i]){
				Q.push(i);
			}
		}
		int visnodescnt = 0;
		while(!Q.empty()){
			++visnodescnt;
			int u = Q.front();
			Q.pop();
			toposort.push_back(u);
			for(auto v : adj[u]){
				if(!(--indegree[v])){
					Q.push(v);
				}
			}
		}
		if(visnodescnt != n){
			// cycle exists and thereby given graph isn't a DAG
			toposort.clear();
		}
		return toposort;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> adj[n];
	for(int i = 0; i < m; ++i){
		// edge directed from vertex 'u' to vertex 'v'
		int u, v;
		cin >> u >> v;
		--u; --v;
		adj[u].push_back(v);
	}
	KahnsAlgorithm K(n, adj);
	vector<int> t = K.getTopoOrdering();
	if(!int(t.size())){
		cout << "Given graph is not a DAG, as it contains a cycle!!";
	}else{
		cout << "TopoOrdering for given DAG : ";
		for(auto i : t){
			cout << i + 1 << " ";
		}
	}
	return 0;
}

/*

INPUT : 

6 6
1 2
2 3
3 4
4 5
5 6
6 1

OUTPUT : 

Given graph is not a DAG, as it contains a cycle!!

*/