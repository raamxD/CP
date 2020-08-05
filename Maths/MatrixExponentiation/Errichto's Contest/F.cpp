/*
	Problem Link	:	https://codeforces.com/gym/102644/problem/F
*/

//~raam
//~created : Aug 02, 2020 - 11.49.11 AM IST

using namespace std;
#include "bits/stdc++.h"
#include "debug.h"
#define ll long long

template <typename T>
struct matrix{

   int row;
   int col;
   vector<vector<T>> A;

   matrix(){
      row = 0;
      col = 0;
   }
   matrix(int _row, int _col, long long val = 0){
      row = _row;
      col = _col;
      A.assign(row, vector<T>(col, val));
   }
   // identity square matrix of size 'n'
   matrix(int n){
      row = col = n;
      A.assign(n, vector<T>(n));
      for(int i = 0; i < n; ++i){
         A[i][i] = (T)1;
      }
   }
   // modified multiplication specially for the problem requirement.
   // each cells store minimum instead of summation while multiplying.
   matrix operator * (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col, 2E18);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               if(A[r][i] == 2E18 || B[i][c] == 2E18) continue;
               C[r][c] = min(C[r][c], A[r][i] + B[i][c]);
            }
         }
      }
      return C;	
   }
   // modified multiplication specially for the problem requirement.
   void operator *= (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col, 2E18);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               if(A[r][i] == 2E18 || B[i][c] == 2E18) continue;
               C[r][c] = min(C[r][c], A[r][i] + B[i][c]);
            }
         }
      }
      row = C.row; col = C.col; A = C.A;
   }
   matrix operator ^ (long long p){
      assert(row == col);
      matrix<T> C(row);
      matrix<T> X(row, col);
      X.A = A;
      while(p){
         if(p & 1){
            C *= X;
         }
         X *= X;
         p /= 2;
      }
      return C;
   }
   void operator ^= (long long p){
      assert(row == col);
      matrix<T> C(row);
      matrix<T> X(row, col);
      X.A = A;
      while(p){
         if(p & 1){
            C *= X;
         }
         X *= X;
         p /= 2;
      }
      A = C.A;
   }
   vector<T>& operator[](int i){
      assert(i < row);
      assert(i >= 0);
      return A[i];
   }
   const vector<T>& operator[](int i)const{
      assert(i < row);
      assert(i >= 0);
      return A[i];
   }
   friend ostream& operator << (ostream &out, const matrix<T> m){
      for(int r = 0; r < m.row; ++r){
         for(int c = 0; c < m.col; ++c){
            out << m[r][c] << " ";
         }
         out << "\n";
      }
      return out;
   }
};
void solve(){
   int n, m, k;
   cin >> n >> m >> k;
   matrix<long long> mat(n, n, 2E18);
   for(int i = 0; i < m; ++i){
      int a, b, c;
      cin >> a >> b >> c;
      --a, --b;
      mat[a][b] = c;
   }
   mat ^= k;
   long long ans = 2E18; 
   for(int row = 0; row < n; ++row){
      for(int col = 0; col < n; ++col){
         ans = min(ans, mat[row][col]);
      }
   }
   if(ans == 2E18){
      cout << "IMPOSSIBLE";
      return;
   }
   cout << ans;
}
int main(){
       
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   int t; t=1;
   while(t--)solve();
}
