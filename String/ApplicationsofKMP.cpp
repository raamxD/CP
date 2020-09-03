using namespace std;
#include "bits/stdc++.h"
#define ll long long

/// Search for a substring in a string. The Knuth-Morris-Pratt algorithm.
//////////////////////////////////////////////////////////////////////////////

// returns count of occurrence of 't' in 's'
int KMPSubstring(string s, string t){

   s = t + "#" + s;

   int n = s.size();
   vector<int> pi(n,0);
   for(int i = 1; i < n; ++i){        
      int prv = pi[i - 1];
      while(prv > 0 && s[i] != s[prv]) prv = pi[prv - 1];
      if(s[i] == s[prv]) ++prv;
      pi[i] = prv;
   }
   int cnt = 0;
   for(int i = t.size(); i < (int)s.size(); ++i)
      if(pi[i] == (int)t.size()) ++cnt;
   return cnt;
}
//////////////////////////////////////////////////////////////////////////////


/// Booth's Algorithm for Lexicographically Minimal String Rotation
/// Papers -> https://sci-hub.tw/https://www.sciencedirect.com/science/article/abs/pii/0020019080901490?via%3Dihub
/// Wikipedia -> https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation
//////////////////////////////////////////////////////////////////////////////

//returns Lexicographically Minimal String Rotation in O(N).
string boothsAlgo(string s){
   s += s;
   int n = int(s.size());
   vector<int> f(n, -1);
   int k = 0;
   for(int j = 1; j < n; ++j){
      int i = f[j - 1 - k];
      while(i != -1 && s[k + i + 1] != s[j]){
         if(s[k + i + 1] > s[j]){
            k = j - 1 - i;
         }
         i = f[i];
      }
      if(s[k + i + 1] != s[j]){
         if(s[k + i + 1] > s[j]){
            k = j;
         }
         f[j - k] = -1;
      }else{
         f[j - k] = i + 1;
      }
   }
   return s.substr(k, n / 2);
}

//////////////////////////////////////////////////////////////////////////////
int main(){
       
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   string a = "bababccb";
   cout << KMPSubstring(a, "ab");
   cout << "\n";

   string b = "aaaaaaa";
   cout << KMPSubstring(b, "a");
   cout << "\n";
}
