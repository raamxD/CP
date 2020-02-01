/*
        note : NTT works only under special kind of mod.
 
        Source to study     -       1.  https://cp-algorithms.com/algebra/fft.html
                                    2.  https://codeforces.com/blog/entry/48798
        
        Make it faster      -       1.  If method 'Convolute' is needed multiple times, we can
                                        precompute inverse of powers of 2 as done in implementation.
                                    2.  After convoluting vectors 'a' and 'b', if they aren't needed
                                        anymore, you can store result of convolution in any one of them 
                                        instead of using third vector 'c'.
*/


////////////////////////////////////////////////////////////////////////////

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

const int G=3;
const int N=1<<20;
ll root[1<<20];
ll _pow2[(1<<20)+1];

struct ntt{
    ntt(){
        root[N/2]=1;root[N/2+1]=modpow(G,(mod-1)/N);
        for(int i=N/2+2;i<N;++i)root[i]=root[i-1]*root[N/2+1]%mod;
        for(int i=N/2;--i;)root[i]=root[2*i];
        for(int i=0;i<=20;i++)_pow2[1<<i]=inv(1<<i);
    }
    vl Convolute(vl &a, vl &b){
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

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //freopen(".\\testcases\\0.in","r",stdin);
    //freopen(".\\testcases\\0.out","w",stdout);
    cout <<"\n\n--------------------------------\n~OUTPUT:\n\n";      
    auto t_start = chrono::high_resolution_clock::now();
    /*COPY*/
    
    //  a = 3 + 5x - 4x^2 + 2x^3
    //  b = 7 - 2x + 0x^2 - 5x^3
 
    vector<ll> a = {3,5,-4,2};
    vector<ll> b = {7,-2,0,-5};
    
    //  a*b = c = 21 + 29x^1 + -38x^2 + 7x^3 + -29x^4 + 20x^5 + -10x^6
    vector<ll> c = NTT.Convolute(a,b);
    for(auto z : c) cout << z << " ";

    /*STOP*/
    auto t_end = chrono::high_resolution_clock::now(); 
    double t_elps = chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count();
    cout << "\n~Time Elapsed : " << fixed << setprecision(9) << t_elps * 1e-9 << " sec\n";
}

////////////////////////////////////////////////////////////////////////////
