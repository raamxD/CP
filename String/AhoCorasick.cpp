// Source to Study :    
// https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
// https://cp-algorithms.com/string/aho_corasick.html

/*
      for a node of trie structure,
      *  'parent' stores id of the parent node.
      *  'symbol' stores character required to transition at current node from parent.
      *  'finish' is flag which tells whether pattern ends at current node.
      *  'depth' stores the depth of node of the trie structure.
      *  'suflink' stores the id of node which is longest proper suffix of current pattern.
      *  'outlink' stores the id of node which is longes proper suffix and also has finish = 1.
      *  'nxtNode[i][c]' stores id of child of current node after transition of character 'c' else -1 if no such child. 
      *  'nxtState[i][c]' stores id of node after doing transition on current node with input character 'c'.
      *   Suffix link are also called as failure links and Outer links as dictionary links. 
*/

#include <bits/stdc++.h>
using namespace std;

struct ahoCorasick{

   const static int mxNodes = 1000000;
   const static int mxAlpha = 26;
   int timer = 0;
   
   struct Node{
      int  parent;
      char symbol;
      bool finish = 0;
      int  depth  = 0;
      int  sufLink = -1;
      int  outLink = 0;
      int  nxtNode [mxAlpha];
      int  nxtState[mxAlpha];
      Node(int p = -1, char s = '$') : parent(p), symbol(s){
         memset(nxtNode,  -1, 4 * mxAlpha);
         memset(nxtState, -1, 4 * mxAlpha);
      }
   } node[mxNodes];
   
   void buildTree(vector<string> &S){
      // Process all strings
      for(auto &s : S){
         int ptr = 0;
         for(auto &ch : s){
            int i = ch - 'a';
            if(node[ptr].nxtNode[i] == -1){
               node[ptr].nxtNode[i] = ++timer;
               node[timer] = Node(ptr, ch);
            }
            ptr = node[ptr].nxtNode[i];
         }
         node[ptr].finish = 1;
         node[ptr].outLink = ptr;
      }
      // Base Case
      node[0].sufLink = 0;
      for(int i = 0; i < mxAlpha; ++i){
         node[0].nxtState[i] = 0;
      }
      // Find depth, suffix link, outer link and nxtState for all nodes
      queue<int> Q;   
      Q.push(0);
      while(!Q.empty()){
         int curId = Q.front(); Q.pop();
         Node &cur = node[curId];
         for(int c = 0; c < mxAlpha; ++c){
            if(cur.nxtNode[c] != -1){
               Node &child = node[cur.nxtNode[c]];
               child.depth = 1 + cur.depth;
               child.sufLink = node[cur.sufLink].nxtState[c];
               if(!child.outLink){
                  child.outLink = node[child.sufLink].outLink;
               }
               cur.nxtState[c] = cur.nxtNode[c];
               Q.push(cur.nxtNode[c]);
            }else{
               cur.nxtState[c] = node[cur.sufLink].nxtState[c];
            }
         }
      }
   }
};

int main() {
   
   vector<string> S = {"a", "ab", "bab", "bc", "bca", "c", "caa"};
   // vector<string> S = {"baccad", "accad", "cad", "ad"};
   
   ahoCorasick aC;
   aC.buildTree(S);
   for(int i = 0; i <= 15; ++i){
      cout << "Node " << i << " : ";
      for(int j = 0; j < 26; ++j){
         cout << aC.node[i].nxtState[j] << " ";
      }
      cout << "\tsuf : " << aC.node[i].sufLink << "\n";
   }
   return 0;
}
