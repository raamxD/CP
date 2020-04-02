/*
   Yet Another Substring Reverse

   Problem Code       :  https://codeforces.com/contest/1234/problem/F
   Problem Analysis   :  https://codeforces.com/blog/entry/70233 
    
*/

using namespace std;
#include "bits/stdc++.h"
#define ll long long

const int lgN = 20;
const int mxN = (1 << 20);

int dp[mxN];

void solve(){

   string s;
   cin >> s;
    
   for(int i = 0; i < (int) s.size(); ++i){
      int mask = 0;
      for(int j = 0; j < 20 && j + i < (int) s.size(); ++j){
         int pos = (1 << (s[i + j] - 'a'));
         if(mask & pos){
            break;
         };
         mask ^= pos;
         dp[mask] = __builtin_popcount(mask);
      }
    }
   for(int mask = 0; mask < mxN; ++mask){
      for(int i = 0; i < lgN; ++i){
         if(mask & (1 << i)){
            dp[mask] = max(dp[mask], dp[(mask ^ (1 << i))]);
         }   
      }
    }
   int ans = INT_MIN;
   for(int i = 0; i < mxN; ++i){
      ans = max(ans, dp[i] + dp[~i & ((1 << lgN) - 1)]);
   }
   cout << ans;
}

int main(){
       
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   int t; t=1;
   while(t--)solve();
}
