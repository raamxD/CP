#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// POINT INCR UPDATES + RANGE SUM QUERIES 

struct BIT{
	
	vector<ll> Fnwk; int n;
	
	BIT(int _n){
		n = _n;
		Fnwk.assign(n,0);
	}
	BIT(vector<int> a){
		n = a.size();
		Fnwk.assign(n,0);
		for(int i=0;i<n;++i) Updt(i,a[i]);
	}
	ll Kqry(int i){
		/* get sum from [0,i] of array 'a' */
		ll res = 0;
		for(; ~i; i&=(i+1),--i)
			res += Fnwk[i];
		return res;
	}
	ll Kqry(int l, int r){
		/* get sum from [l,r] of array 'a' */
		return(Kqry(r)-Kqry(l-1));
	}
	void Updt(int i, int val){
		/* increment a[i] by val */
		for(; i<n; i|=(i+1))
			Fnwk[i] += val;
	}
};

int main() {

	vector<int> a = {1,2,3,4,5,6,7,8,9,10};
	
	BIT b(a);
	
	cout << b.Kqry(0,9) << "\n";
	b.Updt(4,-5);
	cout << b.Kqry(0,9) << "\n";
	b.Updt(5,-6);
	cout << b.Kqry(0,9) << "\n";

	return 0;
}