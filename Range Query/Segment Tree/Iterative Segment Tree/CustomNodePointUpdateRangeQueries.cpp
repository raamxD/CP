template<typename T>
struct SegTree{
    int n; vector<T> S;  
    SegTree(vector<T>& a){
        n=a.size(); S.resize(2*n);
        for(int i=0;i<n;i++)S[n+i]=a[i];
        for(int i=n-1;i>0;i--)S[i]=fn(S[i*2],S[i*2+1]);
    }
    void Updt(int p,T v){
        for(S[p+=n]=v;p>>=1;)
            S[p]=fn(S[p*2],S[p*2+1]);
    }
    T Kqry(int l,int r){
        T cl=T(),cr=T();
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1)cl=fn(cl,S[l++]);
            if(r&1)cr=fn(S[--r],cr);
        }
        return fn(cl,cr);
    }
    T fn(T a, T b){
        T ans = T();
        // merge nodes a and b
        return ans;
    }
};

vector<T> a;
SegTree S(a);  

---------------------------------------------------------------------------------------------------------------

struct node {
    node(){
    }
    node operator + (node other){
        node res;
        // merge node with other
        return res;
    }
};
template<typename T>
struct SegTree{
    int n;
    vector<T> S;  
    SegTree(vector<T>& a){
        n=a.size(); S.resize(2*n);
        for(int i=0;i<n;i++)S[n+i]=a[i];
        for(int i=n-1;i>0;i--)S[i]=fn(S[i*2],S[i*2+1]);
    }
    void Updt(int p,T v){
        for(S[p+=n]=v;p>>=1;)
            S[p]=fn(S[p*2],S[p*2+1]);
    }
    T Kqry(int l,int r){
        T cl=T(),cr=T();
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1)cl=fn(cl,S[l++]);
            if(r&1)cr=fn(S[--r],cr);
        }
        return fn(cl,cr);
    }
    T fn(T a, T b){
        return a + b;
    }
};

vector<node> a;
SegTree S(a);

---------------------------------------------------------------------------------------------------------------
