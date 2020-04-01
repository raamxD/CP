/*
	Source to study : https://cp-algorithms.com/string/prefix-function.html
	Purpose of use  : Finds prefix function array (pi) for given string.
	Time Complexity : O(N)

	Prefix Function for the string 's' is defined as an array pi of length n, where pi[i] is the 
	length of the longest proper prefix of the substring s[0…i] which is also a suffix of this substring. 
	A proper prefix of a string is a prefix that is not equal to the string itself.

	for example : S = "bababccb"

	S[i]    = b a b a b c c b
	pi[i]   = 0 0 1 2 3 0 0 1 
*/

using namespace std;
#include "bits/stdc++.h"
#define ll long long

/// Prefix Function in O(N)
//////////////////////////////////////////////////////////////////////////////

vector<int> prefixFunc(string s){

	int n = s.size();
	vector<int> pi(n,0);
	for(int i = 1; i < n; ++i){        
		int prv = pi[i - 1];
		while(prv > 0 && s[i] != s[prv]) prv = pi[prv - 1];
		if(s[i] == s[prv]) ++prv;
		pi[i] = prv;
	}
	return pi;
}

//////////////////////////////////////////////////////////////////////////////

int main(){
       
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a = "bababccb";
	vector<int> pi = prefixFunc(a);
	for(auto i : pi) cout << i << " ";
	cout << "\n";
}
