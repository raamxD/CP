#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

////////////////////////////////////////////////////////////////////

// Point Incr Updates + Range Sum Queries

struct ft{

   int n;
   vector<ll> b;
    
   ft(int _n){
      n = _n ;
      b.assign(n,0);
   }
   ft(vector<int> a){
      n = a.size();
      b.assign(n,0);
      for(int i = 0; i < n; ++i) Updt(i,a[i]);
   }
   void Updt(int i, int val){
      for(; i < n; i |= i+1)
         b[i] += val;
   }
   ll Kqry(int i){
      ll res = 0;
      for(; ~i; i &= i+1, --i)
         res += b[i];
      return res;
   }
   ll Kqry(int l, int r){
     return Kqry(r) - Kqry(l-1);
   }
};

////////////////////////////////////////////////////////////////////

// Range Incr Updates + Point Value Queries
struct ft{

   int n;
   vector<ll> b;
    
   ft(int _n){
      n = _n;
      b.assign(n,0);
   }
   ft(vector<int> a){
      n = a.size();
      b.assign(n,0);
      for(int i = 0; i < n; ++i) Updt(i,i,a[i]);
   }
   void Updt(int i, int val){
      for(; i < n; i |= i+1)
         b[i] += val;
   }
   void Updt(int l, int r, int val){
      Updt(l, val);
      Updt(r+1, -val);
   }
   ll Kqry(int i){
      ll res = 0;
      for(; ~i; i &= i+1, --i)
         res += b[i];
      return res;
   }
};

////////////////////////////////////////////////////////////////////

// Range Incr Updates + Range Sum Queries
struct ft{

   int n;
   vector<ll> b0, b1;
    
   ft(int _n){
      n = _n;
      b0.assign(n,0);
      b1.assign(n,0);        
   }
   ft(vector<int> a){
      n = a.size();
      b0.assign(n,0);
      b1.assign(n,0); 
      for(int i = 0; i < n; ++i) Updt(i,i,a[i]);
   }
   void Updt(vector<ll> &b, int i, int val){
      for(; i < n; i |= i+1)
         b[i] += val;
   }
   void Updt(int l, int r, int val){
      Updt(b0, l, val);
      Updt(b0, r+1, -val);
      Updt(b1, l, val*(l-1));
      Updt(b1, r+1, val*(-r));    
   }
   ll Kqry(vector<ll> &b, int i){
      ll res = 0;
      for(; ~i; i &= i+1, --i)
         res += b[i];
      return res;
   }
   ll Kqry(int i){
      return Kqry(b0,i) * i - Kqry(b1,i); 
   }
   ll Kqry(int l, int r){
     return Kqry(r) - Kqry(l-1);
   }
};

////////////////////////////////////////////////////////////////////

// 2D + Point Incr Updates + Range Sum Queries
struct ft{

   int r,c;
   vector<vector<ll>> b;
    
   ft(int _r, int _c){
      r = _r;
      c = _c;
      b.resize(r,vector<ll>(c,0));     
   }
   ft(vector<vector<int>> a){
      r = a.size();
      c = a[0].size();
      b.resize(r,vector<ll>(c,0)); 

      for(int i = 0; i < r; ++i)
         for(int j = 0; j < c; ++j)
            Updt(i,j,a[i][j]);
   }
   void Updt(int r1, int c1, int val){
      for(int i = r1; i < r; i |= i+1)
         for(int j = c1; j < c; j |= j+1)
            b[i][j] += val;
   }
   ll Kqry(int r1, int c1){
      ll res = 0;
      for(int i = r1; ~i; i &= i+1, --i)
         for(int j = c1; ~j; j &= j+1, --j)
            res += b[i][j];
      return res;
   }
   ll Kqry(int r1, int c1, int r2, int c2){
      if(r1 > r2 || c1 > c2) {
         swap(r1,r2); 
         swap(c1,c2);
      }
      return (Kqry(r2,c2) + Kqry(r1-1,c1-1) - Kqry(r2,c1-1) - Kqry(r1-1,c2));
   }
};

////////////////////////////////////////////////////////////////////
