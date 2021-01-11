#include <bits/stdc++.h>
using namespace std;

struct DSU{
   int N;
   vector<int> leader;
   vector<int> rank;
   DSU(int _N){
      N = _N + 1;
      leader.resize(N);
      rank.resize(N);
   }
   // Creates a new set with leader as 'x'.
   void newSet(int x){
      leader[x] = x;
      rank[x] = 0;
   };
   // Returns the leader of node 'x'. Uses path-compression optimization.
   int getLeader(int x){
      if(leader[x] == x)
         return x;
      return leader[x] = getLeader(leader[x]);
   }
   // Merge the sets having the node 'a' and 'b' into single set. Uses union by depth optimization.
   void mergeSets(int a, int b){
      a = getLeader(a);
      b = getLeader(b);
      if(a != b){
         if(rank[a] > rank[b]) 
            swap(a, b);
         leader[a] = b;
         if(rank[a] == rank[b])
            ++rank[b];
      }
   }
   // Returns true if the node 'a' and 'b' shares same leader. 
   bool alikeLeader(int a, int b){
      return (getLeader(a) == getLeader(b));
   }
};