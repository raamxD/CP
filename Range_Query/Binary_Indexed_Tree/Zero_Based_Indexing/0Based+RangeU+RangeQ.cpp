#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

               
/*
               RANGE INCR UPDATES + RANGE SUM QUERIES

   Consider Fnwk0 and Fnwk1 initialized to 0.
   if we incremented [l,r] by value x, we will increment Fnwk0(l,r) by x.
   The prefix for i can be given by

            case 1 : 0             if i < l
   sum[0,i] =  case 2 : x*(i-l+1)      if l <= i <= r
            case 3 : x*(r-l+1)      if i > r
            
   We can use Fnwk1 to get sum[0,i] as Fnwk0[0,i] * i - Fnwk1[0,i]
   
            case 1 : 0*i - 0              if i < l
   sum[0,i] =  case 2 : x*i - x*(l-1)        if l <= i <= r
            case 3 : 0*i - (x*(-r)+x*(l-1))  if i > r
*/

struct BIT{
   
   vector<ll> Fnwk0,Fnwk1; int n;
   
   BIT(int _n){
      n = _n;
      Fnwk0.assign(n,0);
      Fnwk1.assign(n,0);
   }
   BIT(vector<int> a){
      n = a.size();
      Fnwk0.assign(n,0);
      Fnwk1.assign(n,0);
      for(int i=0; i<n; ++i) Updt(i,i,a[i]);
   }
   ll Kqry(vector<ll> &Fnwk, int i){
      ll res=0;
      for(; ~i; i&=i+1,--i)
         res += Fnwk[i];
      return res;
   }
   ll Kqry(int i){
      /* get sum of a[0...i] */
      return Kqry(Fnwk0,i)*i-Kqry(Fnwk1,i);
   }
   ll Kqry(int l, int r){
      /* get sum of a[l...r] */
      return (Kqry(r)-Kqry(l-1));
   }
   void Updt(vector<ll>&Fnwk, int i, int val){
      for(; i<n; i|=i+1)
         Fnwk[i] += val;
   }
   void Updt(int l, int r, int val){
      /* increment a[l...r] by val */
      Updt(Fnwk0,l,val);
      Updt(Fnwk0,r+1,-val);
      Updt(Fnwk1,l,val*(l-1));
      Updt(Fnwk1,r+1,val*(-r));
   }
};

int main() {

   vector<int> a = {1,2,3,4,5,6,7,8,9,10};
   
   BIT b(a);
   
   cout << b.Kqry(0,9) << "\n";
   cout << b.Kqry(2,9) << "\n";
   cout << b.Kqry(5,9) << "\n";
   cout << b.Kqry(8,9) << "\n";
   
   b.Updt(0,4,5); cout << "\n";
   
   cout << b.Kqry(0,9) << "\n";
   cout << b.Kqry(2,9) << "\n";
   cout << b.Kqry(5,9) << "\n";
   cout << b.Kqry(8,9) << "\n";
   
   b.Updt(0,0,50); cout << "\n";
   
   cout << b.Kqry(0,9) << "\n";
   cout << b.Kqry(2,9) << "\n";
   
   return 0;
}
