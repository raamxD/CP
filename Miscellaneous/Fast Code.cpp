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
/// Longest Increasing Subsequence (Not Tested)

// for a given vector<int> a : 

// a) finding lis length
vector<int> res
res.push_back(a[0]);
for(int i = 1; i < n; ++i){
	if(res.back() < a[i])
		res.push_back(a[i]);
	else
		*lower_bound(begin(res), end(res), a[i]) = a[i];

}
cout << "Length of LIS of given array : " << size(res) << "\n";


// b) finding lis 
vector<array<int, 2>> v;
vector<int> p(n, -1);
for(int i = 0; i < n; ++i){
	array<int, 2> key = {a[i], -1};
	int j = upper_bound(begin(v), end(v), key) - begin(v);
	if(j == size(v))
		v.push_back({a[i], i});
	else
		v[j] = {a[i], i};
	p[i] = (j - 1 >= 0 ? v[j - 1][1]: -1);
}
vector<int> res;
int cur = v.back()[1];
while(cur != -1){
	res.push_back(a[cur]);
	cur = p[cur];
}
reverse(begin(res), end(res));
cout << "LIS of given array : "; for(auto& i : res) cout << i << " "; cout << "\n";    	
	
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
long long modpow(long long a, int b){
	int res = 1;
	while(b > 0){
		if(b & 1){
			res = (res * a) % mod;
		}
		a = (a * a) % mod;
		b /= 2;
	}
	return res;
}

// modinv : calculates (1 / a) under mod in O(log mod)
// works iff mod is a prime number and a < mod
int modinv(int a, int mod){
	return modpow(a, mod - 2, mod);
}

// shorter version I guess?
long long modpow(long long a, int b){
	  long long res = 1;
	  for(; b; b >>= 1, a = (a * a) % mod)
			if(b & 1) res = (res * a) % mod;
	  return res;
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Euclidean Algorithm for GCD
// src : https://cp-algorithms.com/algebra/euclid-algorithm.html

/* 

Originally, the Euclidean algorithm was formulated as : subtract the smaller number from the larger one until one of the numbers is zero. 
Indeed, if 'g' divides 'a' and 'b', it also divides 'a-b'. On the other hand, if 'g'  divides 'a-b' and 'b', then it also divides 'a = b + (a-b)', 
which means that the sets of the common divisors of {a, b} and {b,a-b} coincide. 
Note that 'a' remains the larger number until 'b' is subtracted from it at least floor(a / b) times. 
Therefore, to speed things up, we can use modulo operation.  Then the algorithm is formulated in an extremely simple way:

				  gcd(a, b) = 	{	a 						if(b == 0)
									{	gcd(b, a % b) 		otherwise.
*/

// recursive 1
int gcd (int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd (b, a % b);
}

// recursive short
int gcd (int a, int b) {
    return b ? gcd (b, a % b) : a;
}

// iterative
int gcd (int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm 
// src : https://cp-algorithms.com/algebra/extended-euclid-algorithm.html

// Diofant

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
// Useful combinatorics calculations

// Identical Objects into Identical Bins
// ref : https://brilliant.org/wiki/identical-objects-into-identical-bins/

Case 1 : We have 'n' objects and we can have any number of bins but each bin should have atleast 1 object
	This problem is same as Integer Partitioning Problem.
	Let p(n, mx) be ways to partition an integer 'n' such that maximum part size is at most 'mx'
	Then, 
		p(n, mx) = p(n - mx, mx) + p(n, mx - 1)
	Using that, 
	p(n, n) represents total ways to partition integer 'n' or ways to distribute 'n' objects in bins.

Case 2 : We have 'n' objects and we have fixed 'r' number of bins
	Let us define dp(n, r) as ways to distribute 'n' objects into at most 'r' number of bins
	Then,
		dp(n, r) = dp(n - r, r) + dp(n, r - 1)
	Why? 
		because, dp(n - r, r) are the ways where every bin has atlest one object 
		and dp(n, r - 1) are the ways where we have some bins which are empty
	From above, we can say that p(n, k) = dp(n, k).
	i.e  The number of partitions of an integer n into r parts is the same as the number of partitions of n for which the largest part is r.
	
// Code : NOT_TESTED 

const int n = 1005;
const int r = 1005;

// dp[i][j] = ways to distribute 'i' identical objects into 'j' identical bins

vector<vector<long long>> dp(n + 1, vector<long long>(r + 1, 0));
for(int i = 0; i <= n; ++i){
    for(int j = 1; j <= r; ++j){
        if(i == 0){
            dp[i][j] = 1;
            continue;
        }
        if(i - j >= 0){
            dp[i][j] = dp[i - j][j];
        }
        dp[i][j] += dp[i][j - 1];
    }
}
return dp[n][r];

-----------------------------------------------------------------------------------------------------------------------------------------------

// Identical Objects into Distinct Bins
// ref : https://brilliant.org/wiki/identical-objects-into-distinct-bins/

Case 1 : We have 'n' objects and 'r' bins where bins can be empty
	
	-Theorem : 	Suppose there are 'n' identical objects to be distributed among 'r' distinct bins. 
				This can be done in precisely nCr(n + r - 1, r - 1) ways.
				
	-Proof : Modeled as stars and bars, there are n stars in a line and r − 1 bars that divide them into distinct groups. 
				There are a total of n+r−1 things that will be placed, and r−1 of those placements are chosen for the bars. 
				The stars will be put in the remaining placements. Thus, there are n + r − 1 possible placements of the bars. 
				Equivalently, there are nCr(n + r − 1, r - 1) possible distributions of n identical objects among r distinct bins.
	
	hence, dp[n][r] = nCr(n + r - 1, r - 1)

Case 2 : We have 'n' objects and 'r' bins where bins cannot be empty
	
	-Theorem : 	Suppose there are n identical objects to be distributed among r distinct non-empty bins, with n≥r. 
				This can be done in precisely nCr(n - 1, r - 1) ways.
				
	-Proof : 	For this type of problem n≥r must be true. If n<r, then there are not enough objects to fill each of the bins with at least one object.
				Modeled as stars and bars, there are n stars and r−1 bars to place. In order for the groups to be non-empty, 
				the bars can only be placed between the stars, and only one bar can be placed between a pair of stars. 
				Thus, there are n−1 possible placements for the bars. Out of those n−1 possible placements, r−1 are chosen for the bars. 
				Hence, the number of possible arrangements of stars and bars is nCr(n - 1, r - 1).
				Equivalently, there are nCr(n - 1, r - 1) distributions of n identical objects into r distinct non-empty bins.

	hence, dp[n][r] = nCr(n - 1, r - 1)
	
-----------------------------------------------------------------------------------------------------------------------------------------------

// Distinct Objects into Identical Bins
// ref : https://brilliant.org/wiki/distinct-objects-into-identical-bins/
// ref : https://codeforces.com/blog/entry/117906
// ref : https://en.wikipedia.org/wiki/Bijection,_injection_and_surjection

Case 1 : We have 'n' objects and 'k' bins where bins cannot be empty
	The Stirling number of 2nd kind, S(n, k) is the number of ways to partition a set of n objects into k groups.
	We'll look into two ways to find stirling numbers.
	
	a) Recurrence Relation : S(n, k) = k * S(n - 1, k) + S(n - 1, k - 1) where 1 <= k <= n
	
	Let us now show that the recurrence formula follows from the enumerative definition. 
	Division of n objects into k groups can be achieved by only one of two basic maneuvers: 
		We could partition the first n-1 objects into k groups, and then add object a 'n' into one of those groups. There are k * S(n-1,k) ways to do this. 
		We could partition the first n-1 objects into k-1 groups and then add object a 'n' as a new, 1 element group. This gives an additional S(n-1,k-1) ways to create the desired partition.
		
	Code : 
	
		const int mod = 1e9 + 7;

		// Function to calculate the Stirling numbers using DP tabulation
		vector<vector<long long>> stirling_second;
		void fillStirlingSecondKind(int N, int K){
			assert(K <= N);
			stirling_second.resize(N + 1, vector<long long>(K + 1)); 
			// Fill in the base cases
			stirling_second[0][0] = 1;
			// dp(n, k) = dp(n - 1, k - 1) + k * dp(n - 1, k) where 1 <= k <= n
			for(int i = 1; i <= N; ++i){
				for(int j = 1; j <= i; ++j){
					stirling_second[i][j] = (stirling_second[i - 1][j - 1] + (stirling_second[i - 1][j] * j) % mod) % mod;
				}
			}
		}
		
	b) Inclusion-exclusion : 
		A -> B onto function which means every element in 'B' has a pre-image in 'A'.
		Lets say, A has 'n' points and B has 'k' points

		Total number of functions from A -> B is cleary k ^ n; For each element in 'A' we have k choices to map.
		To count the number of onto functions we can now use inclusion exclusion principal by substracting those
		functions in which exactly 1, 2, 3. . .  elements of 'B' were not mapped.

		Total number of functions where at least 1 element in 'B' is not mapped = kC1 * [(k - 1) ^ n]
		Why, ways to select that unmapped element = kC1 and ways to map remaining elements = (k - 1) ^ n
		Similarly,
		Total number of functions where at least 2 element in 'B' is not mapped = kC2 * [(k - 2) ^ n]
		Total number of functions where at least 3 element in 'B' is not mapped = kC3 * [(k - 3) ^ n]
		..
		..
		..
		Total number of functions where at least k element in 'B' is not mapped = kCk * [(k - k) ^ n]

		On using inclusion - exclusion principal, 

		Onto(n, k) = (k ^ n) - [kC1*(k-1)^n] + [kc2*(k-2)^n] - [kc3*(k-3)^n] + .. . ..[kCk*(k-k)^n]

		Now we have calculated no. of onto functions, we can go back to our original problem of stirling numbers of second kind. 
		So that problem is exactly same as this onto problem, except that here we are distinguishing k subsets also, 
		but in our original problem, k subsets were identical, so we divide whole thing we derived by k!, 
		so our final formula for S(n,k) becomes

		S(n, k) = Onto(n, k) / k!
				= [(k ^ n) - [kC1*(k-1)^n] + [kc2*(k-2)^n] - [kc3*(k-3)^n] + .. . ..[kCk*(k-k)^n]] / k!
			
		Note : A row of Stirling number can be calulated in O(nlogn) time complexity using polynomial multiplication
			   C(x) = A(x) * B(x), where 
				+-----------------------------------+
				|			n						         |
				|	A(x) = SUM	[(-1)^k / i!] x^k 	|
				|		   k>=0						      |
				+-----------------------------------+
				|			n						         |
				|	B(x) = SUM	[(i^n) / i!] x^k 	   |
				|		   k>=0						      |
				+-----------------------------------+		  
			
			then, S(n, k) = c(k), where c(k) is the coefficient of x^k in C(x).
			
Case 2 : We have 'n' objects and 'k' bins where bins can be empty

		The Bell numbers count the number of ways n distinct objects can be distributed into up to n identical non-empty bins. 
		In the language of sets, Bell numbers count the partitions of a set of n objects into non-empty disjoint subsets whose union is the entire set.
		
		The Stirling numbers denote the number of ways to arrange n distinct objects into k identical boxes,
		and the Bell numbers denote the number of ways to arrange n distinct objects into up to n identical objects.
		
		Hence, Bell numbers are computed as a sum of Stirling numbers:
		
					 ---------------------
					|		  n			   |
					|	Bn = SUM S(n, k)  |
					|		 k=1		      |
					 ---------------------
					 
-----------------------------------------------------------------------------------------------------------------------------------------------

// Distinct Objects into Distinct Bins
// ref : https://brilliant.org/wiki/distinct-objects-into-distinct-bins/

Suppose there are n distinct objects that are to be distributed among r distinct bins. This can be done in precisely r ^ n ways.

-----------------------------------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Splitting string using delimiter in C++

string s = "Banana,Mango,Apple,Grapes";
stringstream ss(s);
string piece;
while(getline(ss, piece, ','){
	cout << piece << "\n";
}

Output : 
	Banana	
	Mango
	Apple
	Grapes

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Useful char functions in C++

int isalnum(int ch)	The isalnum() function returns nonzero if its argument is a letter or a digit; otherwise it returns zero.
int isalpha(int ch)	This function returns nonzero if ch is an alphabet; otherwise it returns zero.
int isdigit(int ch)	Returns nonzero if ch is a digit (i.e., 0-9); otherwise it returns zero.
int islower(int ch)	Returns nonzero if ch is a lowercase letter ; otherwise it returns zero.
int isupper(int ch)	This function returns nonzero if ch is uppercase ; otherwise it returns zero.
int toupper(int ch)	Returns the uppercase equivalent of ch if ch is a letter; otherwise, ch is returned unchanged.
int tolower(int ch)	Returns the lowercase equivalent of ch if ch is a letter; otherwise ch is returned unchanged.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Know your STL Libraries :
1) <algorithm> - 	https://cplusplus.com/reference/algorithm/ , https://www.sandordargo.com/blog/2019/01/30/stl-algos-intro
2) <numeric>	-	https://cplusplus.com/reference/numeric/
3) <string>		-	https://cplusplus.com/reference/string/
4) <bitset>		-	https://cplusplus.com/reference/bitset/
5) <tuple>		-	https://cplusplus.com/reference/tuple/

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

1) AND(&) : Both 'T' then 'T', otherwise 'F'
2) OR(|)	 : Both 'F' then 'F', otherwise 'T'
3) XOR(^) :	Modulo 2 operation on sum of bits

4) Left-shift(<<)		:	Shifts all bits to the left and fills vacated bit positions with 0.
5) RIght-Shift(>>)	:	Shifts all bits to the right and fills vacated bit positions with 0.
NOTE: Where the left shift filled the vacated positions with 0, a right shift will do the same only when the value is unsigned. 
If the value is signed then a right shift will fill the vacated bit positions with the sign bit or 0, whichever one is implementation-defined. 
So the best option is to never right shift signed value

6) One's Complement(~) : The bitwise complement inverts the bits in a single binary number.

7) K-th Bit is Set or Not 	: 	if(N & (1 ≪ K -1) != 0) K'th bit is a set bit.
8) Setting K-th Bit			: 	N | 1 ≪ (K – 1)
9) Clearing K-th Bit 		: 	N & ~(1 ≪ K – 1)
10) Toggling K-th Bit 		: 	N ^(1 ≪ K – 1)

11) Toggling Rightmost One Bit 	: N & N – 1
12) Isolating Rightmost Zero Bit : ~N & N + 1

13) Number is Power of 2 or Not : if(N & N – 1 == 0) N is power of 2
14) Multiplying Number by Power of 2 : (N ≪ K) is equal to N * (2 ^ K) where ^ represents exponent
15) Dividing Number by Power of 2 :	(N ≫ K) is equal to N / (2 ^ K) where ^ represents exponent

16) Performing Average without Division : low + ((high – low) >> 1)
-------------------------------------------------------------------------------------------------------------

Some more important points for advanced bit manipulations

A)	Accessing the i'th digit (0-based lsb) of any number in base X. (Quite Useful Trick for Base-X Bitmasks)

	int digit  =  (num  %  pow[i + 1]) /  pow[i]; 		where pow[i] = X ^ i
 
For example :  Get 2nd digit of Base-10 number num = 2406137 
	(2406137  %  (10 ^ 3)) / 10^2 = 1; 
-------------------------------------------------------------------------------------------------------------

B)	Enumerating all submasks of a given mask : 
ref : https://cp-algorithms.com/algebra/all-submasks.html#enumerating-all-submasks-of-a-given-mask

for (int submask =  mask; submask; submask =  (submask -  1)  &  mask){
	 ... you can use submask here...
}
If we want to iterate over submasks of all the mask from [0, (1 << N - 1)], we can do it using above loop
in Time Complexity of (3^N)
	
for(int mask = 0; mask < (1 << N); ++mask){
	for (int submask =  mask; submask;	submask =  (submask -  1)  &  mask){
	 	... you can use submask here...
	}
}
-------------------------------------------------------------------------------------------------------------










	
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
// Get a topo ordering for a DAG using a simple DFS

int n;
vector<vector<int>> adj;
vector<bool> used;
vector<int> toposort;

void dfs(int u){
	used[u] = 1;
	for(auto &v :  adj[u]){
		if(!used[v]){
			dfs(v);
		}
	}
	toposort.push_back(u);
}
vector<int> getTopoOrdering(){
	for(int i = 0; i < n; ++i){
		if(!used[i]){
			dfs(i);
		}
	}
	reverse(begin(toposort), end(toposort));
	return toposort;
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
// Cycle detection and identification using 3-color dfs in directed graph

/*
t[i] stores color of node 'i' as : 
	- t[i] < 0 implies node 'i' hasn't been visited/touched yet 
	- t[i] = 0 implies node 'i' has been visited
	- t[i] > 0 implies we are examining whether node 'i'. It basically marks entry time of dfs. 
*/
		
vector<int> t;
vector<vector<int>> adj;
		
void dfs(int u, int par = -1){
  if(t[u] != 0){
		t[u] = (par == -1 ? 1 : 1 + t[par]);
		for(auto& v : adj[u]){
			 if(t[v] == -1){
				  dfs(v, u);
			 }else
			 if(t[v] > 0 && t[v] < t[u]){
				  	// gotcha! found a cycle with : u and v as endpoints & t[u] - t[v] + 1 as cycle length.
			 }
		}
		t[u] = 0;
  }
}
// call on each vertex
t.resize(n, -1);
for(int i = 0; i < n; ++i)  dfs(i);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Strongly Connected Components (SCC) for a directed graph
// src : https://www.topcoder.com/thrive/articles/kosarajus-algorithm-for-strongly-connected-components
		
		

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

// Modular Arithmetic + Combinatorics
/*______________________________________________________________________________________*/

const int mod = 1000000007;
template <
 int mod = mod
>
struct Modular {   
   int val; 
    
   Modular(){
      val=0;
   }
   Modular(long long _val){
      val = Normalize(_val);
   }
   Modular(int _val){
      val = Normalize(_val);
   }
   inline int Normalize(long long &_val){
      if(_val < 0)    _val = _val % mod + mod;
      if(_val >= mod) _val %= mod;
      return _val;  
   }
   inline int Normalize(int &_val){
      if(_val < 0)    _val = _val % mod + mod;
      if(_val >= mod) _val %= mod;
      return _val;  
   }
   inline Modular modinv(int a, int m = mod){
      int u = 0, v = 1;
      while (a != 0) {
         int t = m / a;
         m -= t * a; swap(a, m);
         u -= t * v; swap(u, v);
      }
      assert(m == 1);
      return u;
   }
   inline Modular modinv(){
      return modinv(val);
   }
   inline Modular modpow(long long p) const {
      assert(p >= 0);
      Modular a = *this, result = 1;
      while (p > 0){
         if (p & 1)
            result *= a;
         a *= a;
         p >>= 1;
      }
      return result;
   }

   inline Modular& operator += (const Modular& other) { 
      val += other.val; 
      if(val >= mod) val -= mod; 
      return *this; 
   }
   inline Modular& operator -= (const Modular& other) { 
      val -= other.val; 
      if(val < 0) val += mod; 
      return *this; 
   }
   inline Modular& operator %= (const Modular& other) { 
      val %= other.val;
      return *this; 
   }
   inline Modular& operator *= (const Modular& other) { 
      val = ((uint64_t)val * other.val) % mod;   
      return *this; 
   }
   inline Modular& operator /= (const Modular& other) { 
      return *this *= modinv(other.val); 
   }

   inline friend Modular operator + (const Modular& a, const Modular& b) { 
      return Modular(a) += b; 
   }
   inline friend Modular operator - (const Modular& a, const Modular& b) { 
      return Modular(a) -= b; 
   }
   inline friend Modular operator % (const Modular& a, const Modular& b) { 
      return Modular(a) %= b; 
   }
   inline friend Modular operator * (const Modular& a, const Modular& b) { 
      return Modular(a) *= b; 
   }
   inline friend Modular operator / (const Modular& a, const Modular& b) { 
      return Modular(a) /= b; 
   }

   inline friend istream& operator >> (istream& stream, Modular& m) {
      long long x; stream >> x; m.val = m.Normalize(x);
      return stream;
   }
   inline friend ostream& operator << (ostream& stream, const Modular& m) {
      return stream << m.val;
   }

   inline Modular operator ++ () { return *this += 1; }
   inline Modular operator -- () { return *this -= 1; }
   inline Modular operator ++(int) { Modular x = *this; ++*this; return x; }
   inline Modular operator --(int) { Modular x = *this; --*this; return x; }
   inline Modular operator -() const { return Modular(-val); }

   inline friend bool operator == (const Modular& a, const Modular& b) { return a.val == b.val; }
   inline friend bool operator != (const Modular& a, const Modular& b) { return a.val != b.val; }
   inline friend bool operator >  (const Modular& a, const Modular& b) { return a.val >  b.val; }
   inline friend bool operator <  (const Modular& a, const Modular& b) { return a.val <  b.val; }
   inline friend bool operator >= (const Modular& a, const Modular& b) { return a.val >= b.val; }
   inline friend bool operator <= (const Modular& a, const Modular& b) { return a.val <= b.val; }
};

#define mint Modular<mod> 
#define vm vector<mint>

mint  fc[(1 << 20) + 1];
mint _fc[(1 << 20) + 1];

mint  nCr (int n, int r) {return (n < r) ? 0 :  fc[n] * _fc[n-r] * _fc[r];}
mint _nCr (int n, int r) {return (n < r) ? 0 : _fc[n] *  fc[n-r] *  fc[r];}
mint  nPr (int n, int r) {return (n < r) ? 0 :  fc[n] * _fc[n-r];}
mint _nPr (int n, int r) {return (n < r) ? 0 : _fc[n] *  fc[n-r];}

inline void preProcessFact(int N = (1 << 20)){
   for(int i = 0;i <= N; i++){
      fc[i] = (i == 0 ? 1 : i * fc[i - 1]);
   }
   for(int i = N; ~i; --i){
      _fc[i] = (i == N ? fc[N].modinv() : (i + 1) * _fc[i + 1]);
   }
}

/*______________________________________________________________________________________*/
