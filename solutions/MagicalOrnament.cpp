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

// $ cp-batch MagicalOrnament | diff MagicalOrnament.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MagicalOrnament.cpp && ./a.out

/*

 1/30/2021

 4:23-5:06 AC

 https://atcoder.jp/contests/abc190/editorial/630
 https://youtu.be/VXm-9nBgQG0?t=4668

 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N],C[MAX_N];
int N,M,K;

VI G[MAX_N];
vector<pair<LL,int>> G2[20];

const LL Inf=1e16;
LL dp[1<<17][17];

bool ith(int mask, int i) { return (mask>>i)&1; }
void solve() {
  REP(i,M) {
    int a=A[i]-1,b=B[i]-1;
    G[a].push_back(b),G[b].push_back(a);
  }

  const int Inf1=1e8;
  VV<int> ds(K,VI(N,Inf1));
  queue<II> Q;
  REP(i,K) Q.emplace(C[i],i),ds[i][C[i]]=0;
  while(SZ(Q)) {
    int u,i; tie(u,i)=Q.front(),Q.pop();
    int d=ds[i][u];
    FORR(v,G[u]) if(ds[i][v]>d+1) {
      ds[i][v]=d+1,Q.emplace(v,i);
    }
  }

  REP(i,K) FOR(j,i+1,K) {
    int w=ds[i][C[j]];
    if(w>=Inf1) continue;
    G2[i].emplace_back(w,j),G2[j].emplace_back(w,i);
  }

  REP(mask,1<<K)REP(i,K) dp[mask][i]=Inf;
  REP(i,K) dp[1<<i][i]=0;
  REP(mask,1<<K) REP(i,K) if(dp[mask][i]<Inf) {
    for(auto [w,j] : G2[i]) if(!ith(mask,j)) {
      int mask2=mask|(1<<j);
      SMIN(dp[mask2][j], dp[mask][i]+w);
    }
  }

  LL res=Inf;
  REP(i,K) SMIN(res,dp[(1<<K)-1][i]);
  //REP(i,K) dump(i,dp[(1<<K)-1][i]);
  if(res>=Inf) res=-2;
  cout<<res+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) cin>>A[i]>>B[i];
  cin>>K;
  REP(i,K) cin>>C[i],C[i]--;
  solve();

  return 0;
}
