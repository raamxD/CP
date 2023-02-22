// Problem : https://leetcode.com/problems/handling-sum-queries-after-update/description/
// Code : https://leetcode.com/problems/handling-sum-queries-after-update/submissions/903045329/

template<class M, class F>
class SegLzy{
public:
	#define Lf(x) (x<<1)+1
	#define Rg(x) (x<<1)+2
	
	SegLzy(int n) : N(n){
		while(__builtin_popcount(n)!=1)n++;
		T.resize(2*n);L.resize(2*n);
	}
	SegLzy(vector<M> a,int n) : N(n){
		while(__builtin_popcount(n)!=1)n++,a.push_back({});
		T.resize(2*n);L.resize(2*n);build(a);
	}
	void build(vector<M>& a){ 
		build(0,0,N-1,a); 
	}
	M query(int l,int r){
		return query(0,0,N-1,l,r);
	}
	void update(int l,int r,const F& f){
		update(0,0,N-1,l,r,f);
	}
	
private:
	int N; vector<M> T; vector<F> L;
	
	void build(int x,int s,int e,vector<M>& a){
		if(s==e) T[x]=a[s];
		else{
			int m=(s+e)/2;
			build(Lf(x),s,m,a); 
			build(Rg(x),m+1,e,a);
			T[x]=M(T[Lf(x)],T[Rg(x)]);
		}
	}
	M query(int x,int s,int e,int l,int r){
		if(l>e||r<s) return M();
		push(x,s,e);
		if(l<=s&&r>=e) return T[x];
		int m=(s+e)/2;
		return M(query(Lf(x),s,m,l,r),query(Rg(x),m+1,e,l,r));
	}
	void update(int x,int s,int e,int l,int r,const F& f){
		push(x,s,e);
		if(l>e||r<s){
		}else if(l<=s&&e<=r){
			L[x].compose(f);
			push(x,s,e); 
		}else{
			int m=(s+e)/2;
			update(Lf(x),s,m,l,r,f); 
			update(Rg(x),m+1,e,l,r,f);
			T[x]=M(T[Lf(x)],T[Rg(x)]);
		}
	}
	void push(int x,int s,int e){
		if(!L[x].isIdentityFunction()){
			T[x]=L[x](T[x]);
			if(s!=e){
				L[Lf(x)].compose(L[x]);
				L[Rg(x)].compose(L[x]);
			}
			L[x] = F();
		}
	}
};
class Monoid{
public :  
	// TODO : Mandatory node info
    int on, off;

	// TODO : Mandatory methods
	Monoid() : on(0), off(0){ }
	Monoid(const Monoid& l, const Monoid& r) : on(l.on + r.on), off(l.off + r.off){}
	
	// TODO : Non-mandatory custom methods
    Monoid(int on, int off) : on(on), off(off){ }
};
class Function{
public : 
	// TODO : Mandatory function representation
    bool toggle;

	// TODO : Mandatory methods
	Function() : toggle(false){ }
	bool isIdentityFunction(){
        return !toggle;
    }
	void compose(const Function& other){
        toggle ^= other.toggle;
    }
	Monoid operator()(const Monoid& node){
        return {node.off, node.on};
	}
	
	// TODO : Non-mandatory custom methods
    Function(bool toggle) : toggle(toggle) {}
};

/* 
	SegLzy<Monoid, Function> ST(N);
	SegLzy<Monoid, Function> ST(vector<Monoid> a, size(a));
*/

class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = size(nums1);
        
        vector<Monoid> a(n);
        for(int i = 0; i < n; ++i){
            a[i] = {nums1[i], !nums1[i]};
        }
        
        SegLzy<Monoid, Function> ST(a, size(a));
        #define toggleUpdate {1}
        
        long long sum = accumulate(begin(nums2), end(nums2), 0LL); 
        vector<long long> answer;

        for(auto& q : queries){
            if(q[0] == 1){
                ST.update(q[1], q[2], toggleUpdate);
            }else if(q[0] == 2){
                sum += 1LL * q[1] * ST.query(0, n - 1).on;
            }else{
                answer.push_back(sum);
            }
        }
        return answer;
    }
};
