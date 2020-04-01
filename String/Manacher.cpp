/*
	Source to study : https://cp-algorithms.com/string/manacher.html
	Purpose of use  : Finds all subpalindrome of given string.
	Time Complexity : O(N)

	for example : S = "bababccb"

	2 * odd[i] - 1  = length of longest odd  length palindrome with centre S[i]
	2 * even[i]     = length of longest even length palindrome with centre S[i]

	S[i]    = b a b a b c c b
	odd[i]  = 1 2 3 2 1 1 1 1
	even[i] = 0 0 0 0 0 0 2 0
*/

using namespace std;
#include "bits/stdc++.h"
#define ll long long

void manacher(string s){
 
	int n = s.size();
	int odd[n], even[n];
 
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
	cout << "ODD : ";for(int i = 0; i < n; ++i) cout << odd[i] << " "; 
	cout << "\n";
	cout << "EVE : ";for(int i = 0; i < n; ++i) cout << even[i] << " ";
	cout << "\n";
}

int main(){
       
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
	string  S = "bababccb";
	manacher(S);
}
