// Problem : https://www.codechef.com/problems/ADDMUL

using namespace std;
#include<bits/stdc++.h>

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

template<class M, class F>
class SegLzy{
public:
	#define Lf(x) (x<<1)+1
	#define Rg(x) (x<<1)+2
	
	SegLzy(int n) : N(n){
		while(__builtin_popcount(n)!=1)n++;
		T.resize(2*n);L.resize(2*n);
	}
	SegLzy(vector<M> a,int n) : N(n){
		while(__builtin_popcount(n)!=1)n++,a.push_back({});
		T.resize(2*n);L.resize(2*n);build(a);
	}
	void build(vector<M>& a){ 
		build(0,0,N-1,a); 
	}
	M query(int l,int r){
		return query(0,0,N-1,l,r);
	}
	void update(int l,int r,const F& f){
		update(0,0,N-1,l,r,f);
	}
	
private:
	int N; vector<M> T; vector<F> L;
	
	void build(int x,int s,int e,vector<M>& a){
		if(s==e) T[x]=a[s];
		else{
			int m=(s+e)/2;
			build(Lf(x),s,m,a); 
			build(Rg(x),m+1,e,a);
			T[x]=M(T[Lf(x)],T[Rg(x)]);
		}
	}
	M query(int x,int s,int e,int l,int r){
		if(l>e||r<s) return M();
		push(x,s,e);
		if(l<=s&&r>=e) return T[x];
		int m=(s+e)/2;
		return M(query(Lf(x),s,m,l,r),query(Rg(x),m+1,e,l,r));
	}
	void update(int x,int s,int e,int l,int r,const F& f){
		push(x,s,e);
		if(l>e||r<s){
		}else if(l<=s&&e<=r){
			L[x].compose(f);
			push(x,s,e); 
		}else{
			int m=(s+e)/2;
			update(Lf(x),s,m,l,r,f); 
			update(Rg(x),m+1,e,l,r,f);
			T[x]=M(T[Lf(x)],T[Rg(x)]);
		}
	}
	void push(int x,int s,int e){
		if(!L[x].isIdentityFunction()){
			T[x]=L[x](T[x]);
			if(s!=e){
				L[Lf(x)].compose(L[x]);
				L[Rg(x)].compose(L[x]);
			}
			L[x] = F();
		}
	}
};
class Monoid{
public :  
	// TODO : Mandatory node info
    mint sum, sz;
    
	// TODO : Mandatory methods
	Monoid() : sum(0), sz(0){}
	Monoid(const Monoid& l, const Monoid& r) : sum(l.sum + r.sum), sz(l.sz + r.sz) {}
	
	// TODO : Non-mandatory custom methodsy
	Monoid(mint sum, mint sz) : sum(sum), sz(sz){}
};
class Function{
public : 
	// TODO : Mandatory function representation
    mint add, mul;
    
	// TODO : Mandatory methods
	Function() : add(0), mul(1){}
	bool isIdentityFunction(){
	    return add == 0 && mul == 1;
	}
	void compose(const Function& other){
	    add = add * other.mul + other.add;
	    mul = mul * other.mul;
	}
	Monoid operator()(const Monoid& node){
	    return Monoid(node.sum * mul + node.sz * add, node.sz);
	}
	
	// TODO : Non-mandatory custom methods
	Function(mint add, mint mul) : add(add), mul(mul){}
};

/* 
	SegLzy<Monoid, Function> ST(N);
	SegLzy<Monoid, Function> ST(vector<Monoid> a, size(a));
*/

int main() {
	// your code goes here
	int N, Q;
	cin >> N >> Q;
	vector<Monoid> a(N);
	for(int i = 0; i < N; ++i){
	    int x; cin >> x;
	    a[i] = {x, 1};
	}
	SegLzy<Monoid, Function> ST(a, size(a));
	#define addUpdate(x) {x, 1}
	#define mulUpdate(x) {0, x}
	
	while(Q--){
	    int choice, l, r; 
	    cin >> choice >> l >> r;
	    --l; --r;
	    
	    mint v;
	    switch(choice){
	        case 1 : cin >> v;
	                 ST.update(l, r, addUpdate(v));
	                 break;
	        case 2 : cin >> v;
	                 ST.update(l, r, mulUpdate(v));
	                 break;
	        case 3 : cin >> v;
	                 ST.update(l, r, mulUpdate(0));
	                 ST.update(l, r, addUpdate(v));
	                 break;
	        case 4 : cout << ST.query(l, r).sum << "\n";
	                 break;
	    }
	}
	return 0;
}
