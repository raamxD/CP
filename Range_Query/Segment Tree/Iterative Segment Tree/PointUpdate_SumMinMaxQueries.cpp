using namespace std;
#include <bits/stdc++.h>+

struct SegTree{
	typedef long long ll; 
	vector<ll> S; ll n,tt; 
	// pass 't' as {-1,0,1} for {min,sum,max} segtree
	SegTree(vector<ll> arr,int t){   
		n=arr.size(); S.assign(2*n,0); tt=-1e18*t;
		for(int i=0;i<n;i++)  S[n+i]=arr[i];
		for(int i=n-1;i>0;i--)S[i]=fn(S[i*2],S[i*2+1]);        
	}
	void Updt(int p,int v){
		S[p+n]=v; p+=n;
		for(int i=p;i>1;i/=2)S[i/2]=fn(S[i],S[i^1]);
	}
	ll Kqry(int l,int r){
		ll res=tt;
		for(l+=n,r+=n;l<r;l/=2,r/=2){
			if(l&1)res=fn(res,S[l++]);
			if(r&1)res=fn(res,S[--r]);
		}return res;
	}
	inline ll fn(ll a,ll b){
		return(tt==0)?a+b:(tt<0)?max(a,b):min(a,b);
	}
};
int main(){
    vector<long long> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    SegTree S1(a,-1);
    cout<<S1.Kqry(3,6)<<"\n";
    S1.Updt(5,-1);
    cout<<S1.Kqry(3,6)<<"\n";
}
