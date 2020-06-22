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
LL choose(LL n, LL k) {
  if(n<k) return 0;

  const int MAX_N = 1e7+1;
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
// $ cp-batch Extension | diff Extension.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Extension.cpp && ./a.out

/*

 6/20/2020

 5:28-6:34
 7:30 give up

 6/21/2020

 15:30-17:06 read editorials and got AC

 https://twitter.com/hanseilimak/status/1274829013555412992
 https://img.atcoder.jp/agc046/editorial.pdf
 https://betrue12.hateblo.jp/entry/2020/06/21/010037
 https://ngtkana.growi.cloud/contest/agc046

 https://twitter.com/kyopro_friends/status/1274354018148446209
 https://twitter.com/armeria_betrue/status/1274351290756132870
 https://twitter.com/tsutaj/status/1274354253486673921
 https://twitter.com/tsutaj/status/1274349751727558660
 https://twitter.com/smiken_61/status/1274369874047848448
 https://twitter.com/prd_xxx/status/1274349383803273218
 https://twitter.com/n_vip/status/1274349165288361984
 https://twitter.com/snuke_/status/1274369917983195141

 */

const int MAX_N=3e3+10;
int A,B,C,D;

void solve_wrong() {
  ModInt res=0;
  int AA=C-A,BB=D-B;
  dump(AA,BB);
  REPE(x,AA) REPE(y,BB) {
    ModInt a=ModInt(B).pow(x)*choose(AA,x);
    ModInt b=ModInt(A).pow(y)*choose(BB,y);
    ModInt c=ModInt(choose(AA*BB,AA+BB-x-y));
    dump(x,y,a,b,c,a*b*c);
    res+=a*b*c;
  }
  cout<<res<<endl;
}

ModInt dp[MAX_N][MAX_N][2];
void solve() {
  dp[A][B][1]=1;
  FORE(i,A,C)FORE(j,B,D)REP(tor,2) {
    if(i==A&&j==B) continue;
    if(tor==1)dp[i][j][tor]=dp[i][j-1][1]*i+dp[i][j-1][0];
    if(tor==0)dp[i][j][tor]=(dp[i-1][j][0]+dp[i-1][j][1])*j;
  }
  //dump(dp[2][1][0],dp[2][1][1],dp[1][2][1]);
  //dump(dp[C][D][0],dp[C][D][1]);
  ModInt res=dp[C][D][0]+dp[C][D][1];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>A>>B>>C>>D;
  solve();

  return 0;
}
