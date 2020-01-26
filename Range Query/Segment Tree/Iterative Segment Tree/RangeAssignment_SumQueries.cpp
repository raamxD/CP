using namespace std;
#include <bits/stdc++.h>

struct SegLzy{
    typedef long long ll;
    #define _  j*2
    #define __ j*2+1

    vector<ll> S,L; int n,h;

    SegLzy(vector<int> ar){
        n=ar.size(); h=32-__builtin_clz(n);
        S.assign(2*n,0); L.assign(n,0);
        for(int i=0;i<n;i++)S[n+i]=ar[i];
        for(int j=n-1;j>0;j--)S[j]=S[_]+S[__];  
    }
    inline void Push(int l,int r) {
        ll s=h,k=1<<(h-1);
        for(l+=n,r+=n-1;s>0;--s,k/=2){
            for(int j=l>>s;j<=r>>s;++j)if(L[j]){
                S[_] =L[j]*k;if(_ <n)L[_] =L[j];
                S[__]=L[j]*k;if(__<n)L[__]=L[j];
                L[j] = 0;
            }
        }      
    }
    void Updt(int l,int r,int v){
        ll s=l+n,e=r-1+n,k=1,j,c;
        for(l+=n,r+=n;l<r;l/=2,r/=2,k*=2) {
            if(l&1){S[l]=v*k;if(l<n)L[l]=v;l++;}
            if(r&1){--r;S[r]=v*k;if(r<n)L[r]=v;}
        }
        j=s;c=2;while((j/=2)>0)
        S[j]=(!L[j])?S[_]+S[__]:L[j]*c,c*=2;
        j=e;c=2;while((j/=2)>0)
        S[j]=(!L[j])?S[_]+S[__]:L[j]*c,c*=2;
    }
    long long Kqry(int l,int r,ll res=0){
        Push(l,l+1);Push(r-1,r);
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1)res+=S[l++];
            if(r&1)res+=S[--r];
        }return res;
    }
};

int main(){
    vector<int> a = {1,2,3,4,5,6,7,8,9,10};
    SegLzy S1(a);
    cout << S1.Kqry(0,10) << endl;
    S1.Updt(0,5,5);
    cout << S1.Kqry(0,5) << endl;
    S1.Updt(0,4,3);
    cout << S1.Kqry(0,5) << endl;
}

//------------------------------------------------------------------------------
// struct SegLzy{
    
//     vector<int> S,L; ll n,h;

//     SegLzy(vector<int> ar){
//         n=ar.size(); h=32-__builtin_clz(n);
//         S.assign(2*n,0); L.assign(n,0);
//         for(int i=0;i<n;i++)S[n+i]=ar[i];
//         for(int j=n-1;j>0;j--)S[j]=S[2*j]+S[2*j+1];  
//     }

//     void calc(int p, int k) {
//         if (L[p] == 0) S[p] = S[p<<1] + S[p<<1|1];
//         else S[p] = L[p] * k;
//     }

//     void apply(int p, int value, int k) {
//         S[p] = value * k;
//         if (p < n) L[p] = value;
//     }

//     void build(int l, int r) {
//         int k = 2;
//         for (l += n, r += n-1; l > 1; k <<= 1) {
//             l >>= 1, r >>= 1;
//             for (int i = r; i >= l; --i) calc(i, k);
//         }
//     }

//     void push(int l, int r) {
//         int s = h, k = 1 << (h-1);
//         for (l += n, r += n-1; s > 0; --s, k >>= 1)
//             for (int i = l >> s; i <= r >> s; ++i) if (L[i] != 0) {
//                 apply(i<<1, L[i], k);
//                 apply(i<<1|1, L[i], k);
//                 L[i] = 0;
//             }
//     }

//     void modify(int l, int r, int value) {
//         if (value == 0) return;
//         push(l, l + 1);
//         push(r - 1, r);
//         int l0 = l, r0 = r, k = 1;
//         for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
//             if (l&1) apply(l++, value, k);
//             if (r&1) apply(--r, value, k);
//         }
//         build(l0, l0 + 1);
//         build(r0 - 1, r0);
//     }

//     int query(int l, int r) {
//         push(l, l + 1);
//         push(r - 1, r);
//         int res = 0;
//         for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
//             if (l&1) res += S[l++];
//             if (r&1) res += S[--r];
//         }
//         return res;
//     }
// };

// int main(){
//     vector<int> a = {1,2,3,4,5,6,7,8,9,10};
//     SegLzy S1(a);
//     cout << S1.query(0,10) << endl;
//     S1.modify(0,5,5);
//     cout << S1.query(0,5) << endl;
//     S1.modify(0,4,3);
//     cout << S1.query(0,5) << endl;
// }

