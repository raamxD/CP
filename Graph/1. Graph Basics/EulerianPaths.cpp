/*

https://www.youtube.com/watch?v=xR4sGgwtR2I
https://www.youtube.com/watch?v=8MpoO2zA2l4
https://cp-algorithms.com/graph/euler_path.html

Eulerian Path and Eulerian Circuit using HierHolzer's Algorithm

-----------------------------------------------------------------------------------------------------------------

Definitions - 

i) Eulerian Path : An Eulerian path is a path of edges that visit all edges in a graph exactly once.

ii) Eulerian Circuit : An Eulerian circuit is an Eulerian path that starts and ends at the same vertex.
 
Note : Every Euler circuit is an Euler path, but not every Euler path is an Euler circuit.


-----------------------------------------------------------------------------------------------------------------

Conditions - 

 We assume vertices with nonzero degree belong to a single strongly connected component.

 _______________________________________________________________________________________________________________
|  Graph Types  |       Eulerian Circuits               |                Eulerian Path                          |
|_______________|_______________________________________|_______________________________________________________|
|               |                                       |                                                       |
|               | Every vertex should have equal        | Each vertex should have the same in-degree & outdegree|
|   Directed    | in-degree and out-degree edges.       | except for 2 of them.                                 |
|     Graph     |                                       | -One of these vertex will be the start vertex         |
|               |                                       | which has 1 more out-going edge than in-going edges.  |
|               |                                       | -The other one will be the end vertex which has 1     |
|               |                                       | more in-going edge than out-going edges.              |
|_______________|_______________________________________|_______________________________________________________|
|               |                                       |                                                       |
|               | Every vertex should have an           | Each vertex should have an even                       |
|   Undirected  | even degree.                          | degree or only 2 vertices                             | 
|     Graph     |                                       | should have odd degrees.                              |
|_______________|_______________________________________|_______________________________________________________|

*/

// For Directed Graph
// expect nodes to be non negative
struct EulerianPathAndCircuit_DirectedGraph{
    int n;
    bool hasEulerianPath;
    vector<vector<int>> adj;
    vector<int> path, indeg, outdeg;

    EulerianPathAndCircuit_DirectedGraph(vector<vector<int>> _adj){ 
        adj = _adj;
        n = size(adj);
        hasEulerianPath = 1;
        indeg.resize(n), outdeg.resize(n);
        checkIfPathExists();
    }
    void checkIfPathExists(){
        for(int u = 0; u < n; ++u){
            for(auto& v : adj[u]){
                ++outdeg[u];
                ++indeg[v];
            }
        }
        // check if path exists
        int s = -1, e = -1;
        for(int u = 0; u < n && hasEulerianPath; ++u){
            if(abs(indeg[u] - outdeg[u]) > 1) hasEulerianPath = 0;
            else if(outdeg[u] - indeg[u] > 0) {hasEulerianPath &= s == -1; s = u;}
            else if(indeg[u] - outdeg[u] > 0) {hasEulerianPath &= e == -1; e = u;}
        }
        if(hasEulerianPath) dfs(s == -1 ? 0 : s);
        reverse(begin(path), end(path));
    }
    void dfs(int u){
        while(outdeg[u]){
            dfs(adj[u][--outdeg[u]]);
        }
        path.push_back(u);
    }
    vector<int> getEulerianPath(){
        if(path.empty()){
            return {};
        }
        return path;
    }
    vector<int> getEulerianCircuit(){
        if(path[0] != path.back()){
            return {};
        }
        return path;
    }
};


// For Undirected Graph
// expect nodes to be non negative
struct EulerianPathAndCircuit_UndirectedGraph{
    int n;
    bool hasEulerianPath;
    vector<vector<array<int, 2>>> adj;
    vector<int> path, degree, removed_edges;
    
    EulerianPathAndCircuit_UndirectedGraph(int _n, vector<vector<int>> edges){ 
        n = _n;
        adj.resize(n);
        for(int e = 0; e < edges.size(); ++e){
            int u = edges[e][0], v = edges[e][1];
            adj[u].push_back({v, e});
            adj[v].push_back({u, e});
        }
        hasEulerianPath = 1;
        removed_edges.resize(edges.size());
        degree.resize(n);
        checkIfPathExists();
    }
    void checkIfPathExists(){
        for(int u = 0; u < n; ++u){
            for(auto& v : adj[u]){
              ++degree[u];
            }
        }
        // check if path exists
        int s = -1, e = -1;
        for(int u = 0; u < n && hasEulerianPath; ++u){
            if(degree[u] % 2 != 0){
                hasEulerianPath &= (s == -1 || e == -1);
                e == -1 && s != -1 ? e = u : e;
                s == -1 ? s = u : s;
            }
        }
        hasEulerianPath &= (s == -1 && e == -1) || (s != -1 && e != -1);
        if(hasEulerianPath) dfs(s == -1 ? 0 : s);
            reverse(begin(path), end(path));
        }
    void dfs(int u){
        while(degree[u]){
            if(!removed_edges[adj[u][--degree[u]][1]]){
                removed_edges[adj[u][degree[u]][1]] = 1;
                dfs(adj[u][degree[u]][0]);
            }
        }
        path.push_back(u);
    }
    vector<int> getEulerianPath(){
        if(path.empty()){
            return {};
        }
        return path;
    }
    vector<int> getEulerianCircuit(){
        if(path[0] != path.back()){
            return {};
        }
        return path;
    }
};

int main() {
	vector<vector<int>> edges;
	edges.push_back({0, 1});
	edges.push_back({1, 2});
	edges.push_back({0, 2});
	
	EulerianPathAndCircuit_UndirectedGraph e(3, edges);
	vector<int> path = e.getEulerianPath();
	for(auto& p : path) cout << p << ", ";
	return 0;
}
