#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch OddSubrectangles | diff OddSubrectangles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address OddSubrectangles.cpp && ./a.out

/*
 
 3/4/2019
 
 10:59-11:43 give up
 
 I had no idea what I should do.
 - dp(i,j)
  - recurrence relationd is not found
 - 2d cumulative sum
  - cannot connect to # of ways
 - fix row or colum
  - cannot connect to subset of rows or columns
 
 3/7/2019
 
 15:45-17:20 read editorials
 
 3/8/2019
 
 15:18-17:00 read editorials
 
 3/9/2019
 
 18:10-18:40 got AC
 
 http://drken1215.hatenablog.com/entry/2019/02/10/024200
 https://betrue12.hateblo.jp/entry/2019/02/10/014031
 https://img.atcoder.jp/yahoo-procon2019-qual/editorial.pdf
 
 https://twitter.com/satanic0258/status/1094264168809562112
 https://twitter.com/semiexp/status/1094236696730685440
 https://twitter.com/n_vip/status/1094238057178357761
 https://twitter.com/kyopro_friends/status/1094236051881644033
 https://twitter.com/evima0/status/1094236227035750400
 https://twitter.com/beet_aizu/status/1094234574425444352
 https://twitter.com/rickytheta/status/1094239222544793602
 https://twitter.com/rickytheta/status/1094234926788927489
 https://twitter.com/rickytheta/status/1094235098612850688
 
 */
template <typename T> struct MX {
  int N,M;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
  inline vector<T>& operator [] (int i) {return dat[i]; }
  MX<T> &operator+=(MX<T> that) { dat=add(dat,that.dat); return *this; }
  MX<T> &operator-=(MX<T> that) { that*=-1,dat=add(dat,that.dat); return *this; }
  MX<T> &operator*=(MX<T> that) { dat=mult(dat,that.dat); return *this; }
  MX<T> &operator*=(T k) { dat=mult(dat,k); return *this; }
  MX<T> operator + (const MX<T> &that) const { return MX<T>(*this)+=that; }
  MX<T> operator - (const MX<T> &that) const { return MX<T>(*this)-=that; }
  MX<T> operator * (const MX<T> &that) const { return MX<T>(*this)*=that; }
  MX<T> operator * (const T &k) const { return MX<T>(*this)*=k; }
  bool operator==(MX<T> that) const { return dat==that.dat; }
  bool operator!=(MX<T> that) const { return dat!=that.dat; }
  // res = A^n, O(N^3*lg n) time
  MX<T> pow (long long n) const {
    assert(N==M);
    MX<T> res(N,N); for(int i=0; i<N; ++i) res.dat[i][i]=1;
    MX<T> a=MX<T>(*this);
    while(n>0) {
      if(n%2) res*=a;
      a*=a,n>>=1;
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const MX<T>& that) {
    for(int i=0; i<that.N; ++i) for(int j=0; j<that.M; ++j) os<<that.dat[i][j]<<",\n"[j==that.M-1];
    return os;
  }
private:
  vector<vector<T>> dat;
  // O(N^2) time
  vector<vector<T>> add(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A.size()==B.size()&&A[0].size()==B[0].size());
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=A[i][j]+B[i][j];
    return res;
  }
  // O(N^3) time
  vector<vector<T>> mult(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A[0].size()==B.size());
    int NN=A.size(),MM=B[0].size(),L=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(NN,vector<T>(MM));
    for(int i=0; i<NN; ++i) for(int j=0; j<MM; ++j) for(int k=0; k<L; ++k) res[i][j]+=A[i][k]*B[k][j];
    return res;
  }
  vector<vector<T>> mult(vector<vector<T>> &A, T k) {
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=k*A[i][j];
    return res;
  }
};
int gf2_rank(MX<int> mx) {
  int res=0;
  for(int j=0; j<mx.M; j++) {
    int pivot=-1;
    for(int i=res; i<mx.N; i++) if(mx[i][j]) {
      pivot=i;
      break;
    }
    if(pivot>=0) {
      if(pivot!=res) for(int k=0; k<mx.M; k++) swap(mx[pivot][k], mx[res][k]);
      for(int i=res+1; i<mx.N; i++) if(mx[i][j]) for(int k=0; k<mx.M; k++) mx[i][k]^=mx[res][k];
      res++;
    }
  }
  return res;
}
const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

//const int MAX_N=300+1;
VV<int> A;
int N,M;

void solve() {
  MX<int> mx(A);
  int r=gf2_rank(mx);
  ModInt res=ModInt(2).pow(N+M-1)-ModInt(2).pow(N+M-r-1);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  A=VV<int>(N,VI(M));
  REP(i,N)REP(j,M) cin>>A[i][j];
  solve();
  
  return 0;
}
