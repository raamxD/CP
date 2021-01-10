// caution : not tested...

#include <bits/stdc++.h>
using namespace std;

// DSU with Path Compression + Union by Size optimization
struct DSU{
	
		int N;
		vector<int> leader;
		vector<int> size;
		
		DSU(int _N){
			N = _N + 1;
			leader.assign(N);
			size.assign(N);
		}
		void newSet(int x){
			leader[x] = x;
			size[x] = 0;
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
				if(size[a] > size[b]) 
					swap(a, b);
				leader[a] = b;
				size[b] += size[a];
			}
		}
		bool alikeLeader(int a, int b){
			return (getLeader(a) == getLeader(b));
		}
};