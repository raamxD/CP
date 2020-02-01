/*
        Source to study     -   https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind
        
        O(nlog^2n) approach to find coefficients of polynomial
            1. [x * (x-1) * (x-2) * ... * (x-r)]
            2. [x * (x+1) * (x+2) * ... * (x+r)]
        
        These rising or falling factorial type polynomial's coefficient known as Stirling Numbers of 1st Kind.
        Code uses Divide and Conquer Strategy and is pretty fast when r <= 10^5.
        For r > 10^5 use O(nlogn) approach using polynomial translation.

        Note : 1. Coefficients are calculated under NTT friendly modulus.
               2. You can make it faster by making it compatible Mint class (NTTwithMint.cpp).
*/

using namespace std;
#include<bits/stdc++.h>
#define sz(a) a.size()
typedef long long ll;
typedef vector<ll> vl;

const int mod=998244353;

ll modpow(ll a,ll b){
    ll res=1;a=a%mod;
    while(b>0){
        if(b&1)res=(res*a)%mod;
        b=b>>1;
        a=(a*a)%mod;
    }
    return res;
}
ll inv(ll a){
    return modpow(a,mod-2);
}

/// Number Theoretic Transform Stuff
//////////////////////////////////////////////////////////////////////////////////////////////////

const int G=3;
const int N=1<<20;
ll root[1<<20];
ll _pow2[(1<<20)+1];

struct ntt{
    ntt(){
        root[N/2]=1;root[N/2+1]=modpow(G,(mod-1)/N);
        for(int i=N/2+2;i<N;++i)root[i]=root[i-1]*root[N/2+1]%mod;
        for(int i=N/2;--i;)root[i]=root[2*i];
        for(int i=1;i<=20;i++)_pow2[1<<i]=inv(1<<i);
    }
    vl Convolute(vl a, vl b){
        int s=sz(a)+sz(b)-1,n=1;while(n<s)n*=2;
        vl c(n);
        a.resize(n);NTT(a);
        b.resize(n);NTT(b);
        for(int i=0;i<n;i++)c[i]=a[i]*b[i]%mod*_pow2[n]%mod;
        reverse(c.begin()+1,c.end());
        NTT(c);
        //return{c.begin(),c.begin()+s};
        c.resize(s); return c;
    }
    void NTT(vl &a){
        int n=a.size();
        for(int i=0,j=0;i<n;++i){
            if(i>j)swap(a[i],a[j]);
            for(int k=n/2;(j^=k)<k;k/=2);
        }
        for(int k=1;k<n;k*=2){
            for(int i=0;i<n;i+=2*k){
                for(int j=0;j<k;j++){
                    ll z=root[j+k]*a[i+j+k]%mod,&ai=a[i+j];
                    a[i+j+k]=(z>ai?ai-z+mod:ai-z);
                    ai+=(ai+z>=mod?z-mod:z);
                }
            }
        }
    }	
}NTT;

/// Stirling numbers of first kind
//////////////////////////////////////////////////////////////////////////////////////////////////

// O(nlog^2n) recursive approach
// Coefficients of polynomial           [x * (x-1) * (x-2) * ....* (x-r)]
// If want coefficients of polynomial   [x * (x+1) * (x+2) * ....* (x+r)]
// change line 1 of GetStirling to return {l,1};
 
vector<ll> GetStirling(int l,int r){
     if(l==r)return{-l,1};
     int m=(l+r+1)/2;
     return NTT.Convolute(GetStirling(l,m-1),GetStirling(m,r));
 }

//---------------------------------------------------------------------------

// O(nlog^2n) iterative approach returns
// Coefficients of polynomial           [x * (x-1) * (x-2) * ....* (x-(r-1))]
// If want coefficients of polynomial   [x * (x+1) * (x+2) * ....* (x+(r+1))]
// change line 1 of GetStirling to poly[i] = {i,1};
    
vector<ll> poly[100005];
vector<ll> GetStirling(int r){
    for(int i=0;i<r;i++)poly[i]={-i,1};
    for(int i=0;i<r-1;i+=2){
        poly[i].push_back(1);
        poly[i][1]=(poly[i][0]+poly[i+1][0]+mod)%mod;
        poly[i][0]=(poly[i][0]*poly[i+1][0])%mod;
    }
    for(int i=2;i<r;i*=2){
        for(int j=0;j<r;j+=2*i){
            if(j+i>=r)break;

            // multiply poly[j] and poly[j+i] and store result in poly[j]
            // To use next line, change Convolute accordingly and comment down below lines.
            // NTT.Convolute(poly[j],poly[j+i]); 
            
            int sj=sz(poly[j]),sji=sz(poly[j+i]),n=1;int s=sj+sji-1;
            while(n<s)n*=2;
            poly[j].resize(n);
            poly[j+i].resize(n);
            NTT.NTT(poly[j]);
            NTT.NTT(poly[j+i]);
            for(int k=0;k<n;k++)
                poly[j][k]=poly[j][k]*poly[j+i][k]%mod*_pow2[n]%mod;
            reverse(poly[j].begin()+1,poly[j].end());
            NTT.NTT(poly[j]);
            poly[j].resize(s);
        }
    }
    return poly[0];
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //freopen(".\\testcases\\0.in","r",stdin);
    //freopen(".\\testcases\\0.out","w",stdout);
    cout <<"\n\n--------------------------------\n~OUTPUT:\n\n";      
    auto t_start = chrono::high_resolution_clock::now();
    /*COPY*/
    
    vector<ll> S;
    
    S = GetStirling(0,2);
    for(auto z:S) cout<<z<<" "; cout<<"\n";

    S = GetStirling(3);
    for(auto z:S) cout<<z<<" "; cout<<"\n";
   
    /*STOP*/
    auto t_end = chrono::high_resolution_clock::now(); 
    double t_elps = chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count();
    cout << "\n~Time Elapsed : " << fixed << setprecision(9) << t_elps * 1e-9 << " sec\n";
}
