#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5+5;
vector<int> G[mxN]; 

int p[mxN];
pair<int,int> dfs(int u, int par, int dis = 0){
   p[u] = par;
   pair<int, int> res = {dis,u};
   for(int v : G[u]){
      if(v == par){
         continue;
      }
      res = max(res,dfs(v,u,dis+1));
   }
   return res;
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
   auto endpt1 = dfs(0, -1);
   auto endpt2 = dfs(endpt1.second, -1);
   int node1 = endpt1.second; // end 1 of diam
   int node2 = endpt2.second; // end 2 of diam
   int dimlen = endpt2.first; // length of diam
   // diameter itself
   vector<int> diam;
   int node = node2;
   while(node != node1){
      diam.push_back(node);
      node = p[node];
   }
   diam.push_back(node1);
   for(auto z : diam) cout << z + 1 << " ";
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
