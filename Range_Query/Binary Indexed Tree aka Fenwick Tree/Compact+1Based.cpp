#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

////////////////////////////////////////////////////////////////////

// Point Incr Updates + Range Sum Queries

struct ft{

   int n;
   vector<ll> b;
    
   ft(int _n){
      n = _n + 1;
      b.assign(n,0);
   }
   ft(vector<int> a){
      n = a.size() + 1;
      b.assign(n,0);
      for(int i = 0; i < n; ++i) Updt(i,a[i]);
   }
   void Updt(int i, int val){
      for(++i; i < n; i += i & -i)
         b[i] += val;
   }
   ll Kqry(int i){
      ll res = 0;
      for(++i; i; i -= i & -i)
         res += b[i];
      return res;
   }
   ll Kqry(int l, int r){
      return Kqry(r) - Kqry(l-1);
   }
	// returns lower_bound on prefix sum of array 'a'
	int Find(int val){
      int pos = 0, sum = 0;
      for(int i = 20; ~i; --i){
         if(pos + (1 << i) < n && sum + b[pos + (1 << i)] < val){
            pos += (1 << i);
            sum += b[pos];
         }
      }
      return pos;
   }
};


////////////////////////////////////////////////////////////////////


// Range Incr Updates + Point Value Queries
struct ft{

   int n;
   vector<ll> b;
    
   ft(int _n){
      n = _n + 1;
      b.assign(n,0);
   }
   ft(vector<int> a){
      n = a.size() + 1;
      b.assign(n,0);
      for(int i = 0; i < n; ++i) Updt(i,i,a[i]);
   }
   void Updt(int i, int val){
      for(++i; i < n; i += i & -i)
         b[i] += val;
   }
   void Updt(int l, int r, int val){
      Updt(l, val);
      Updt(r+1, -val);
   }
   ll Kqry(int i){
      ll res = 0;
      for(++i; i; i -= i & -i)
         res += b[i];
      return res;
   }
	// if the array 'a' is decreasing then, Find(val)
	// returns rightmost index of 'a' such that a[index] >= val
	int Find(int val){
      int pos = 0, sum = 0;
      for(int i = 20; ~i; --i){
         if(pos + (1 << i) < n && sum + b[pos + (1 << i)] >= val){
            pos += (1 << i);
            sum += b[pos];
         }
      }
      return pos;
   }
};


////////////////////////////////////////////////////////////////////


// Range Incr Updates + Range Sum Queries
struct ft{

   int n;
   vector<ll> b0, b1;
    
   ft(int _n){
      n = _n + 1;
      b0.assign(n,0);
      b1.assign(n,0);        
   }
   ft(vector<int> a){
      n = a.size() + 1;
      b0.assign(n,0);
      b1.assign(n,0); 
      for(int i = 0; i < n; ++i) Updt(i,i,a[i]);
   }
   void Updt(vector<ll> &b, int i, int val){
      for(++i; i < n; i += i & -i)
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
      for(++i; i; i -= i & -i)
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
      r = _r + 1;
      c = _c + 1;
      b.resize(r,vector<ll>(c,0));     
   }
   ft(vector<vector<int>> a){
      r = a.size() + 1;
      c = a[0].size() + 1;
      b.resize(r,vector<ll>(c,0)); 

      for(int i = 0; i < r - 1; ++i)
         for(int j = 0; j < c - 1; ++j)
            Updt(i,j,a[i][j]);
   }
   void Updt(int r1, int c1, int val){
      for(int i = r1 + 1; i < r; i += i & -i)
         for(int j = c1 + 1; j < c; j += j & -j)
            b[i][j] += val;
   }
   ll Kqry(int r1, int c1){
      ll res = 0;
      for(int i = r1 + 1; i; i -= i & -i)
         for(int j = c1 + 1; j; j -= j & -j)
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
