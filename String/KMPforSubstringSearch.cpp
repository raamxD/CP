/*
	Source to study : https://cp-algorithms.com/string/prefix-function.html#toc-tgt-8
	Purpose of use  : Find number of occurences of given string 't' in given string 's'
	Time Complexity : O(N)
*/

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
