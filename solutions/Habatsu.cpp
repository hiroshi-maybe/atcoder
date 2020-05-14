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

int maxIndependentSet(vector<vector<int>> &G) {
  auto ztrans=[&](vector<int> &dp, int N) {
    for(int i=0; i<N; ++i) for(int mask=0; mask<(1<<N); ++mask) {
      if(mask&(1<<i)) dp[mask]&=dp[mask^(1<<i)];
    }
  };
  auto independentset=[&](int l, int r)->vector<int> {
    vector<int> dp(1<<(r-l),1);
    for(int u=l; u<r; ++u) for(auto v : G[u]) if(l<=v&&v<r) {
      dp[(1<<(u-l))|(1<<(v-l))]=false;
    }
    ztrans(dp,r-l);
    for(int mask=0; mask<(1<<(r-l)); ++mask) dp[mask]=dp[mask]?__builtin_popcount(mask):0;
    return dp;
  };
  
  int V=G.size();
  int V1=V/2,V2=V-V1;
  vector<int> fr(1<<V1,(1<<V2)-1);
  vector<int> dp1=independentset(0,V1);
  vector<int> dp2=independentset(V1,V);
  
  for(int u=0; u<V1; ++u) for(auto v : G[u]) if(v>=V1) {
    fr[1<<u]&=((1<<V2)-1)^(1<<(v-V1));
  }
  ztrans(fr,V1);
  
  for(int mask=0; mask<(1<<V2); ++mask) for(int i=0; i<V2; ++i) {
    if((mask&(1<<i))==0) dp2[mask|(1<<i)]=max(dp2[mask|(1<<i)],dp2[mask]);
  }
  int res=0;
  for(int mask=0; mask<(1<<V1); ++mask) {
    res=max(res,dp1[mask]+dp2[fr[mask]]);
  }
  return res;
}

// $ cp-batch Habatsu | diff Habatsu.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Habatsu.cpp && ./a.out

/*
 
 5/14/2020
 
 9:43-10:00 AC

 https://www.slideshare.net/chokudai/abc002
 
 */

int N,M;
VV<int> G;

void solve() {
  VV<int> GG(N);
  REP(u,N)REP(v,N)if(u!=v&&count(ALL(G[u]),v)==0) {
    GG[u].push_back(v);
  }
  cout<<maxIndependentSet(GG)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  G=VV<int>(N);
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();
  
  return 0;
}
