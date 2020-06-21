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
LL choose(LL n, LL k) {
  if(n<k) return 0;

  const int MAX_N = 3e6+1;
  assert(0<=k&&k<=MAX_N);
  static LL fact[MAX_N+1],revfact[MAX_N+1],rev[MAX_N+1];

  if(rev[1]==0) {
    rev[1]=1;
    for(int i=2;i<=MAX_N;i++) rev[i]=rev[MOD%i]*(MOD-MOD/i)%MOD;
    fact[0]=1,revfact[0]=1;
    for(int i=1;i<=MAX_N;i++) {
      fact[i]=fact[i-1]*i%MOD;
      revfact[i]=revfact[i-1]*rev[i]%MOD;
    }
  }
  return fact[n]*revfact[n-k]%MOD*revfact[k]%MOD;
}

// $ cp-batch Strivore | diff Strivore.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Strivore.cpp && ./a.out

/*

 6/21/2020

 5:31-6:36 AC

 https://twitter.com/hanseilimak/status/1274807244618518528
 https://img.atcoder.jp/abc171/editorial.pdf

 https://kmjp.hatenablog.jp/entry/2020/06/21/1030
 https://betrue12.hateblo.jp/entry/2020/06/21/224142

 https://twitter.com/laycrs/status/1274698687961198593
 https://twitter.com/laycrs/status/1274698727194689545
 https://twitter.com/tsutaj/status/1274698703689801729
 https://twitter.com/tsutaj/status/1274699141063438336
 https://twitter.com/satanic0258/status/1274698765710983174
 https://twitter.com/satanic0258/status/1274701660460179456
 https://twitter.com/tanakh/status/1274698626611032064
 https://twitter.com/kyopro_friends/status/1274705953099669505
 https://twitter.com/gojira_kyopro/status/1274699048344145920
 https://twitter.com/shun_skycrew/status/1274698755921436681
 https://twitter.com/tempura_cpp/status/1274701382960861185

 */

//const int MAX_N=1e6+1;
string S;
int K;

void solve() {
  int N=SZ(S);
  ModInt res=0;
  REPE(i,K) {
    res+=ModInt(26).pow(i)*ModInt(25).pow(K-i)*choose(K-i+N-1,K-i);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>K>>S;
  solve();

  return 0;
}
