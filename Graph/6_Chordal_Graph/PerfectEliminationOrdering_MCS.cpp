//https://www.codechef.com/MARCH20A/problems/EGGFREE
//https://www.codechef.com/viewsolution/30527284
//https://www.codechef.com/viewsolution/30327565

using namespace std;
#include<bits/stdc++.h>
#define ll long long

cons

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

