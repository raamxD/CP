#include <bits/stdc++.h>
using namespace std;

// Query1 : Get count of on bits in range
// Query2 : Get count of off bits in range
class Monoid{
public:
	// TODO : Node info 
	int on, off;
	
	// TODO : Mandatory methods
	Monoid() : on(0), off(0){}
	Monoid(const Monoid& l, const Monoid& r) : on(l.on + r.on), off(l.off + r.off){}
	
	// Custom methods
	Monoid(int on, int off) : on(on), off(off) {}
};

// Update1 : Toggle bits in range
class Function{
public:
	// TODO : Function representation 
	bool toggle;
    
	// TODO : Mandatory methods
	Function() : toggle(0){
	}
	bool isIdentityFunction(){
		return toggle == 0;
	}
	void compose(const Function& other){
		toggle ^= other.toggle;
	}
	Monoid operator()(const Monoid& node){
        return {node.off, node.on};
	}
	
	// Custom methods
	Function(bool toggle) : toggle(toggle){}
};

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
	// your code goes here
	int n = 10;
	vector<Monoid> a(n, {0, 1});
	SegTree<Monoid, Function> ST(a); 
	
	auto print = [&](){
		cout << "Array : [";
		for(int i = 0; i < n; ++i){
			cout << ST.query(i, i).on << ",]"[i == n - 1];
		}
		cout << "\n";
	};
	
	#define toggleUpdate {1}
	
	ST.update(0, 3, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n";
	ST.update(4, 9, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n"; 
	ST.update(4, 9, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n"; 
	ST.update(2, 5, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n"; 
	ST.update(0, 9, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n"; 
	ST.update(0, 9, toggleUpdate); print(); cout << "Setbits : " << ST.query(0, n - 1).on << "\n\n"; 
	
	return 0;
}

/* 
Output : 
	
Array : [1,1,1,1,0,0,0,0,0,0]
Setbits : 4

Array : [1,1,1,1,1,1,1,1,1,1]
Setbits : 10

Array : [1,1,1,1,0,0,0,0,0,0]
Setbits : 4

Array : [1,1,0,0,1,1,0,0,0,0]
Setbits : 4

Array : [0,0,1,1,0,0,1,1,1,1]
Setbits : 6

Array : [1,1,0,0,1,1,0,0,0,0]
Setbits : 4

*/
