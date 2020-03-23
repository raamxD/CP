/*
    Source to study :   https://beta-community-app.topcoder.com/thrive/articles/Problem%20Solving%20-Solving%20Maximum%20Bipartite%20Matching%20Problem
    Aim : To get maximal bipartite matching.
    Given : Bipartite Graph adj[mxN][mxM]. In adj[i][j] node 'i' belongs to left set and node 'j' represents 
            node in right set which is linked to node 'i'.  
    Time Complexity : O(N * M)
*/

using namespace std;
#include<bits/stdc++.h>
#define ll long long

const int mxN = 100;
const int mxM = 100;

struct maxMatching{

    int n,m;
    int mxCnt = 0;      
    vector<int> *adj;
    vector<int> match;
    vector<bool> used;
    
    maxMatching(int _n, int _m, vector<int> *_adj){
        n = _n; m = _m;
        adj = _adj;
        used.assign(n,0);
        match.assign(m,-1);
    }

    // returns 1, if match for node 'u' from left set exists.
    bool kuhn(int u){
        if(used[u]) return 0;
        used[u] = 1;
        for(auto v : adj[u]){
            if(match[v] < 0 || kuhn(match[v])){
                match[v] = u;
                return 1;
            }
        }
        return 0;
    }
    // res[i] stores match of node 'i' from left set to right.
    // -1 if no match exists.
    vector<int> getConnection(){
        for(int i = 0; i < n; ++i){
            fill(begin(used), end(used), 0);
            mxCnt += kuhn(i);
        }
        vector<int> res(n,-1);
        for(int i = 0; i < m; ++i){
            if(match[i] != -1){
                res[match[i]] = i;
            }
        }
        return res;
    }
};

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; // n = Number of nodes in left side. [1,n]
    int m; // m = Number of nodes in right side.[1,m]
    int e; // e = total number of edges

    cin >> n >> m >> e;

    vector<int> adj[mxN];

    for(int i = 0; i < e; ++i){
        int l, r;
        cin >> l >> r;
        --l; --r;
        adj[l].push_back(r);
    }
    
    maxMatching MBM(n, m, adj);
    vector<int> match = MBM.getConnection();
    
    for(int i = 0; i < n; ++i){
        if(match[i] != -1){
            cout << "Node " << i + 1 << " from left set matches with Node ";
            cout << match[i] + 1 << " from right set\n";
        }else{
            cout << "Node " << i + 1 << " from left set doesn't have any match from right set.\n";
        }
    }
}

/*
    4 6 5
    1 2
    2 2
    3 3
    4 1
    4 3
*/
