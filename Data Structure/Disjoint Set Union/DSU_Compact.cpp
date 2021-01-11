
// Uses union by size optimization
struct DSU{
   int N;
   vector<int> leader, size;
   DSU(int _N){
      N = _N + 1; leader.resize(N); size.resize(N);
   }
   void newSet(int x){
      leader[x] = x; size[x] = 0;
   };
   int getLeader(int x){
      return (leader[x] == x? x : leader[x] = getLeader(leader[x]));
   }
   void mergeSets(int a, int b){
      a = getLeader(a); b = getLeader(b);
      if(a != b){
        if(size[a] > size[b]) swap(a, b);
         leader[a] = b; size[b] += size[a];
      }
   }
   bool alikeLeader(int a, int b){
      return (getLeader(a) == getLeader(b));
   }
};
//////////////////////////////////////////////////////////////////////////////////////////////

// Uses union by depth optimization
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


//////////////////////////////////////////////////////////////////////////////////////////////