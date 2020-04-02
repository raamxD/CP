using namespace std;
#include "bits/stdc++.h"
#define ll long long

const int mxN = 200005;
vector<int> adj[mxN];

// LexBFS traversal. 
// Traversal is PEO if graph class is Chordal.
vector<int> lexBFS(int n){
   set<pair<int,int>> pq;
   for(int i = 0; i < n; ++i){
      pq.insert({0, i});
   }
   vector<int> seq, label(n,0), used(n,0);
   for(int i = 0; i < n; ++i){
      auto u = pq.rbegin() -> second;
      pq.erase({label[u],u});
      used[u] = 1;
      for(auto v : adj[u]){
         if(used[v]){
            continue;
         }
         pq.erase({label[v], v});
         ++label[v];
         pq.insert({label[v],v});
      }
      seq.push_back(u);
   }
   return seq;
}

// If given sequence is PEO then graph class is Chordal.
bool isChordal(int n, vector<int> &seq){
   vector<set<int>> adjSet(n);
   for(int i = 0; i < n; ++i){
      adjSet[i] = set<int>(begin(adj[i]), end(adj[i]));
   }
   vector<int> pos(n,-1);
   for(int i = 0; i < n; ++i){
      int u = seq[i];
      int closest = u;
      for(auto v : adj[u]){
         if(pos[v] > pos[closest]){
            closest = v;
         }
      }
      for(auto v : adj[u]){
         if(pos[v] != -1 && closest != v && !adjSet[closest].count(v)){
            return 0;
         }
      }
      pos[u] = i;
   }
   return 1;
}

void solve(){
    
   int n,m;
   cin >> n >> m;
   for(int i = 0; i < m; ++i){
      int u,v;
      cin >> u >> v;
      --u; --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }     
   vector<int> seq = lexBFS(n);
   if(!isChordal(n, seq)){
      cout << "Graph isn't Chordal\n";
      return;
   }
   cout << "Graph is Chordal\n";
   cout << "PEO for Graph is : ";
   for(int i : seq) cout << i + 1 << " ";
}

int main(){
       
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   int t; t = 1;
   while(t--)solve();
}
