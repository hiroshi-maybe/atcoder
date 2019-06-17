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
// $ cp-batch CommonSubsequence | diff CommonSubsequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CommonSubsequence.cpp && ./a.out

/*
 
 6/16/2019
 
 5:23-6:40 give up
 
 My original dp formula: dp[i][j]=dp[i-1][j-1]+(S[i]==T[j])
 
 There are two mistakes in this formula.
 
 1. +(S[i]==T[j]) part
 In LCS, we are adding `1` because it's computing longest LENGTH.
 However, we are counting # of subsequence. It does NOT make sense to add `1` at all 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 2. Inconsistency of state of dp[i][j]
 
 dp[i][j] in above formula is just counting # of subsequences which ends by S[i-1](=T[j-1]). It's missing existing subsequences in dp[i-1][j] and dp[i][j-1].
 
 From those two points, obviously code doesn't pass samples.
 I was trying to accumulate cumulative sum for S[i-1] and T[j-1].
 This is totally wrong too. Matching of S[i-1] and T[x<j-1] should be already computed in dp[i][j-1] if my state definition is computed. Very stupid.
 
 8:30-9:00 I figured out to remove "+1" part 😞
 
 15:00-17:50 read editorials
 
 https://img.atcoder.jp/abc130/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/06/17/0930
 https://twitter.com/tempura_cpp/status/1140275743902990338
 https://twitter.com/kuuso1/status/1140258859455434757
 https://twitter.com/tanakh/status/1140256316792791040
 https://twitter.com/torus711/status/1140254350687649792
 https://twitter.com/hamko_intel/status/1140255573360799746
 
 */

const int MAX_V=1e5+10;
const int MAX_N=2e3+10;
int A[MAX_N],B[MAX_N];
int N,M;

ModInt dp[MAX_N][MAX_N],sum[MAX_N][MAX_N];
void solve() {
  ZERO(sum);
  sum[0][0]=1;
  REPE(i,N)sum[i][0]=1;
  REPE(j,M)sum[0][j]=1;
  REP(i,N)REP(j,M) {
    ModInt x=0;
    if(A[i]==B[j]) x=sum[i][j];
    sum[i+1][j+1]=sum[i+1][j]+sum[i][j+1]-sum[i][j]+x;
//    dump(i,j,A[i]==B[j],x,sum[i+1][j+1],sum[i+1][j],sum[i][j+1],sum[i][j]);
  }
  cout<<sum[N][M]<<endl;
}

void solve_org() {
  ZERO(dp);
  dp[0][0]=1;
  REPE(i,N) dp[i][0]=1;
  REPE(j,M) dp[0][j]=1;
  FORE(i,1,N) {
    FORE(j,1,M) {
      if(A[i-1]==B[j-1]) dp[i][j]=dp[i-1][j-1];
      dp[i][j]+=dp[i-1][j]+dp[i][j-1];
      dp[i][j]-=dp[i-1][j-1];
    }
  }
  cout<<dp[N][M]<<endl;
}

void solve_wrong() {
  ZERO(dp);
  
  map<int,map<int,ModInt>> cumA;
  REP(i,MAX_V) cumA[i][0]=1;
  map<int,map<int,ModInt>> cumB;
  REP(i,MAX_V) cumB[i][0]=1;
  dp[0][0]=1;
  FORE(i,1,N) {
    int a=A[i-1];
    FORE(j,1,M) {
      int b=B[j-1];
      dp[i][j]=cumA[b][j]+cumB[a][i];
//      if(a==b) dp[i][j]+=dp[i-1];
      cumA[b][j]+=dp[i][j];
      cumB[a][i]+=dp[i][j];
    }
  }
  cout<<dp[N][M]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  REP(i,M) cin>>B[i];
  solve();
  
  return 0;
}
