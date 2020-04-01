/*
    Refer : https://codeforces.com/blog/entry/45223
            https://www.geeksforgeeks.org/sum-subsets-dynamic-programming/

    Problem Statement : Given a fixed array A of 2^N integers, we need to calculate ∀ x function 
                        F(x) = Sum of all A[i] such that x&i = i, i.e., i is a subset of x. 
*/

/*
 *  Let dp[mask][i] represents set of only subset of mask which differ from mask only in first 'i'
 *  bits. (zero based)
 *
 *  Now, transition for given mask while moving from i'th state to (i+1)'th
 *                      
 *                     ------>  dp[mask][i]                          , if (i+1)'th bit of mask is on.
 *  dp[mask][i + 1] =  |    
 *                     |
 *                     ------>  dp[mask][i] + dp[mask^(1<<(i+1))][i] , if (i+1)'th bit of mask is off.
 *
 */

#define GLIBCXX_DEBUG
#include<bits/stdc++.h>
using namespace std;

const int lgN = 10;
const int mxN = (1 << lgN);

int dp[mxN][lgN];
int a[mxN];
int F[mxN];

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; ++i)
        cin >> a[i];

    for(int mask = 0; mask < mxN; ++mask){
        if(mask < n){
            // Base Condition
            if(mask & 1) dp[mask][0] = a[mask] + a[mask^1];
            else dp[mask][0] = a[mask];
        }
        for(int i = 1; i < lgN; ++i){
            if(mask & (1 << i)){
                dp[mask][i] = dp[mask][i-1] + dp[mask ^ (1 << i)][i-1];
            }else{
                dp[mask][i] = dp[mask][i-1];
            }
        }
        F[mask] = dp[mask][lgN-1];
    }
    
    //More memory optimized
    //for(int i = 0; i < n; ++i)
        //F[i] = a[i];
    //for(int i = 0; i < lgN; ++i){
        //for(int mask = 0; mask < mxN; ++mask){
            //if(mask & (1 << i))
                //F[mask] += F[mask ^ (1 << i)];
        //}
    //}

    for(int i = 0; i < n; ++i)
        cout << F[i] << " ";
}

/*

INPUT : 
4
7 12 14 16

OUTPUT:
7 19 21 49

Explanation: There will be 4 values of x: 0,1,2,3
So, we need to calculate F(0),F(1),F(2),F(3).
F(0) = A0 = 7 
F(1) = A0 + A1 = 19
F(2) = A0 + A2 = 21
F(3) = A0 + A1 + A2 + A3 = 49

*/
