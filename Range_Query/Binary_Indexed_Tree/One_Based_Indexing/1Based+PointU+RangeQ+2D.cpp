#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT2D{
	int r,c;
	vector<vector<ll>> Fnwk;

	BIT2D(int _r, int _c){
		r = _r + 1;
		c = _c + 1;
		Fnwk.resize(r,vector<ll>(c,0));
	}
	BIT2D(vector<vector<ll>> A){
		r = A.size() + 1;
		c = A[0].size() + 1;
		Fnwk.resize(r,vector<ll>(c,0));
			
		for(int i=1;i<r;++i) 
			for(int j=1;j<c;++j)
				Updt(i-1,j-1,A[i-1][j-1]);
		
		/*cout << "Fnwk[][] : \n";
		for(int i=1;i<r;++i) 
			for(int j=1;j<c;++j)
				cout<<Fnwk[i][j]<<(j==c-1?"\n":"\t");*/
	}
	ll Kqry(int r1, int c1){
		/*get sum of submatrix with top left corner as (0,0)
		and bottom right corner as (r1,c1)*/
		ll res = 0;
		for(int i=r1+1; i; i-=i&-i)
			for(int j=c1+1; j; j-=j&-j)
				res += Fnwk[i][j];
		return res;
	}
	ll Kqry(int r1, int c1, int r2, int c2){
		/*get sum of submatrix with top left corner as (r1,c1)
		and bottom right corner as (r2,c2)*/
		return (Kqry(r2,c2)+Kqry(r1-1,c1-1)-Kqry(r2,c1-1)-Kqry(r1-1,c2));
	}
	void Updt(int r1, int c1, int val){
		/*increment value at A[r1][c1] by val*/
		for(int i=r1+1; i<r; i+=i&-i)
			for(int j=c1+1; j<c; j+=j&-j)
				Fnwk[i][j] += val;
	}
};

int main() {

	/*int r=5,c=5;
	vector<vector<ll>> A(r,vector<ll>(c,0));*/
	
	vector<vector<ll>> A = {{1, 2, 3, 4, 5 },
							{6, 7, 8, 9, 10},
							{11,12,13,14,15},
							{16,17,18,19,20},
							{21,22,23,24,25}};
							
	/*cout << "A[][] : \n";
	for(int i=0;i<r;++i) 
		for(int j=0;j<c;++j)
			cout<<A[i][j]<<(j==c-1?"\n":"\t");*/
	
	BIT2D B(A);
	
	cout << B.Kqry(1,1) << "\n";
	cout << B.Kqry(0,2) << "\n";
	cout << B.Kqry(2,0) << "\n";
	cout << B.Kqry(2,2) << "\n";
	
	B.Updt(0,0,5); cout << "\n";
	
	cout << B.Kqry(1,1) << "\n";
	cout << B.Kqry(0,2) << "\n";
	cout << B.Kqry(2,0) << "\n";
	cout << B.Kqry(2,2) << "\n";
	
	B.Updt(0,0,-5); cout << "\n";
	
	cout << B.Kqry(0,0,1,1) << "\n";
	cout << B.Kqry(0,0,0,2) << "\n";
	cout << B.Kqry(0,0,2,0) << "\n";
	cout << B.Kqry(0,0,2,2) << "\n";
	
	cout << "\n";
	
	cout << B.Kqry(1,1,1,1) << "\n";
	cout << B.Kqry(2,2,3,3) << "\n";
	cout << B.Kqry(4,4,4,4) << "\n";
	cout << B.Kqry(1,2,3,4) << "\n";
	
	return 0;
}
