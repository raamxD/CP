using namespace std;
#include "bits/stdc++.h"
#define ll long long

namespace MO{
   
   int q, mxB;

   struct Query{
      int id;
      int l; int r;
      int ans;
   }query[100005];

   bool cmp1(Query a, Query b){
      if(a.l/mxB != b.l/mxB)
         return a.l/mxB < b.l/mxB;
      return a.r < b.r;
   }
   bool cmp2(Query a, Query b){
      return a.id < b.id;
   }
   void init(int _q){
      q = _q;
      mxB = (int)sqrt(q);
      for(int i = 0; i < q; ++i){
         int l, r; 
         cin >> l >> r;
         query[i].l   = --l;
         query[i].r   = --r;
         query[i].id  = i;
         query[i].ans = 0;
      }
      sort(query, query + q, cmp1);
   }
   void solve(int n, int *arr){

      int sum = 0;
        
      auto add = [&](int idx){
         sum += arr[idx];
      };
      auto del = [&](int idx){
         sum -= arr[idx];
      };
        
      int curL = 0;
      int curR = -1;
      for(int i = 0; i < q; ++i){

         int queL = query[i].l;
         int queR = query[i].r;

         while(curL > queL)  add(--curL);
         while(curR < queR)  add(++curR);
         while(curL < queL)  del(curL++);
         while(curR > queR)  del(curR--);
         
         query[i].ans = sum; 
      }
      sort(query, query + q, cmp2);
      for(int i = 0; i < q; ++i){
         cout << query[i].ans << "\n";
      }
   }
};

void solve(){

   int n;
   cin >> n;
   int arr[n];
   for(int i = 0; i < n; ++i) cin >> arr[i];

   int q;
   cin >> q;
   MO::init(q);
   MO::solve(n, arr);
}
/*
int main(){
       
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   int t; cin >> t;
   while(t--)solve();
}
*/
int main(){

   ios_base::sync_with_stdio(0);
   cin.tie(0); 
   
   freopen(".\\testcases\\0.in","r",stdin);
   freopen(".\\testcases\\0.out","w",stdout);
   cout <<"\n--------------------------------\n~OUTPUT:\n\n";      
   
   auto t_start = chrono::high_resolution_clock::now();

   int t; cin >> t; while(t--) solve();
    
   auto t_end = chrono::high_resolution_clock::now();
   
   double t_elps = chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count();
   cout << "\n--------------------------------\n~Time Elapsed : ";
   cout << fixed << setprecision(9) << t_elps * 1e-9 << " sec\n\n";
}
