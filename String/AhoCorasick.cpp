// Source to Study : 	
// https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
//	https://cp-algorithms.com/string/aho_corasick.html

/*
		for a node of trie structure,
	
		*  nxtNode stores ID of it's 26 children, else -1 if child doesn't exist.
      *  sufLink stores ID of longest proper suffix of string formed by chars from root to this node.
		*  nxtState stores ID of longest proper suffix of (string + one of 26 chars).
		*  par stores ID of parent of node
		*  chr stores transition character from parent to node.
      *  isEnd stores bool value if patter ends at this node.
*/

#include <bits/stdc++.h>
using namespace std;

struct ahoCorasick{
	
	const static int mxNodes = 1000;
	const static int mxAlpha = 26;
	int timer = 0;
	
	struct Node{
		int nxtNode[mxAlpha];
		int nxtState[mxAlpha];
		int sufLink = -1;
		int  par;
		char chr;
		bool isEnd = 0;
		Node(int par = -1, char chr = '$') : par(par), chr(chr){
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
			node[ptr].isEnd = 1;
		}
		// Join longest proper suffix links for all nodes.
		// Base Case
		node[0].sufLink = 0;
		for(int i = 0; i < mxAlpha; ++i){
			node[0].nxtState[i] = 0;
		}
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()){
			int curId = Q.front();
			Q.pop();
			Node &cur = node[curId];
			for(int c = 0; c < mxAlpha; ++c){
				if(cur.nxtNode[c] != -1){
					Node &child = node[cur.nxtNode[c]];
					child.sufLink = node[cur.sufLink].nxtState[c];
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
