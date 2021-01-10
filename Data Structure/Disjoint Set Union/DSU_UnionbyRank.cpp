// caution : not tested...

#include <bits/stdc++.h>
using namespace std;

// DSU with Path Compression + Union by Rank optimization
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
			a = getLeader(a);
			b = getLeader(b);
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