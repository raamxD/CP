#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5+5;
const int lgN = 20;
vector<int> Adj[mxN];

//////////////////////////////////////////////////////////////////
/// LCA Calculation 

int Dep[mxN];
int Anc[mxN][lgN];	//memset(Anc,-1,sizeof(Anc));

void dfs(int u, int p=-1){
	Dep[u] = (p!=-1? 1+Dep[p]:0);
	Anc[u][0] = p;
	for(int i=0; i<lgN; ++i)
        if(Anc[u][i-1]!=-1)
            Anc[u][i] = Anc[Anc[u][i-1]][i-1];
    for(int v:Adj[u]){
    	if(v!=p) dfs(v,u);
    }
}
int getLCA(int u, int v){
	if(Dep[u] < Dep[v]) swap(u,v);
    for(int i=lgN-1; i>=0; --i)
        if(Anc[u][i]+1 && Dep[Anc[u][i]]>=Dep[v])
            u = Anc[u][i];
    if(u==v) return u;
    for(int i=lgN-1; i>=0; --i)
        if(Anc[u][i]!=Anc[v][i])
            u=Anc[u][i], v=Anc[v][i];
    return Anc[u][0];
}

//////////////////////////////////////////////////////////////////
/// Returns K'th Ancestor of node if present else -1 

int getKthAnc(int u, int k){
	for(int i=0; i<lgN; ++i){
		if((1<<i)&k){
			u = Anc[u][i];
			if(u==-1)
				break;
		}
	}
	return u;
}

//////////////////////////////////////////////////////////////////
/// Get Distance b/w 2 nodes (i.e # of edges)

int getDist(int u, int v){
	int l = getLCA(u,v);
	return (Dep[u]+Dep[v]-2*Dep[l]);
}

//////////////////////////////////////////////////////////////////

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n-1; i++){
		int u,v;
		cin >> u >> v;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	
	memset(Anc,-1,sizeof(Anc));
	dfs(1);
	
	cout << getKthAnc(11,1) << "\n";
	cout << getKthAnc(11,2) << "\n";
	cout << getKthAnc(11,3) << "\n";
	cout << getKthAnc(11,4) << "\n";
	
	cout << getDist(11,14) << "\n";
	cout << getDist(1,7) << "\n";
	cout << getDist(9,8) << "\n";
	cout << getDist(5,13) << "\n";
	cout << getDist(7,7) << "\n";
	
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

OUTPUT :

5
2
1
-1
6
2
2
5
0

*/