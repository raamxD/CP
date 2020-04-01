/*
	Aim : To get longest palindromic prefix (LPP) of given string in O(N).

	for example :  S = "abbacm" then longest palindromic prefix = "abba"
                  S = "xmcn"   then longest palindromic prefix = "x"    
*/

using namespace std;
#include "bits/stdc++.h"
#define ll long long

/// Using Manacher Algorithm in O(N)
//////////////////////////////////////////////////////////////////////////////

string manacherLPP(string s){
 
   int n = s.size();
   int odd[n], even[n];
    
   // manacher algo for finding all subpalindrome in O(N)
   for(int i = 0, l = 0, r = -1; i < n; ++i){
		int k = i > r ? 1 : min(odd[l + r - i], r - i + 1);
		while(0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
		odd[i] = k--;
		if(i + k > r) l = i - k, r = i + k;
   }
   for(int i = 0, l = 0, r = -1; i < n; ++i){
		int k = i > r ? 0 : min(even[l + r - i + 1], r - i + 1);
		while(0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
		even[i] = k--;
		if(i + k > r) l = i - k - 1, r = i + k;
   }

   //lines added for calculation of longest palindromic prefix (LPP)
   string res1 = "";
   for(int i = n - 1; ~i; --i){
      if(odd[i] - 1 == i){
         res1 = s.substr(0, 2 * odd[i] - 1);
         break;
      }
   }
   string res2 = "";
   for(int i = n - 1; ~i; --i){
		if(even[i] == i){
         res2 = s.substr(0, 2 * even[i]);
         break;
      }
   }
   return(res1.size() > res2.size() ? res1 : res2);
}

/// Using Prefix Function in O(N)
//////////////////////////////////////////////////////////////////////////////

string prefixFuncLPP(string s){

	string r = s;
	reverse(begin(r),end(r));
	s = s + "#" + r;

	int n = s.size();
	vector<int> pi(n,0);
	for(int i = 1; i < n; ++i){        
		int prv = pi[i - 1];
		while(prv > 0 && s[i] != s[prv]) prv = pi[prv - 1];
		if(s[i] == s[prv]) ++prv;
		pi[i] = prv;
	}
	return s.substr(0, pi[s.size()-1]);
}

//////////////////////////////////////////////////////////////////////////////

int main(){
       
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a = "bababccb";

	cout << prefixFuncLPP(a) << "\n";
	cout << manacherLPP(a) << "\n";
}
