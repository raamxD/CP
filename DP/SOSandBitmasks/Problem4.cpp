/*
    Problem Code : Marbles -> https://codeforces.com/contest/1215/problem/E
    Solution     : https://codeforces.com/blog/entry/69815

*/

/** 
 * @author  : raam
 * @created : Mar 31, 2020 - 3.16.43 PM IST
 *
 * असाध्य ते साध्य करिता सायास । कारण अभ्यास तुका म्हणे 
 *                                              - संत तुकाराम
 *
 * IMPOSSIBLE BECOMES POSSIBLE IF YOU TAKE EFFORTS.
 * PRACTICE  OVER  AND  OVER  TILL YOU  ACHIEVE IT.
 *                                              - SANT TUKARAM
 */
 
using namespace std;
#include "bits/stdc++.h"
#define ll long long

const int mxB = 20;
const int mxN = (1 << 20);
ll dp[mxN];
ll cost[mxB][mxB];
ll frq[mxB];

void solve(){
	int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        ++frq[--x];
        for(int j = 0; j < mxB; ++j)
            if(x != j) cost[x][j] += frq[j]; 
    }
    memset(dp,0x3f,sizeof(dp)); 
    dp[0] = 0;
    for(int mask = 0; mask < mxN; ++mask){
        for(int i = 0; i < mxB; ++i){
            if(!(mask & (1 << i))){
                ll c = 0;
                for(int j = 0; j < mxB; ++j)
                    if(mask & (1 << j))   
                        c += cost[j][i];
                int newmask = (mask ^ (1 << i));
                dp[newmask] = min(dp[newmask], dp[mask] + c);
            }
        }
    }
    cout << dp[mxN-1];
}

int main(){
       
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; t=1;
    while(t--)solve();
}
