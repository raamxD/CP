/*
	Operations allowed : 1) multiplication
								2) exponentiation.

	Will add more utilites later.
*/

template <typename T>
struct matrix{

   int row;
   int col;
   vector<vector<T>> A;

   matrix(){
      row = 0;
      col = 0;
   }
   matrix(int _row, int _col, int val = 0){
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
   matrix operator * (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               C[r][c] += A[r][i] * B[i][c];
            }
         }
      }
      return C;	
   }	
   void operator *= (const matrix<T> &B){
      assert(col == B.row);
      matrix<T> C(row, B.col);
      for(int r = 0; r < row; ++r){
         for(int c = 0; c < B.col; ++c){
            for(int i = 0; i < col; ++i){
               C[r][c] += A[r][i] * B[i][c];
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