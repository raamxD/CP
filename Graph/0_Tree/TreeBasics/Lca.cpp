#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
const int lgN = 20;
vector<int> Adj[mxN];

////////////////////////////////////////////////////////////////////
/// LCA Calculation

//	Anc[i][j] stores ancestor of Node 'i' at a distance of
// 2^j above it. Anc[i][0] is thereby parent of 'i'
// Know as Binary Lifting or Sparse Table Technique
int Dep[mxN];
int Anc[mxN][lgN];	//memset(Anc,-1,sizeof(Anc));

void dfs(int u, int p=-1){
	Dep[u] = (p != -1 ? 1 + Dep[p] : 0);
	Anc[u][0] = p;
	for(int i = 1; i < lgN; ++i){
		if(Anc[u][i-1] != -1){
			Anc[u][i] = Anc[Anc[u][i-1]][i-1];
		}
	}
   for(int v : Adj[u]){
		if(v != p) dfs(v,u);
   }
}
int getLCA(int u, int v){
	if(Dep[u] < Dep[v]) swap(u,v);
   for(int i = lgN - 1; ~i; --i){
		if(Anc[u][i] + 1 && Dep[Anc[u][i]] >= Dep[v]){
			u = Anc[u][i];
		}
	}
   if(u == v){
		return u;
	}
	for(int i = lgN - 1; ~i; --i){
		if(Anc[u][i] != Anc[v][i]){
			u = Anc[u][i], v = Anc[v][i];
		}
	}
	return Anc[u][0];
}
////////////////////////////////////////////////////////////////////

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n - 1; i++){
		int u,v;
		cin >> u >> v;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	
	memset(Anc,-1,sizeof(Anc));
	dfs(1);
	
	cout << Anc[11][0] << "\n";
	cout << Anc[11][1] << "\n";
	cout << Anc[11][2] << "\n";
	cout << Anc[11][3] << "\n";
	
	cout << getLCA(12,6) << "\n";
	cout << getLCA(13,14) << "\n";
	cout << getLCA(7,3) << "\n";
	cout << getLCA(3,3) << "\n";
	
	return 0;
}

/*

INPUT : 

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

OUTPUT:

5
2
-1
-1
2
7
3
3

*/
