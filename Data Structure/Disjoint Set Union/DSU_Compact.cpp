
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

class DisjointUnionSet{
private :
    vector<int> leader, size;
public :
    DisjointUnionSet(int mx) : leader(mx), size(mx, 1){
        iota(begin(leader), end(leader), 0);
    }
    int GetLeader(int a){
        return leader[a] == a ? a : leader[a] = GetLeader(leader[a]);
    }
    void MergeGroups(int a, int b){
        a = GetLeader(a); b = GetLeader(b);
        if(a != b){
            if(size[a] > size[b]) swap(a, b);
            size[b] += size[a];
            leader[a] = b;
        }
    }
    int GetGroupSize(int a){
        return size[GetLeader(a)];
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
