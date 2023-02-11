using namespace std;
#include <bits/stdc++.h>
#define ll long long

struct SegLzy{
    #define _  j*2
    #define __ j*2+1

    vector<int> S,L; ll n,h,tt;
    //pass 't' as {-1,1} for {min,max} segtree
    SegLzy(vector<int> ar,int t){
        n=ar.size(); h=32-__builtin_clz(n); tt=-1e18*t;
        S.assign(2*n,0); L.assign(n,0);
        for(int i=0;i<n;i++)S[n+i]=ar[i];
        for(int j=n-1;j>0;j--)S[j]=fn(S[_],S[__]);  
    }
    void inline Push(long long p){
        for(int i=h,j=p>>i;i>0;--i,j=p>>i)if(L[j]){
            S[_] =L[j];if(_ <n)L[_] =L[j];
            S[__]=L[j];if(__<n)L[__]=L[j];
            L[j]=0;
        } 
    }
    void Updt(int l,int r,int v){
        ll s=l+n,e=r-1+n,j;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1){S[l]=v;if(l<n)L[l]=v;l++;}
            if(r&1){--r;S[r]=v;if(r<n)L[r]=v;}
        }
        j=s;while((j/=2)>0)S[j]=fn(fn(S[_],S[__]),L[j]);
        j=e;while((j/=2)>0)S[j]=fn(fn(S[_],S[__]),L[j]);
    }
    long long Kqry(int l,int r){
        Push(l+n); Push(r-1+n); ll res=tt;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1)res=fn(res,S[l++]);
            if(r&1)res=fn(res,S[--r]);
        }return res;
    }
    inline ll fn(ll x,ll y){
        return(tt<0)?max(x,y):min(x,y);
    }
};

int main() {
    
   vector<int> a = {1,2,3,4,5,6,7,18,9,10};
   SegLzy S(a,1);
   cout << "Kqry [0,10) : " << S.Kqry(0,10) << endl;
   cout << "Kqry [0,5)  : " << S.Kqry(0,5) << endl;
   S.Updt(3,7,10);
   cout << "Kqry [0,10) : " << S.Kqry(0,10) << endl;
   cout << "Kqry [0,5)  : " << S.Kqry(0,5) << endl;
}

//-----------------------------------------------------------------------------  
