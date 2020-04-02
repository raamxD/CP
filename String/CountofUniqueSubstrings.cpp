/*  
 *  Source to study :   https://cp-algorithms.com/string/string-hashing.html#toc-tgt-5
 *  Aim : to get count of occurrences of unique substrings of given string 's'
 */

#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct hashFunc{
    
   const int p = 31;
   const int m = 1000000007;
   vector<long long> poww;

   hashFunc(int mxN){
      poww.assign(mxN,1);
      for(int i = 1; i < mxN; ++i){
         poww[i] = (poww[i - 1] * p) % m;
      }
   }
   long long hashVal(string const &s){
      int res = 0;
      int idx = 0;
      for(auto i : s){
         res += ((i - 'a' + 1) * poww[idx++]) % m;
      }
      return res;
   }
   long long unqSubstrings(string const &s){
      int n = s.size();
      vector<long long> h(n + 1, 0);
      for(int i = 0; i < n; ++i)
      h[i + 1] = (h[i] + (s[i] - 'a' + 1) * poww[i]) % m;
      int cnt = 0;
      for(int i = 1; i <= n; ++i){
         set<long long> hs;
         for(int j = 0; j <= n - i; ++j){
            long long curh = (h[j + i] + m - h[j]) % m;
            curh = (curh * poww[n - j - 1]) % m;
            hs.insert(curh);
         }
         cnt += hs.size();
      }
      return cnt;
   }
};

int main(){

   ios_base::sync_with_stdio(0);
   cin.tie(0);

   string s1 = "bitch";
   string s2 = "abab";

   hashFunc H(100);
   cout << H.hashVal(s1) << " " << H.unqSubstrings(s2) << "\n";
}

