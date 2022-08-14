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
      assert(num < size(prime) && num > 1);
      return prime[num];
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
		return spf[x] == x;
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
