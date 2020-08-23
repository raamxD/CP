#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// RANGE INCR UPDATES + POINT VALUE QUERIES

struct BIT{
   
   vector<ll> Fnwk; int n;
   
   BIT(int _n){
      n = _n + 1;
      Fnwk.assign(n,0);
   }
   BIT(vector<int> a){
      n = a.size() + 1;
      Fnwk.assign(n,0);
      for(int i=0;i<n;++i) Updt(i,i,a[i]);
   }
   ll Kqry(int i){
      /* get value at a[i] */
      ll res = 0;
      for(++i; i; i-=i&-i)
         res += Fnwk[i];
      return res;
   }
   void Updt(int i, int val){
      /* increment a[i] by val */
      for(++i; i<n; i+=i&-i)
         Fnwk[i] += val;
   }
   void Updt(int l, int r, int val){
      /* increment a[l...r] by val */
      Updt(l,val);
      Updt(r+1,-val);
   }
};

int main() {

   vector<int> a = {1,2,3,4,5,6,7,8,9,10};
   
   BIT b(a);
   
   cout << b.Kqry(0) << "\n";
   cout << b.Kqry(2) << "\n";
   cout << b.Kqry(5) << "\n";
   cout << b.Kqry(8) << "\n";
   
   b.Updt(0,4,5); cout << "\n";
   
   cout << b.Kqry(0) << "\n";
   cout << b.Kqry(2) << "\n";
   cout << b.Kqry(5) << "\n";
   cout << b.Kqry(8) << "\n";
   
   b.Updt(0,0,50); cout << "\n";
   
   cout << b.Kqry(0) << "\n";
   cout << b.Kqry(2) << "\n";
   
   return 0;
}
