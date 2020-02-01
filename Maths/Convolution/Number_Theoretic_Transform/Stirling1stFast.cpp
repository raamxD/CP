/*
    Read about Stirling numbers  -   https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind
 
    O(NlogN) approach to find coefficients of polynomial using polynomial translation technique. 
        1. [x * (x-1) * (x-2) * ... * (x-r)]
        2. [x * (x+1) * (x+2) * ... * (x+r)]
    
    Note - 1. Coefficients are calculated under NTT friendly modulus.

*/

using namespace std;
#include<bits/stdc++.h>
#define sz(a) a.size()
typedef long long ll;
typedef vector<ll> vl;
  
/// Modular Arithmetic Stuff
///////////////////////////////////////////////////////////////////////////

const int mod = 998244353;
template <int mod = mod>
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
        while (p > 0) {
            if (p & 1)
                result *= a;
            a *= a;
            p >>= 1;
        }
        return result;
    }
    static unsigned Fastmod(uint64_t x, unsigned m = mod) {
        #if !defined(_WIN32)
            return x % m;
        #endif
        unsigned xhi = x >> 32, xlo = (unsigned) x;
        unsigned q, r;
        asm("divl %4\n"
            : "=a"(q),"=d" (r)
            : "d" (xhi),"a"(xlo),"r"(m));
        return r;
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
        val = Fastmod((uint64_t)val * other.val);   
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
    
    inline Modular operator ++ () { return *this += 1; }
    inline Modular operator -- () { return *this -= 1; }
    inline Modular operator ++(int) { Modular x = *this; ++*this; return x; }
    inline Modular operator --(int) { Modular x = *this; --*this; return x; }
    inline Modular operator -() const { return Modular(-val); }
    
    inline friend bool operator == (const Modular& a, const Modular& b) { 
        return a.val == b.val; 
    }
    inline friend bool operator != (const Modular& a, const Modular& b) { 
        return a.val != b.val; 
    }
    inline friend bool operator >  (const Modular& a, const Modular& b) { 
        return a.val >  b.val; 
    }
    inline friend bool operator <  (const Modular& a, const Modular& b) {
        return a.val <  b.val; 
    }
    inline friend bool operator >= (const Modular& a, const Modular& b) {
        return a.val >= b.val; 
    }
    inline friend bool operator <= (const Modular& a, const Modular& b) {
        return a.val <= b.val; 
    }
	
    inline friend istream& operator >> (istream& stream, Modular& m) {
	long long x; stream >> x; m.val = m.Normalize(x);
	return stream;
    }
    inline friend ostream& operator << (ostream& stream, const Modular& m) {
        return stream << m.val;
    }
};

#define mint Modular<mod> 
#define vm   vector<mint> 

/// Combinatorics Stuff
///////////////////////////////////////////////////////////////////////////

const int mxF = 1e6;
mint  fc[mxF+1];
mint _fc[mxF+1];

inline void PreCalFact(int N = mxF){
    fc[0]=1;
    for(int i=1;i<=N;i++) fc[i]=i*fc[i-1];
    _fc[N] = fc[N].modinv();
    for(int i=N-1;i>=0;--i) _fc[i]=(i+1)*_fc[i+1];
}
mint  nCr (ll n, ll r) {return (n < r) ? 0 :  fc[n] * _fc[n-r] * _fc[r];}
mint _nCr (ll n, ll r) {return (n < r) ? 0 : _fc[n] *  fc[n-r] *  fc[r];}
mint  nPr (ll n, ll r) {return (n < r) ? 0 :  fc[n] * _fc[n-r] * _fc[r];}
mint _nPr (ll n, ll r) {return (n < r) ? 0 : _fc[n] *  fc[n-r] *  fc[r];}

/// Number Theoretic Transform Stuff
//////////////////////////////////////////////////////////////////////////////////////////////////

const int G=3;
const int N=1<<20;
mint root[1<<20];
mint _pow2[(1<<20)+1];

struct ntt{
    ntt(){
        root[N/2]=1;root[N/2+1]=((mint)G).modpow((mod-1)/N);
        for(int i=N/2+2;i<N;++i)root[i]=root[i-1]*root[N/2+1];
        for(int i=N/2;--i;)root[i]=root[2*i];
        for(int i=0;i<=20;i++)_pow2[1<<i]=((mint)(1<<i)).modinv();
    }
    void Convolute(vm &a, vm &b){
        int s=sz(a)+sz(b)-1,n=1;while(n<s)n*=2;
        a.resize(n);NTT(a);
        b.resize(n);NTT(b);
        for(int i=0;i<n;i++)a[i]*= b[i]*_pow2[n];
        reverse(a.begin()+1,a.end());
        NTT(a);a.resize(s);
    }
    void NTT(vm &a){
        int n=a.size();
        for(int i=0,j=0;i<n;++i){
            if(i>j)swap(a[i],a[j]);
            for(int k=n/2;(j^=k)<k;k/=2);
        }
        for(int k=1;k<n;k*=2){
            for(int i=0;i<n;i+=2*k){
                for(int j=0;j<k;j++){
                    mint z=root[j+k]*a[i+j+k],&ai=a[i+j];
                    a[i+j+k]=ai-z;
                    ai+=z;
                }
            }
        }
    }	
}NTT;

/// Polynomial Translation Stuff
//////////////////////////////////////////////////////////////////////////////////////////////////

vm polyTranslation(vm &poly, mint t){
    int n = sz(poly);
    if(n==1) return poly;
    vm M(n),N(n),res(n); 
    mint powt=1;
    for(int i=0;i<n;i++){
        M[i] = poly[n-1-i] * fc[n-1-i];
        N[i] = powt * _fc[i];
        powt *= t;
    }
    NTT.Convolute(M,N);
    for(int i=0;i<n;i++){
        res[i] = M[n-1-i] * _fc[i];
    }
    return res;
}

/// Get Stirling Coefficient
//////////////////////////////////////////////////////////////////////////////////////////////////

// O(nlogn) recursive approach return
// Coefficients of polynomial           [x * (x-1) * (x-2) * ....* (x-r)]
// if want Coefficients of polynomial   [x * (x+1) * (x+2) * ....* (x+r)]
// change as per comments

vm getStirling(int r){
    if(r == 0) return {1};
    vector<mint> A = getStirling(r/2);
    vector<mint> B = polyTranslation(A,-r/2); // r/2
    NTT.Convolute(A,B);
    if(r&1){
        A.push_back(0);
        for(int i=sz(A)-2;i>=0;--i) {
            A[i+1]+=A[i];
            A[i]*=(-(r-1)); // (r-1)
        }
    }
    return A;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //freopen(".\\testcases\\0.in","r",stdin);
    //freopen(".\\testcases\\0.out","w",stdout);
    cout <<"\n\n--------------------------------\n~OUTPUT:\n\n";      
    auto t_start = chrono::high_resolution_clock::now();
    /*COPY*/
    
    PreCalFact();
    vm S = getStirling(3);
    cout << "\nPoly : ";for(auto z: S) cout << z << " "; cout<<"\n";
   
    /*STOP*/
    auto t_end = chrono::high_resolution_clock::now(); 
    double t_elps = chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count();
    cout << "\n~Time Elapsed : " << fixed << setprecision(9) << t_elps * 1e-9 << " sec\n";
}
