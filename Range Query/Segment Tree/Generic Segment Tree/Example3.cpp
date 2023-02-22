#include <bits/stdc++.h>
using namespace std;


// Query1 : Get range minimum
// Query2 : Get range maximum
class Monoid{
public:
	static const int INF = 1e9;
	// TODO : Node info 
	int mn, mx;
	
	// TODO : Mandatory methods
	Monoid() : mn(INF), mx(-INF) {}
	Monoid(const Monoid& l, const Monoid& r) : mn(min(l.mn, r.mn)), mx(max(l.mx, r.mx)){ }
	
	// Custom methods
	Monoid(int x) : mn(x), mx(x) {}
	Monoid(int mn, int mx) : mn(mn), mx(mx) {}

};

// Update1 : Increment range 
// Update2 : Amplify range
class Function{
public:
	// TODO : Function representation 
	int add, mul;

	// TODO : Mandatory methods
	Function() : add(0), mul(1){
	}
	bool isIdentityFunction(){
		return add == 0 && mul == 1;
	}
	void compose(const Function& other){
		add = add * other.mul + other.add;
		mul = mul * other.mul;
	}
	Monoid operator()(const Monoid& node) const{
		return Monoid(node.mn * mul + add, node.mx * mul + add);
	}
	
	// Custom Methods
	Function(int add, int mul) : add(add), mul(mul) {}
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
	int n = 10;
	vector<Monoid> a(n, {0, 0});
	SegTree<Monoid, Function> ST(a); 
 
	auto print = [&](){
		cout << "Array : [";
		for(int i = 0; i < n; ++i){
			cout << ST.query(i, i).mx << ",]"[i == n - 1];
		}
		cout << "\n";
	};
	
	#define addUpdate(x) {x, 1}
	#define mulUpdate(x) {0, x}
	
	ST.update(0, 3, addUpdate(5)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n";
	ST.update(4, 9, addUpdate(7)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n"; 
	ST.update(4, 9, mulUpdate(2)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n";
	ST.update(2, 5, mulUpdate(3)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n";
	ST.update(0, 9, mulUpdate(0)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n";
	ST.update(0, 9, addUpdate(1)); print(); cout << "Min : " << ST.query(0, 9).mn << " | Max : " << ST.query(0, 9).mx << "\n\n";
	
	return 0;
}

/*

Output : 

Array : [5,5,5,5,0,0,0,0,0,0]
Min : 0 | Max : 5

Array : [5,5,5,5,7,7,7,7,7,7]
Min : 5 | Max : 7

Array : [5,5,5,5,14,14,14,14,14,14]
Min : 5 | Max : 14

Array : [5,5,15,15,42,42,14,14,14,14]
Min : 5 | Max : 42

Array : [0,0,0,0,0,0,0,0,0,0]
Min : 0 | Max : 0

Array : [1,1,1,1,1,1,1,1,1,1]
Min : 1 | Max : 1

*/
