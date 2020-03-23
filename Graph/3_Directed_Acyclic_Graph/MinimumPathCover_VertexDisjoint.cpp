/*
    Source to study : 
    
    Aim :   To cover the given Directed Acyclic Graph with minimum possible
            vertex - disjoint paths.
    
    Time Complexity : O(N^2)
*/

using namespace std;
#include<bits/stdc++.h>
#define ll long long

struct minPathCover{
    
    int n; int pcnt;      
    vector<int> *adj;
    vector<int> match;
    vector<bool> used;

    minPathCover(int _n, vector<int> *_adj){
        n = _n;
        pcnt = n;
        adj = _adj;
        used.assign(n,0);
        match.assign(n,-1);
    }
    bool kuhn(int u){
        if(used[u]) return 0;
        used[u] = 1;
        for(auto v : adj[u]){
            if(match[v] < 0 || kuhn(match[v])){
                match[v] = u;
                return 1;
            }
        } return 0;
    }
    vector<vector<int>> getDAGCover(){
        for(int i = 0; i < n; ++i){
            fill(begin(used), end(used), 0);
            pcnt -= kuhn(i);
        }
        vector<int> nxt(n,-1);
        for(int i = 0; i < n; ++i)
            if(match[i] != -1)
                nxt[match[i]] = i;

        vector<vector<int>> Paths;
        for(int i = 0; i < n; ++i){
            if(match[i] == -1){
                vector<int> newPath;
                int cur = i;
                while(cur != -1)
                    newPath.push_back(cur),
                    cur = nxt[cur];
                Paths.push_back(newPath);
            }
        }
        return Paths;
    }
};

int main(){

    int n,m;
    cin >> n >> m;
    vector<int> adj[n];
    for(int i = 0; i < m; ++i){
        int u,v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
    }
    
    minPathCover mpc(n, adj);
    vector<vector<int>> Paths = mpc.getDAGCover();
    
    int cnt = 0;
    cout << "Total Paths : " << mpc.pcnt << "\n";
    for(auto i : Paths){
        cout << "Path " << ++cnt << " : ";
        for(auto j : i)
            cout << j + 1 << " ";
        cout << "\n";
    }
}

/*
7 14
1 4
1 5
1 6
2 1
2 4
2 5
2 6
2 7
3 4
3 5
3 6
3 7
4 5
7 5

*/
