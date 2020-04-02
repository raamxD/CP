/*
      note  :  NTT works only under special kind of mod.
 
      Source to study   -  1. https://cp-algorithms.com/algebra/fft.html
                           2. https://codeforces.com/blog/entry/48798
        
      Make it faster    -  1. If method 'Convolute' is needed multiple times, we can
                              precompute inverse of powers of 2 as done in implementation.
                           2. After convoluting vectors 'a' and 'b', if they aren't needed
                              anymore, you can store result of convolution in any one of them 
                              instead of using third vector 'c'.
*/



////////////////////////////////////////////////////////////////////////////

using namespace std;
#include<bits/stdc++.h>
#define sz(a) a.size()
typedef long long ll;
typedef vector<ll> vl;

/// Modular Arithmetic 
/////////////////////////////////////////////////////////////////////////

const int mod=998244353;
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
      while (p > 0){
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
#define vm   vector<mint> 

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

//////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

   ios_base::sync_with_stdio(0);
   cin.tie(0);

   //freopen(".\\testcases\\0.in","r",stdin);
   //freopen(".\\testcases\\0.out","w",stdout);
   cout <<"\n\n--------------------------------\n~OUTPUT:\n\n";      
   auto t_start = chrono::high_resolution_clock::now();
   /*COPY*/

   //  a = 3 + 5x - 4x^2 + 2x^3
   //  b = 7 - 2x + 0x^2 - 5x^3

   vector<mint> a = {3,5,-4,2};
   vector<mint> b = {7,-2,0,-5};

   //  a*b = c = 21 + 29x^1 + -38x^2 + 7x^3 + -29x^4 + 20x^5 + -10x^6
   vector<mint> c = NTT.Convolute(a,b);
   for(mint z : c) cout << z << " ";

   /*STOP*/
   auto t_end = chrono::high_resolution_clock::now(); 
   double t_elps = chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count();
   cout << "\n~Time Elapsed : " << fixed << setprecision(9) << t_elps * 1e-9 << " sec\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////

