/*
   Source to study : https://cp-algorithms.com/string/z-function.html
   Purpose of use  : The Z-function for this string is an array of length 'n' where the  
							i'th element is equal to the greatest number of characters starting from the position 'i' (prefix of substring(i, n - 1))
		 					that coincide with the first characters of s (prefix of 's').
		  
   Time Complexity : O(N)

	For example, here are the values of the Z-function computed for different strings:

	"aaaaa" - [0, 4, 3, 2, 1] 
	"aaabaab" - [0, 2, 1, 0, 2, 1, 0]
	"abacaba" - [0, 0, 1, 0, 3, 0, 1]
*/

 vector<int> zfunc(string s){
	  int n = size(s);
	  vector<int> z(n);
	  z[0] = n;
	  for(int i = 1, l = 0, r = 0; i < n; ++i){
			if(i < r){
				 z[i] = min(z[i - l], r - i);
			}
			while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
				 z[i]++;
			}
			if(i + z[i] > r){
				 l = i;
				 r = i + z[i];
			}
	  }
	  return z;
 }
