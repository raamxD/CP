/* 
   Source to study : https://cp-algorithms.com/graph/finding-cycle.html
    
   Aim   :  To check if given undirected graph contains cycle.
            
   Time Complexity   :  O(V + E)
   
*/

#include <bits/stdc++.h>
using namespace std;

struct cycleChecker{
   
   enum color {white, gray, black};
   
   int n;
   vector<int> *adj;
   vector<int> par;
   vector<int> cycle;
   vector<color> nodeColor;
   
   cycleChecker(int _n, vector<int> *_adj){
      n = _n;
      adj = _adj;
      par.assign(n, -1);
      nodeColor.assign(n, white);
   }
   bool dfs(int node, int p){
      nodeColor[node] = gray;
      for(int &v : adj[node]){
         if(v == p) continue;
         if(nodeColor[v] == white){
            par[v] = node;
            if(dfs(v, par[v])){
               return true;
            }
         }else
         if(nodeColor[v] == gray){
            // cycle found
            int Beg = v;
            int End = node;
            cycle.push_back(Beg);
            for(int i = End; i != Beg; i = par[i]){
               cycle.push_back(i);
            }
            cycle.push_back(Beg);
            reverse(begin(cycle), end(cycle));
            return true;
         }
      }
      nodeColor[node] = black;
      return false;
   }
   // return bool value as true for cyclic graph
   bool isCyclic(){
      for(int i = 0; i < n; ++i){
         if(nodeColor[i] == white && dfs(i, par[i])){
            return true;
         }
      }
      return false;
   }
   // graph needs to be cyclic else returns empty vector.
   vector<int> getCycle(){
      return cycle;
   }
};

int main() {
   int n, m;
   cin >> n >> m;
   vector<int> adj[n];
   for(int i = 0; i < m; ++i){
      int u, v;
      cin >> u >> v;
      --u; --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   cycleChecker C(n, adj);
   if(C.isCyclic()){
      vector<int> c = C.getCycle();
      cout << "Given graph contains cycle.\n";
      cout << "cycle : ";
      for(auto &i : c){
         cout << i + 1 << " ";
      }
   }else{
      cout << "Given graph is an Acyclic Graph !!";
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

Given graph contains cycle.
cycle : 1 2 3 4 5 6 1 

INPUT :

3 3
1 2
1 3
2 3

OUTPUT :

Given graph contains cycle.
cycle : 1 2 3 1 

INPUT : 

4 3
1 2
1 3
3 4

OUTPUT :

Given graph is an Acyclic Graph !!

*/
