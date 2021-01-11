struct DSU{
   int N;
   vector<int> leader, rank;
   DSU(int _N){
      N = _N + 1; leader.resize(N); rank.resize(N);
   }
   void newSet(int x){
      leader[x] = x; rank[x] = 0;
   };
   int getLeader(int x){
      return (leader[x] == x? x : leader[x] = getLeader(leader[x]));
   }
   void mergeSets(int a, int b){
      a = getLeader(a); b = getLeader(b);
      if(a != b){
         if(rank[a] > rank[b]) swap(a, b);
         leader[a] = b;
         if(rank[a] == rank[b]) ++rank[b];
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
   vector<edge> spanningEdges;
   MinimumSpanningTree(int _n, vector<edge> _edges){
      n = _n; edges = _edges; cost = 0;
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