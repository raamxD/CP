#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct hashFunc{
    
	const int p = 31;
	const int m = 1000000007;
	vector<long long> poww;

	hashFunc(int mxN){
		poww.assign(mxN,1);
		for(int i = 1; i < mxN; ++i){
			poww[i] = (poww[i - 1] * p) % m;
		}
	}
	long long hashVal(string const &s){
		int res = 0;
		int idx = 0;
		for(auto i : s){
			res += ((i - 'a' + 1) * poww[idx++]) % m;
		}
		return res;
	}
};

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s1 = "bitch";
	string s2 = "bitch";

	hashFunc H(100);
	cout << H.hashVal(s1) << " " << H.hashVal(s2) << "\n";
}
