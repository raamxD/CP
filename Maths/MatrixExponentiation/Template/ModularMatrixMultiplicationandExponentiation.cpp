/*
	for operations under modulo, 
	simply create matrix of type mint.
*/

using namespace std;
#include "bits/stdc++.h"
#include "debug.h"
#define ll long long

const int mod = 1000000007;

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
//////////////////////////////////////////////////////////////////////////

template <typename T>
struct matrix{

   int row;
   int col;
   vector<vector<T>> A;

   matrix(){
      row = 0;
      col = 0;
   }
   matrix(int _row, int _col, int val = 0){
      row = _row;
      col = _col;
      A.assign(row, vector<T>(col, val));
   }
   // identity square matrix of size 'n'
   matrix(int n){
      row = col = n;
      A.assign(n, vector<T>(n));
      for(int i = 0; i < n; ++i){
         A[i][i] = (T)1;
      }
   }
   matrix operator * (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               C[r][c] += A[r][i] * B[i][c];
            }
         }
      }
      return C;	
   }	
   void operator *= (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               C[r][c] += A[r][i] * B[i][c];
            }
         }
      }
      row = C.row; col = C.col; A = C.A;
   }
   matrix operator ^ (long long p){
      assert(row == col);
      matrix<T> C(row);
      matrix<T> X(row, col);
      X.A = A;
      while(p){
         if(p & 1){
            C *= X;
         }
         X *= X;
         p /= 2;
      }
      return C;
   }
   void operator ^= (long long p){
      assert(row == col);
      matrix<T> C(row);
      matrix<T> X(row, col);
      X.A = A;
      while(p){
         if(p & 1){
            C *= X;
         }
         X *= X;
         p /= 2;
      }
      A = C.A;
   }
   vector<T>& operator[](int i){
      assert(i < row);
      assert(i >= 0);
      return A[i];
   }
   const vector<T>& operator[](int i)const{
      assert(i < row);
      assert(i >= 0);
      return A[i];
   }
   friend ostream& operator << (ostream &out, const matrix<T> m){
      for(int r = 0; r < m.row; ++r){
         for(int c = 0; c < m.col; ++c){
            out << m[r][c] << " ";
         }
         out << "\n";
      }
      return out;
   }
};