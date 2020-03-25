/*  
 *  Source to study :  https://cp-algorithms.com/string/rabin-karp.html 
 *  Aim : Given 2 strings 't' and 's', count occurrences of string 's'
 *        in string 't'.
 *  Time Complexity : O(|s| + |t|)
 */

#define _GLIBCXX_DEBUG
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct RabinKarp{
    
    const int p = 31;
    const int m = 1000000007;
    vector<long long> poww;

    RabinKarp(int mxN){
        poww.assign(mxN,0);
        poww[0] = 1;
        for(int i = 1; i < mxN; ++i)
            poww[i] = (poww[i - 1] * p) % m;
    }
    //returns occurrences of 's' in 't'
    vector<int> getCount(string const &s, string const &t){
        int S = s.size();
        int T = t.size();
        vector<long long> h(T + 1, 0);
        for(int i = 0; i < T; ++i)
            h[i + 1] = (h[i] + (t[i] - 'a' + 1) * poww[i]) % m;
        long long hs = 0;
        for(int i = 0; i < S; ++i)
            hs = (hs + (s[i] - 'a' + 1) * poww[i]) % m;
        vector<int> occ;
        for(int i = 0; i + S - 1 < T; ++i){
            long long curh = (h[i + S] + m - h[i]) % m;
            if(curh == (hs * poww[i]) % m)
                occ.push_back(i);
        }
        return occ;
    }   
};

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string t = "aaaaa";
    string s = "aa";

    RabinKarp RK(100);
    vector<int> occ = RK.getCount(s,t);
    if(!occ.empty())
        cout << "string 't' appears at pos : ";
    for(auto i : occ)
        cout << i + 1 << " ";
    cout << "\n";
}



