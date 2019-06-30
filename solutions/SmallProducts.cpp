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
// $ cp-batch SmallProducts | diff SmallProducts.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SmallProducts.cpp && ./a.out

/*
 
 6/29/2019
 
 6:02-6:40 give up
 
 6/30/2019
 
 14:47-16:07 read editorials and got AC
 
 https://img.atcoder.jp/abc132/editorial.pdf
 https://kenkoooo.hatenablog.com/entry/2019/06/29/225436
 http://drken1215.hatenablog.com/entry/2019/06/29/224100_1
 http://kmjp.hatenablog.jp/entry/2019/06/29/1100
 https://twitter.com/satanic0258/status/1144964145537699840
 https://twitter.com/tanakh/status/1144966718898360321
 https://twitter.com/satanic0258/status/1144966599108993024
 https://twitter.com/a3VtYQo/status/1144965341522477057
 https://twitter.com/_primenumber/status/1144964837782376449
 https://twitter.com/DEGwer3456/status/1144965267434307584
 https://twitter.com/xuzijian629/status/1144965234219556864
 https://twitter.com/hamko_intel/status/1144967727762694144
 
 From formula p*q<=N, we can iterate p for {1,..,sqrt(N)}
 
 G={{0,0}, {1,N}, {2,N/2}, .., {sqrt(N),N/sart(N)}, .., {N/2,2},{N,1}}
 
 dp[0][g] = G[g].first-G[g-1].first
 dp[i][g] = ∑ dp[i-1][0..group(G[g].second)] * (G[g].first-G[g-1].first)
 
 res = ∑ dp[K-1][0..SZ(G)-1]
 
 */

const int MAX_G=70000;
const int MAX_K=100+1;
LL N;
int K;

ModInt cum[MAX_G];
ModInt dp[MAX_K][MAX_G];
void solve() {
  vector<II> G(1,{0,0});
  for(int p=1; p*p<=N; ++p) {
    int q=N/p;
    G.emplace_back(p,q);
    if(p!=q) G.emplace_back(q,N/q);
  }
  sort(ALL(G));
  map<int,int> gid;
  int M=SZ(G);
  REP(i,M) gid[G[i].first]=i;
  FOR(i,1,M) dp[0][i]=G[i].first-G[i-1].first;
  REP(i,M) cum[i+1]=cum[i]+dp[0][i];
  FOR(i,1,K) {
    FOR(g,1,M) {
      auto p=G[g];
      int gg=gid[p.second];
      dp[i][g]=cum[gg+1]*(p.first-G[g-1].first);
    }
    REP(g,M) cum[g+1]=cum[g]+dp[i][g];
  }
  cout<<cum[M]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  solve();
  
  return 0;
}
