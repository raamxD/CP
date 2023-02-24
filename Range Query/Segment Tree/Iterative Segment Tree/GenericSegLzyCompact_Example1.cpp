using namespace std;
#include<bits/stdc++.h>

#define ll long long 
const int mod = 1000000007;

template<class M, class F>
class SegLzy{
public:
	#define _  j*2
	#define __ j*2+1
	
  int n, h; vector<M> T; vector<F> L;
	
	SegLzy(vector<M> a){
		n = a.size(); h=32-__builtin_clz(n);
		T.resize(2*n);L.resize(n);
		for(int i=0;i<n;i++)T[n+i]=a[i];
		for(int j=n-1;j>0;j--)T[j]=M(T[_],T[__]); 
	}
	M query(int l,int r){
		push(l,l+1);push(r-1,r); M res;
		for(l+=n,r+=n;l<r;l/=2,r/=2){
			if(l&1)res=M(res,T[l++]);
			if(r&1)res=M(res,T[--r]);
		}
		return res;
	}
	void update(int l,int r, const F& f){
		push(l,l+1);push(r-1,r);
		int s=l+n,e=r-1+n,k=1,j,c;
		for(l+=n,r+=n;l<r;l/=2,r/=2,k*=2) {
			 if(l&1){T[l]=f(T[l]);if(l<n)L[l].compose(f);l++;}
			 if(r&1){--r;T[r]=f(T[r]);if(r<n)L[r].compose(f);}
		}
		j=s;c=1;while((j/=2)>0)c*=2,T[j]=M(T[_],T[__]),T[j]=L[j](T[j]);
		j=e;c=1;while((j/=2)>0)c*=2,T[j]=M(T[_],T[__]),T[j]=L[j](T[j]);
	}
	void push(int l,int r){
		int s=h,k=1<<(h-1);
		for(l+=n,r+=n-1;s>0;--s,k/=2){
			for(int j=l>>s;j<=r>>s;++j){
				if(!L[j].isIdentityFunction()){
					T[_]=L[j](T[_]);if(_ <n)L[_].compose(L[j]);
					T[__]=L[j](T[__]);if(__<n)L[__].compose(L[j]);
					L[j] = F();
				}
			}
		}
	}
};
class Monoid{
public :  
	// TODO : Mandatory node info
    ll sum, sz;
    
	// TODO : Mandatory methods
	Monoid() : sum(0), sz(0){}
	Monoid(const Monoid& l, const Monoid& r) : sum((l.sum + r.sum) % mod), sz(l.sz + r.sz) {}
	
	// TODO : Non-mandatory custom methods
	Monoid(ll sum, ll sz) : sum(sum), sz(sz) {}
};
class Function{
public : 
	// TODO : Mandatory function representation
    ll add, mul;
    
	// TODO : Mandatory methods
	Function() : add(0), mul(1){}
	bool isIdentityFunction(){
	    return add == 0 && mul == 1;
	}
	void compose(const Function& other){
	    add = ((add * other.mul) % mod + other.add) % mod;
	    mul = (mul * other.mul) % mod;
	}
	Monoid operator()(const Monoid& node) const{
	    return Monoid(((node.sum * mul) % mod + (node.sz * add) % mod) % mod, node.sz);
	}
	
	// TODO : Non-mandatory custom methods
	Function(ll add, ll mul) : add(add), mul(mul){}
};

int main() {
	// your code goes here
	int N, Q;
	cin >> N >> Q;
	vector<Monoid> a(N);
	for(int i = 0; i < N; ++i){
	    int x; cin >> x;
	    a[i] = {x, 1};
	}
	SegLzy<Monoid, Function> ST(a);
	#define addUpdate(x) {x, 1}
	#define mulUpdate(x) {0, x}
	
	while(Q--){
	    int choice, l, r; 
	    cin >> choice >> l >> r;
	    --l; --r;
	    
	    ll v;
	    switch(choice){
	        case 1 : cin >> v;
	                 ST.update(l, r + 1, addUpdate(v));
	                 break;
	        case 2 : cin >> v;
	                 ST.update(l, r + 1, mulUpdate(v));
	                 break;
	        case 3 : cin >> v;
	                 ST.update(l, r + 1, mulUpdate(0));
	                 ST.update(l, r + 1, addUpdate(v));
	                 break;
	        case 4 : cout << ST.query(l, r + 1).sum << "\n";
	                 break;
	    }
	}
	return 0;
}
