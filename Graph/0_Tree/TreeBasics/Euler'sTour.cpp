#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5+5;
vector<int> G[mxN];

// Euler Tour Facility
// Flatten stores flattened tree
// Start and End stores starting and Ending index of 'Flatten' respectively
// values from Flatten[Start[i]] to Flatten[End[i]] denotes subtree of node 'i'

vector<int> Flattened;	
int Start[mxN];			  
int End[mxN];			

void EulerTour(int u, int par){
	Flattened.push_back(u);
	Start[u] = Flattened.size() - 1;
	for(int v : G[u]){
		if(v == par){
			continue;
		}
		EulerTour(v,u);
	}
	End[u] = Flattened.size() - 1;
}

int main() {
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	for(int i=1,u,v; i<n; i++){
		cin >> u >> v;
		--u;--v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	EulerTour(0,-1);
	cout << "INDX:\t";for(int i=0; i<n; i++) cout << i << "\t";	cout << "\n";
	cout << "FLAT:\t";for(int z : Flattened) cout << z << "\t"; cout << "\n\n";
	cout << "NODE:\t";for(int i=0; i<n; i++) cout << i << "\t"; cout << "\n";
	cout << "SIDX:\t";for(int i=0; i<n; i++) cout << Start[i] << "\t"; cout << "\n";
	cout << "EIDX:\t";for(int i=0; i<n; i++) cout << End[i] << "\t"; cout << "\n";
}
/*
14
1 2
1 3
1 4
2 5
2 6
3 7 
4 8
4 9
4 10
5 11
5 12
7 13 
7 14
*/
