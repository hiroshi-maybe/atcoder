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

// $ cp-batch XorDistances | diff XorDistances.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XorDistances.cpp && ./a.out

/*

 5/16/2021

 12:31-14:13 TLE
 14:35 AC

 https://youtu.be/Wx6020jI4NM?t=2786
 https://atcoder.jp/contests/abc201/editorial/1827

 Add solution in the official editorial.

 */

const int MAX_N=2e5+1;
int N;
vector<pair<LL,int>> G[MAX_N];

LL ans=0;
int ith(LL mask, int i) { return (mask>>i)&1; }

LL ff(int b) {
  vector<LL> cnt(2);
  auto dfs=[&](auto &&self, int u, int parent, int parity) ->void {
    cnt[parity]++;
    FORR(p,G[u]) {
      LL w; int v; tie(w,v)=p;
      if(v==parent) continue;
      int pp=ith(w,b);
      self(self,v,u,parity^pp);
    }
  };

  dfs(dfs,0,-1,0);

  return cnt[0]*cnt[1];
}

vector<LL> dfs(int bit, int u, int parent) {
  VV<LL> xs;
  FORR(p,G[u]) {
    LL w; int v; tie(w,v)=p;
    if(v==parent) continue;
    auto child=dfs(bit, v, u);

    int pp=ith(w,bit);
    xs.push_back({0,0});
    REP(x,2) xs.back()[x^pp]+=child[x];
  }

  vector<LL> tot(2);
  FORR(x,xs) REP(b,2) tot[b]+=x[b];

/*
  dump(bit,u);
  FORR(x,xs) {
    dump(bit,u,x[0],x[1]);
  }
*/

  FORR(x,xs) {
    ans+=x[1];
    ans+=x[1]*(tot[0]-x[0]);
  }

  vector<LL> res(2);
  res[0]=1;
  REP(b,2) res[b]+=tot[b];
  return res;
}

LL f(int b) {
  ans=0;
  dfs(b,0,-1);
  return ans;
}

void solve() {
  ModInt res=0;
  REP(i,60) {
    auto cnt=ff(i);
    res+=ModInt(1LL<<i)*cnt;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N-1) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    G[u].emplace_back(w,v),G[v].emplace_back(w,u);
  }
  solve();

  return 0;
}
