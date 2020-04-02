/*
 * POLYNOMIAL TRANSLATION  :  Given coefficients of P(x) of degree n, we
                              need to find coeffcients of P(x+t).
                              All calculations are under NTT friendly mod.
                
 * TIME COMPLEXITY         :  O(nlogn) where n is degree of given polynomial 
   
 * SOURCE TO STUDY         :  1. https://discuss.codechef.com/t/binofev-editorial/48481
                              2. https://discuss.codechef.com/t/chefknn-editorial/18179
____________________________________________________________________________________________

   Let,
           n
   P(x) = SUM a_i*x^i
          i=0
      
             n
   P(x+t) = SUM a_i*(x+t)^i
            i=0
             
   But by binomial expansion,
                k=i
      (x+t)^i = SUM [iCk * (t)^(i-k) * (x)^k]
                k=0
      
   +--------------------------------------------------+
   |          n   n                                   |
   |  P(x+t) = SUM SUM [a_k * kCi * (t)^(k-i)] * x^i  |
   |          i=0 k=i                                 |
   +--------------------------------------------------+  
   
   +--------------------------------------------------------------+
   |                              n   n                           |
   | Coefficient of x^i in P(x+t) = SUM SUM [a_k * kCi* (t)^(k-i)]|
   |                        i=0 k=i                               |
   +--------------------------------------------------------------+                                               
             
   which is same as, 
      
       n
      SUM [ci/i!]
      i=0       
               n
   where ci = SUM [(a_k * k!) * (t)^(k-i)] / (k-i)!
              k=i 
   
              n                     
      M(x) = SUM [a_(n-i) * (n-i)!] x^i
             i=0
             
              n                     
      N(x) = SUM [t^i / i!] x^i
             i=0
                    
      R(x) = M(x).N(x)  and 
      
      coeffcient of x^i in R(x) is be r_i, then

      r_i = (p_0 * q_i) + (p_1 * q_(i-1)) + (p_2 * q_(i-2)) +.....+ (p_i * q_0) 
   
      Now it can be seen that 
      
      c_i = coeffcient of x^(n-i) in R(x)


   Therefore,
      found polynomial R(x) = M(x).N(x)
   
   +--------------------------------------------------+
   |        n                                         |
   | P(x+t) = SUM(coeffcient of x^(n-i) in R(x)) / i! |                    
   |        i=0                                       |
   +--------------------------------------------------+                                               
   where,
   +-----------------------------------+
   |       n                           |
   | M(x) = SUM [a_(n-i) * (n-i)!] x^i |
   |      i=0                          |
   +-----------------------------------+      
   |       n                           |
   | N(x) = SUM [t^i / i!] x^i         |
   |       i=0                         |
   +-----------------------------------+
______________________________________________________________________________________________

*/


using namespace std;
#include<bits/stdc++.h>
#define sz(a) a.size()
#define ll long long
#define vl vector<ll>
  
/// Modular Arithmetic 
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
         : "d" (xhi),"a"(xlo),"r"(m)
      );
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

/// Combinatorics
///////////////////////////////////////////////////////////////////////////

const int mxF = 1e5;
mint fc[mxF],_fc[mxF];

void PreCalFact(int N){
   fc[0]=1;for(int i=1;i<=N;i++) fc[i] = i * fc[i-1];
  _fc[N] = fc[N].modinv();
   for(int i=N-1;i>=0;--i) _fc[i] = (i+1) * _fc[i+1];
}
mint  nCr (ll n, ll r) {return (n < r) ? 0 :  fc[n] * _fc[n-r] * _fc[r];}
mint _nCr (ll n, ll r) {return (n < r) ? 0 : _fc[n] *  fc[n-r] *  fc[r];}
mint  nPr (ll n, ll r) {return (n < r) ? 0 :  fc[n] * _fc[n-r] * _fc[r];}
mint _nPr (ll n, ll r) {return (n < r) ? 0 : _fc[n] *  fc[n-r] *  fc[r];}

/// Number Theoretic Transform
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
   vm Convolute(vm &a, vm &b){
      int s=sz(a)+sz(b)-1,n=1;while(n<s)n*=2;
      vm c(n);
      a.resize(n);NTT(a);
      b.resize(n);NTT(b);
      for(int i=0;i<n;i++)c[i]=a[i]*b[i]*_pow2[n];
      reverse(c.begin()+1,c.end());
      NTT(c);
      //return{c.begin(),c.begin()+s};
      c.resize(s); return c;
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

/// Polynomial Translation
//////////////////////////////////////////////////////////////////////////////////////////////////

vm polyTranslation(vm &poly, mint t){
   int n = sz(poly);
   vm M(n),N(n),res(n); 
   mint powt=1;
   for(int i=0;i<n;i++){
      M[i] = poly[n-1-i] * fc[n-1-i];
      N[i] = powt * _fc[i];
      //Q[i] = t.modpow(i) * _fc[i];
      powt *= t;
   }
   vm R = NTT.Convolute(M,N);
   for(int i=0;i<n;i++){
      res[i] = R[n-1-i] * _fc[i];
   }
   return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(){    
   PreCalFact(1e5);
   vm a = {1,2};
   vm b = polyTranslation(a,1);
   for(auto z : b)
      cout << z << " ";
}
