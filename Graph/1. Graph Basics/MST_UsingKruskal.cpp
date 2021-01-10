// caution : not tested...

#include <bits/stdc++.h>
using namespace std;

struct DSU{
	
		int N;
		vector<int> leader;
		vector<int> rank;
		
		DSU(int _N){
			N = _N + 1;
			leader.assign(N);
			rank.assign(N);
		}
		void newSet(int x){
			leader[x] = x;
			rank[x] = 0;
		};
		int getLeader(int x){
			if(leader[x] == x)
				 return x;
		   return leader[x] = getLeader(leader[x]);
		}
		void mergeSets(int a, int b){
			a = getLeader[a];
			b = getLeader[b];
			if(a != b){
				if(rank[a] > rank[b]) 
					swap(a, b);
				leader[a] = b;
				if(rank[a] == rank[b])
					++rank[b];
			}
		}
		bool alikeLeader(int a, int b){
			return (getLeader(a) == getLeader(b));
		}
};
struct edge{
	int u, v, weight;
	bool operator <(edge const& other){
		return weight < other.weight;
	}
};
struct MinimumSpanningTree{

	int n;
	long long cost;
	vector<edge> edges;
	vector<edge> spanningEdges
	
	MinimumSpanningTree(int _n, vector<ar<int, 2>> *_adj){
		n = _n;
		cost = 0;
		for(int u = 0; u < n; ++u){
			for(auto[v, w]  : adj[u]){
				edges.push_back({u, v, w});
			}
		}
	}
	void process(){
		DSU dsu(n);
		for(int i = 0; i < n; ++i){
			dsu.newSet(i);
		}
		sort(begin(edges), end(edges));
		for(edge e : edges){
			if(!dsu.alikeLeader(e.u, e.v)){
				cost += e.weight;
				spanningEdges.push_back(e);
				dsu.mergeSets(e.u, e.v);
			}
		}
	}
	long long getCost(){
		return cost;
	}
	vector<edge> getEdges(){
		return spanningEdges;
	}
};
