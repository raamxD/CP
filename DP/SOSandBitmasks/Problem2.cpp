/*
   https://www.geeksforgeeks.org/number-ordered-pairs-ai-aj-0/

   Problem Statement    :  Given an array A[] of n integers, find out the number of ordered pairs such that Ai&Aj is zero, 
                           where 0<=(i,j)<n. Consider (i, j) and (j, i) to be different.
     
   Constraints    :  1 <= n <= 10^6
                     1 <= Ai <= 10^6

   Solution    :
     
      Let's try to find the valid pairs for 5. Considering it's present in array.
                     Now  Ai  =  5 -> 00101
      then possible Aj's are :   2 -> 00010 -> ~5    
                                 4 -> 00100    
                                 8 -> 01000
                                18 -> 11010
                                 ..    .... 
                                 ..    ....
                              and many more.

      let mask = [5 ^ (1 << log(mxN)-1)] = [~5 & (1 << log(mxN)-1)]
      It is noticeable that all the subsets of mask 
      will be such Aj's that will give zero on Anding with 5.        
      We just need count of those subsets present in given array, which will be answer for 5.

      Let dp[mask][i] represents set of only subset of mask which differ from mask only in first 'i' bits. (zero based)
                  
                           ------>  dp[mask][i]                          , if (i+1)'th bit of mask is on.
      dp[mask][i + 1]   =  |    
                           |
                           ------>  dp[mask][i] + dp[mask^(1<<(i+1))][i] , if (i+1)'th bit of mask is off.
 
*/

using namespace std;
#include<bits/stdc++.h>

const int lgN = 20;
const int mxN = (1 << lgN);

int dp[mxN][lgN];
int cnt[mxN+1];

int main(){
   int n;
   cin >> n;
   int a[n];
   for(int i = 0; i < n; ++i)
      cin >> a[i];
   for(int i = 0; i < n; ++i)
      cnt[a[i]] += 1;
   for(int mask = 0; mask < mxN; ++mask){
      if(mask & 1){
         dp[mask][0] = cnt[mask] + cnt[mask^1];
      }
      else{ 
         dp[mask][0] = cnt[mask];
      }
      for(int i = 1; i < lgN; ++i){
         if(mask & (1 << i)){
            dp[mask][i] = dp[mask][i-1] + dp[mask ^ (1 << i)][i-1];
         }else{
            dp[mask][i] = dp[mask][i-1];
         }
      }
   }
   int ans = 0;
   for(int i = 0; i < n; ++i)
      ans += dp[~a[i] & (1 << lgN)-1][lgN-1];
   cout << ans;
}

/*

INPUT : 
   3
   3 4 2

   4
   5 4 1 6

OUTPUT :
   4

   4
*/
