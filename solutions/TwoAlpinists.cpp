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
const int MOD=1000000007;
//const int MOD=998244353;
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
// $ cp-batch TwoAlpinists | diff TwoAlpinists.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoAlpinists.cpp && ./a.out

/*
 
 8/12/2018
 
 15:25-15:42 got AC
 
 Editorials:
  - http://code-festival-2016-qualc.contest.atcoder.jp/data/other/code-festival-2016-qualc/editorial.pdf
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2016-qualc-c/
  - http://hamko.hatenadiary.jp/entry/2017/07/28/110610
  - https://ykmaku.hatenablog.com/entry/2018/07/15/223228
  - http://competitive-kivantium.hateblo.jp/entry/2016/10/24/135521

  5/14/2020

  21:25-21:41 solve again
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],T[MAX_N],L[2][MAX_N],R[2][MAX_N];
int N;

void solve() {
  REP(i,N) {
    if(i==0||T[i-1]!=T[i]) L[0][i]=R[0][i]=T[i];
    else L[0][i]=1,R[0][i]=T[i];
  }
  for(int i=N-1; i>=0; --i) {
    if(i==N-1||A[i]!=A[i+1]) L[1][i]=R[1][i]=A[i];
    else L[1][i]=1,R[1][i]=A[i];
  }

  ModInt res=1;
  REP(i,N) {
    LL l=max(L[0][i],L[1][i]),r=min(R[0][i],R[1][i]);
    //dump(i,L[0][i],R[0][i],L[1][i],R[1][i],l,r,r-l);
    res*=max(0LL,r-l+1);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>T[i];
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
