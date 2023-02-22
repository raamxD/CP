/*

--Ref: https://s...content-available-to-author-only...b.io/blog/generalizing-segment-trees.html#query-function

--INTUTION:	Range queries on the segment trees modelled as elements of a monoid.
			Updates on the segment tree are functions on the monoid.

A Monoid is a class implementing the following mandatory methods:
* Monoid(); 											// constructor: identity element of monoid
* Monoid(const Monoid&, const Monoid&); 				// constructor: element created by combining 2 elements

A Function is a class implementing the following mandatory methods:
* Function();											// constructor: identity function
* void compose(const Function& other){} 				// function composition
* bool is_identity() const; 							// is identity function
* Monoid operator()(const Monoid&); 					// function definition

________________________________________________________________________________

class Monoid{
public :  
	// TODO : Node info 

	// TODO : Mandatory methods
	Monoid() : {}
	Monoid(const Monoid& l, const Monoid& r) : {}
	
	// Custom methods
};

class Function{
public : 
	// TODO : Function representation 
	
	// TODO : Mandatory methods
	Function() : {}
	bool isIdentityFunction(){}
	void compose(const Function& other){}
	Monoid operator()(const Monoid& node){}
	
	// Custom methods
};
_____________________________________________________________________*/

#include <bits/stdc++.h>
using namespace std;

template<class M, class F>
class SegTree{
// M : Monoid
// F : Function

public:
	typedef M value_type;
    typedef F func_type;
	
	static void identityCheck(){
		if(!F().isIdentityFunction()){
			cerr << "SegTree: function's default constructor is not identity\n";
			exit(1);
		}
	}

private:
	int N;
	vector<M> tree;
	vector<F> lazy;

public:
	SegTree(int n) : N(n), tree(4*N), lazy(4*N) {identityCheck();}
	SegTree(vector<M>& a) : N(a.size()), tree(4*N), lazy(4*N) {identityCheck(); build(a);}

private:
	#define LT(x) (x << 1) + 1
	#define RT(x) (x << 1) + 2
	
	void build(int node, int tl, int tr, vector<M>& a){
		if(tl == tr){
			tree[node] = a[tl];
		}else{
			int tm = (tl + tr) / 2;
			build(LT(node), tl, tm, a);
			build(RT(node), tm+1, tr, a);
			tree[node] = M(tree[LT(node)], tree[RT(node)]);
		}
	}
	void propagate(int node, int tl, int tr){
		if(!lazy[node].isIdentityFunction()){
			tree[node] = lazy[node](tree[node]);
			if(tl != tr){
				lazy[LT(node)].compose(lazy[node]);
				lazy[RT(node)].compose(lazy[node]);
			}
			lazy[node] = F();
		}
	}
	M query(int node, int tl, int tr, int ql, int qr){
		if(ql > tr || qr < tl){
			return M();
		}
		propagate(node, tl, tr);
		if(ql <= tl && qr >= tr){
			return tree[node];
		}else{
			int tm = (tl + tr) / 2;
			return M(
				query(LT(node), tl, tm, ql, qr),
				query(RT(node), tm+1, tr, ql, qr)
			);
		}
	}
	void update(int node, int tl, int tr, int ql, int qr, const F& f){
		propagate(node, tl, tr);
		if(ql > tr || qr < tl){
		}else if(ql <= tl && tr <= qr){
			lazy[node].compose(f);
			propagate(node, tl, tr); 
		}else{
			int tm = (tl + tr) / 2;
			update(LT(node), tl, tm, ql, qr, f);
			update(RT(node), tm+1, tr, ql, qr, f);
			tree[node] = M(tree[LT(node)], tree[RT(node)]);
		}
	}
	
public:
	void build(vector<M>& a){
		build(0, 0, N-1, a);
	}
	M query(int ql, int qr){
		return query(0, 0, N-1, ql, qr);
	}
	void update(int ql, int qr, const F& f){
		update(0, 0, N-1, ql, qr, f);
	}
};

int main() {
	
	vector<Monoid> a;
	SegTree<Monoid, Function> ST(a);
	
	// ST.update(l, r, updatetype);
	// ST.query(l, r).querytype;
	
	return 0;
}
