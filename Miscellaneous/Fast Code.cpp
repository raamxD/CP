// 1) Looking for 'target' in a sorted array.
int f() {
    int left = 0, right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(a[mid] == target) {
            return mid;
        }
        else if(a[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

// 2) Looking for the index of the first element that satisfies some property.
// F F T T T T <- find first index that has TRUE
int f() {
    int left = 0, right = n - 1; // add +1 to 'right' if the answer can be outside [left, right]
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(property(mid)) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SieveOfEratosthenes{
  private:
    vector<bool> prime;
    vector<int> spf;
  public:
    SieveOfEratosthenes(int mx) : prime(mx), spf(mx){
      fill(begin(prime), end(prime), true);
      iota(begin(spf), end(spf), 0);
      SieveNonPrimes();
    }
    void SieveNonPrimes(){
      for(int i = 2; i * i < size(prime); ++i){
        if(prime[i]){
          spf[i] = i;
          for(int j = i * i; j < size(prime); j += i){
            if (spf[j] > i) spf[j] = i;
            prime[j] = false; 
          }
        }
      }
    }
    vector<array<int, 2>> GetPrimeFactorisation(int num){
      assert(num < size(prime) && num > 1);
      vector<array<int, 2>> result;
      while(num != 1){
        int x = GetSmallestPrimeFactor(num);
        result.push_back({x, 0});
        while(num % x == 0){
          result.back()[1]++;
          num /= x;
        }
      }
      return result;
    }
    bool IsPrime(int num){
      return num > 1 && prime[num];
    }
    int GetSmallestPrimeFactor(int num){
      assert(num < size(prime) && num > 1);
      return spf[num];
    }
};

class SieveOfEratosthenes{
	private : 
	  vector<int> spf;
	public :
	  SieveOfEratosthenes(int n) : spf(n){
		iota(begin(spf), end(spf), 0);
		SieveNonPrimes();
	  }
	  void SieveNonPrimes(){
		int n = size(spf);
		for(int i = 2; i * i < n; ++i){
		  if(spf[i] == i){
			for(int j = i * i; j < n; j += i){
			  if(spf[j] > i) spf[j] = i;
			}
		  }
		}
	  }
	  bool isPrime(int x){
		return x > 1 && spf[x] == x;
	  }
	  vector<array<int,2>> GetPrimeFactorisation(int x){
		vector<array<int, 2>> result;
		while(x > 1){
		  int y = spf[x];
		  result.push_back({y, 0});
		  while(x % y == 0){
			result.back()[1]++;
			x /= y;
		  }
		}
		return result;
	  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// getting divisors for a given integer in O(sqrt(n))
vector<int> GetDivisors(int n){
  vector<int> divisors;
  for(int i = 1; i * i <= n; ++i){
	if(n % i == 0){
	  divisors.push_back(i);
	  if(i * i != n) divisors.push_back(n / i);
	}
  }
  return divisors;
}

// storing divisors for each integer in [1..n] in O(nlogn)
const int n = 1000000;
vector<vector<int>> divisors(n + 1);
for (int i = 1; i <= n; i++) {
  for (int j = i; j <= n; j += i) {
    divisors[j].push_back(i);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// modpow : calculate (a ^ b) under mod in O(log b)
int modpow(int a, int b, int mod){
	int res = 1;
	while(b > 0){
		if(b & 1){
			res = (res * a) % mod;
		}
		res = (res * res) % mod;
		b /= 2;
	}
	return res;
}

// modinv : calculates (1 / a) under mod in O(log mod)
// works iff mod is a prime number and a < mod
int modinv(int a, int mod){
	return modpow(a, mod - 2, mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Combinatorics{
private:
	const int mod = 1e9 + 7;
	vector<unsigned long long> fact, ifact;
	
public:
	Combinatorics(int n) : fact(n + 1), ifact(n + 1){
		preprocess(n);
	}
	void preprocess(int n){
		fact[0] = 1;
		for(int i = 1; i <= n; ++i){
			fact[i] = (i * fact[i - 1]) % mod;
		}
		ifact[n] = modinv(fact[n]);
		for(int i = n - 1; i >= 0; --i){
			ifact[i] = ((i + 1)  * ifact[i + 1]) % mod;
		}
	}
	int modpow(long long a, int b){
		unsigned long long res = 1;
		while(b > 0){
			if(b & 1){
				res = (res * a) % mod;
			}
			a = (a * a) % mod;
			b >>= 1;
		}
		return res;
	}
	int modinv(int a){
		return modpow(a, mod - 2);
	}
	int nCr(int n, int r){
		if(n < r){
			return 0;
		}
		return ((fact[n] * ifact[n - r]) % mod * ifact[r]) % mod;
	}
	int nPr(int n, int r){
		if(n < r){
			return 0;
		}
		return (fact[n] * ifact[n - r]) % mod;
	}
};

vector<vector<int>> nCr(N + 1, vector<int>(N + 1));
for(int i = 0; i <= N; ++i){
	for(int j = 0; j <= i; ++j){
		nCr[i][j] = (j == 0 ? 1 : i > 0 ? (nCr[i - 1][j] + nCr[i - 1][j - 1]) : 0);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StringHash{

// (s, p, m)   =   (s[0] * p^0 + s[1] * p^1 + s[2] * p^2 +...+ s[len(s)-1] * p^(len(s) - 1)) % m
		
	const int p = 31;
	const int m = 1000000007;
	vector<long long> pexp;

	StringHash(int mxN){
		pexp.assign(mxN,1);
		prefHash.assign(mxN,0);
		for(int i = 1; i < mxN; ++i){
			pexp[i] = (pexp[i - 1] * p) % m;
		}
	}
	long long hashVal(string const &s){
		int res = 0;
		int idx = 0;
		for(auto i : s){
			res += ((i - 'a' + 1) * pexp[idx]) % m;
			++idx;
		}
		return res;
	}
};

// Type 1 : Need some work to get hash of any substring but can compare 2 substring in O(1)

class Compare2SubstringUsingHash{

// Type 1 : (s, p, mod)   =   (s[0] * p^0 + s[1] * p^1 + s[2] * p^2 +...+ s[len(s)-1] * p^(len(s) - 1)) % mod

	const int p = 31;
	const int mod = 1000000007;
	string s;
	vector<long long> pexp;
	vector<long long> prefhash;
	
	public :
	
	Compare2SubstringUsingHash(int mxN, string& _s){
		pexp.assign(mxN,1);
		prefhash.assign(mxN,0);
		s = _s;
		for(int i = 1; i < mxN; ++i){
			pexp[i] = (pexp[i - 1] * p) % mod;
		}
		preprocess();
	}
	void preprocess(){
		long long res = 0;
		int idx = 0;
		for(auto i : s){
			res += ((i - 'a' + 1) * pexp[idx]) % mod;
			res %= mod;
			prefhash[idx] = res;
			++idx;
		}
	}
	bool isEqual(int l1, int r1, int l2, int r2){
		if(r1 - l1 != r2 - l2){
			return false;
		}
		if(l2 < l1){
			swap(l1, l2); 
			swap(r1, r2);
		}
		long long h1 = (l1 == 0 ? prefhash[r1] : (prefhash[r1] - prefhash[l1 - 1] + mod) % mod);
		long long h2 = (l2 == 0 ? prefhash[r2] : (prefhash[r2] - prefhash[l2 - 1] + mod) % mod);
		return ((h1 * pexp[l2 - l1]) % mod == h2);
	} 
};

// Type 2 : Has advantage to get hash of any substring in O(1);

class GetSubStringHash{

// Type 2 : (s, p, mod)   =   (s[0] * p^(len(s) - 1) + s[1] * p^(len(s) - 3) + s[2] * p^(len(s) - 3) +...+ s[len(s)-1] * p^0) % mod

	const int p = 31;
	const int mod = 1000000007;
	string s;
    int n;
	vector<long long> pexp;
	vector<long long> prefhash;
	
	public :
	
	GetSubStringHash(string& _s){
		s = _s;
        n = size(s);
        pexp.resize(n);
		prefhash.resize(n);
		preprocess();
	}
	void preprocess(){
        pexp[0] = 1;
        prefhash[0] = (s[0] - 'a' + 1);
        for(int i = 1; i < n; ++i){
            prefhash[i] = (prefhash[i - 1] * p + (s[i] - 'a' + 1)) % mod;
			pexp[i] = (pexp[i - 1] * p) % mod;
		}
	}
	int getHash(int l, int r){
		return (l > 0 ? (prefhash[r] - (prefhash[l - 1] * pexp[r - l + 1]) % mod + mod) % mod : prefhash[r]);
	} 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExpressionTreeNode{
public :    
    char data;
    int value;
    ExpressionTreeNode* lhs;
    ExpressionTreeNode* rhs;
    
    ExpressionTreeNode(){}
    ExpressionTreeNode(char data, int value, ExpressionTreeNode* lhs, ExpressionTreeNode* rhs) : data(data), value(value), lhs(lhs), rhs(rhs) {};
    
    /* builds expression tree from infix notation */
    ExpressionTreeNode* BuildExpressionTree(string& expression){
        stack<ExpressionTreeNode*> stk; // to store actual nodes
        stack<char> ops;                // to store operators for calculation order
        
        for(int i = 0; i < size(expression); ++i){
            
            char token = expression[i];
            
            /* opening brace */
            if(token == '('){
                ops.push(token);
            }
            
            /* operands */
            if(IsDigit(token)){
                int number = 0;
                while(i < size(expression) && IsDigit(expression[i])){
                    number = number * 10 + (expression[i] - '0');
                    i++;
                }
                --i;
                stk.push(new ExpressionTreeNode('#', number, nullptr, nullptr));
            }
            
            /* operators */
            if(IsOperator(token)){
                char curtoken = token;
                while(!ops.empty() && ops.top() != '(' && OperatorPriority(ops.top()) >= OperatorPriority(curtoken)){
                    ProcessNode(stk, ops.top()); 
                    ops.pop();
                }
                ops.push(curtoken);
            }
            
            /* closing brace */
            if(token == ')'){
                while(ops.top() != '('){
                    ProcessNode(stk, ops.top());
                    ops.pop();
                }
                ops.pop();
            }
        }
        
        /* process remaining if not already processed */
        while(!ops.empty()){
            ProcessNode(stk, ops.top());
            ops.pop();
        }
        
        /* only root is remaining in stk now */ 
        ExpressionTreeNode* root;
        root = stk.top();
        stk.pop();
        return root;
    }
    
    void ProcessNode(stack<ExpressionTreeNode*>& stk, char op){
        ExpressionTreeNode* rhs = stk.top(); stk.pop();
        ExpressionTreeNode* lhs = stk.top(); stk.pop();
        ExpressionTreeNode* par = new ExpressionTreeNode(op, -1, lhs, rhs);
        stk.push(par);
    }
    
    int OperatorPriority(char& token){
        switch(token){
            case '+' : return 1; 
            case '-' : return 1;
            case '*' : return 2;
            case '/' : return 2; 
        }
        return -1;
    }
    
    bool IsOperator(char& token){
        return (token == '+' || token == '-' || token == '*' || token == '/');
    }
    
    bool IsDigit(char& token){
        return (token >= '0' && token <= '9');
    }
};

int dfs(ExpressionTreeNode* node){
    if(node -> data == '#'){
        return node -> value;
    }
    int lhs = dfs(node -> lhs);
    int rhs = dfs(node -> rhs);
    switch(node -> data){
        case '+' : node -> value = lhs + rhs; break; 
        case '-' : node -> value = lhs - rhs; break;
        case '*' : node -> value = lhs * rhs; break;
        case '/' : node -> value = lhs / rhs; break;
    }
    return node -> value;
}

int calculate(string s) {
	  ExpressionTreeNode* root = new ExpressionTreeNode();
	  root = root -> BuildExpressionTree(s);
	  return dfs(root);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Basic Calculator III

class Solution {
public:
    void process(stack<int>& stk, int num, char op){
        int x;
        switch(op){
            case '+' :  stk.push(num); break;
            case '-' :  stk.push(-num); break;
            case '*' :  x = stk.top(); stk.pop(); stk.push(x * num); break;
            case '/' :  x = stk.top(); stk.pop(); stk.push(x / num); break;
        }
    }
    int solve(string& s, int& i){
        stack<int> stk;
        int num = 0;
        char last_operator = '+';
        while(i < s.size()){
            if(s[i] == ' '){
                i++;
                continue;
            }
            if(s[i] == '('){
                i++;
                num = solve(s, i);
                continue;
            }
            if(s[i] == ')'){
                i++;
                break;
            }
            if(isdigit(s[i])){
                // handle digits
                num *= 10;
                num += s[i] - '0';
            }
            else{
                // handle operators +,-,*,/
                process(stk, num, last_operator);
                last_operator = s[i];
                num = 0;
            }
            i++;
        }
        process(stk, num, last_operator);
        int res = 0;
        while(!stk.empty()){
            res += stk.top();
            stk.pop();
        }
        return res;
    }
    int calculate(string s) {
        int i = 0;
        return solve(s, i);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Accessing the i'th digit (0-based lsb) of any number in base X. (Quite Useful Trick for Base-X Bitmasks)*/

	int digit = (num % pow[i + 1]) / pow[i]; where pow[i] = X ^ i

/* For example : Get 2nd digit of Base-10 number num = 2406137 
	(2406137 % 10^3) / 10^2 = 1; */
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Longest Prefix also Suffix
vector<int> computeLPS(const string& str) { 
	  int n = str.size();
	  vector<int> lps = vector<int>(n);
	  for (int i = 1, j = 0; i < n; i++) {
			while (j > 0 && str[i] != str[j]) j = lps[j - 1];
			if (str[i] == str[j]) lps[i] = ++j;
	  }
	  return lps;
 }
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finding a valid topological ordering + checking if cycle is present in Directed Graph using BFS

	queue<int> q;
	for(int i = 0; i < n; ++i){
		if(!inorder[i]){
			 q.push(i);
		}
	}
	int viscount = 0;
	vector<int> ordering;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		ordering.push_back(u);
		++viscount;
		for(auto& v : graph[u]){
			 if(--inorder[v] == 0){
				  q.push(v);
			 }
		}
	}
	return (viscount == n ? ordering : "Cyclic");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Custom Compartor for Priority Queue 

struct node{
        int score;
        string name;
    };
    struct min_cmp{
        bool operator()(const node& a, const node& b){
            if(a.score == b.score){
                return a.name < b.name;
            }
            return a.score > b.score;
        }
    };
    struct max_cmp{
        bool operator()(const node& a, const node& b){
            if(a.score == b.score){
                return a.name > b.name;
            }
            return a.score < b.score;
        }
    };

    priority_queue<node, vector<node>, min_cmp> min_pq;
    priority_queue<node, vector<node>, max_cmp> max_pq;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

Euler Path and Euler Cycle in graphs : 

Eulerian Path/Walk is a path in a graph that visits every edge exactly once.
-- Condition For Eulerian Path : A Eulerian Path exist in graph iff 
							a) All the vertices in the graph have even degree.
							b) Exactly two vertices have odd degree. (which will become ends of the path)

Eulerian Cycle/Circuit is an Eulerian Path which starts and ends on the same vertex. 
-- Condition For Eulerian Cycle : A Eulerian Cycle exist in graph iff
							a) All the vertices in the graph have even degree.

*/

// If a graph has Eulerian Path, we can use dfs to find the path in O(V + E)
// we can make dfs call using any one end of path if eulerian path exist or any vertex if eulerian cycle exist.

void dfs(string u, vector<vector<int>>& adj){
    while(!adj[u].empty()){
        string v = adj[u].back();	// store next node of edge
        adj[u].pop_back();				// delete edge because we won't be using it anymore
        dfs(v, adj);						// make dfs from next node
    }
    path.push_back(u);					// push node into path if all edges for node are processed
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Getting Convex Hull For Given Set of Points
// reference : https://iq.opengenus.org/monotone-chain-algorithm/

class Solution {
public:
    // returns value for direction of point 'c' w.r.t line ab using cross product
    // value = 0 means point 'c' lies on line ab
    // value > 0 means point 'c' lies to the right of line ab (anti-clockwise direction from b to c)
    // value < 0 means point 'c' lies to the left of line ab (clockwise direction from b to c)
    int orientation(vector<int>& a, vector<int>& b, vector<int>& c){
        return ((b[0] - a[0]) * (c[1] - a[1])) - ((b[1] - a[1]) * (c[0] - a[0]));
    }
    bool isAnticlockwise(vector<int>& a, vector<int>& b, vector<int>& c){
        return orientation(a, b, c) < 0;
    }
    
    // getting the convex hull for set of points
    vector<vector<int>> getConvexHull(vector<vector<int>>& trees) {
        int n = size(trees);
        
        // base condition
        if(n <= 3){
            return trees;
        }
        
        // sort points based on x coordinates
        sort(begin(trees), end(trees));
        
        // getting lower hull for all points
        vector<vector<int>> lowerHull;
        for(int i = 0; i < n; ++i){
            while(size(lowerHull) > 1 && isAnticlockwise(lowerHull[size(lowerHull) - 2], lowerHull.back(), trees[i])){
                lowerHull.pop_back();
            }
            lowerHull.push_back(trees[i]);
        }
        
        // getting upper hull for all points
        vector<vector<int>> upperHull;
        for(int i = n - 1; i >= 0; --i){
            while(size(upperHull) > 1 && isAnticlockwise(upperHull[size(upperHull) - 2], upperHull.back(), trees[i])){
                upperHull.pop_back();
            }
            upperHull.push_back(trees[i]);
        }
        
        // combine lower hull and upper hull to get the convex hull
        vector<vector<int>> convexHull;
        convexHull.insert(end(convexHull), begin(lowerHull), end(lowerHull));
        convexHull.insert(end(convexHull), begin(upperHull), end(upperHull));
        
        // remove the duplicates
        sort(begin(convexHull), end(convexHull));
        convexHull.erase(unique(begin(convexHull), end(convexHull)), end(convexHull));
        
        return convexHull;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
