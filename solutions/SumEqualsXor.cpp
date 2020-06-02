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

// $ cp-batch SumEqualsXor | diff SumEqualsXor.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SumEqualsXor.cpp && ./a.out

/*

 6/9/2019

 5:40-6:40 give up
 10:10-11:30 add solution by @tempura_cpp's approach 2^p*3^s
 13:00-14:15 add normal digit dp solution

 http://kmjp.hatenablog.jp/entry/2019/06/09/0900
 https://twitter.com/tempura_cpp/status/1137717647137619969
 https://twitter.com/tempura_cpp/status/1137720691095040001
 https://twitter.com/kzyKT_M/status/1137717249844817920
 https://twitter.com/hamko_intel/status/1137718170024697856
 This was the way that I was looking for.
 What I didn't come up with is 3^(length of suffix) part, which is enumeration of all the subsets.

 Normal digit dp
 https://twitter.com/D_A_works/status/1137718215965007874
 https://twitter.com/torus711/status/1137718180904701952
 https://twitter.com/satanic0258/status/1137717004394045442

 6/1/2020

 9:34-9:58 solve again by digit dp

 */

const int MAX_N=1e6+1;
string L;

void solve() {
  int N=SZ(L);
  ModInt res=0;
  int cnt1=0;
  REP(i,N) if(L[i]=='1') {
    res+=ModInt(2).pow(cnt1)*ModInt(3).pow(N-i-1);
    ++cnt1;
  }
  res+=ModInt(2).pow(cnt1);
  cout<<res<<endl;
}

ModInt dp[MAX_N][2];
void solve_digitdp() {
  int N=SZ(L);
  dp[0][0]=1;
  REP(i,N) REP(less,2) {
    int d=L[i]-'0';
    int lb=0,hb=!less?d:1;
    FORE(dd,lb,hb) dp[i+1][less|(dd<d)]+=dp[i][less]*(dd==0?1:2);
  }
  cout<<dp[N][0]+dp[N][1]<<endl;
}

void solve_digitdp_org() {
  ZERO(dp);
  int N=SZ(L);
  dp[0][0]=1;
  REP(i,N) {
    if(L[i]=='1') {
      // j=0
      dp[i+1][1]+=dp[i][0];
      dp[i+1][0]+=dp[i][0]*2;

      // j=1
      dp[i+1][1]+=dp[i][1]*3;
    } else {
      // j=0
      dp[i+1][0]+=dp[i][0];
      // j=1
      dp[i+1][1]+=dp[i][1]*3;
    }
  }
  cout<<dp[N][0]+dp[N][1]<<endl;
}

int cum[MAX_N];
void solve_combinatorics_org() {
  int N=SZ(L);
  REP(i,N) cum[i+1]=cum[i]+(L[i]=='1');
  ModInt res;
  REP(i,N)if(L[i]=='1') {
    int p=cum[i],s=N-(i+1);
    res+=ModInt(2).pow(p)*ModInt(3).pow(s);
  }
  res+=ModInt(2).pow(cum[N]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>L;
  solve();

  return 0;
}
