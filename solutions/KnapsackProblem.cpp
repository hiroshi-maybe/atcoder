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

// $ cp-batch KnapsackProblem | diff KnapsackProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KnapsackProblem.cpp && ./a.out

/*
 
 10/12/2019
 
 21:31-21:58 AC
 
 */

const int MAX_N=100+1;
LL A[MAX_N],B[MAX_N],C[MAX_N];
int N,M,W;

int uf[MAX_N];
int find(int u) { return uf[u]==u?u:uf[u]=find(uf[u]); }
void unite(int u, int v) {
  u=find(u),v=find(v);
  uf[u]=v;
}
int dp[MAX_N][10101];
void solve() {
//  VI xs;
  map<int,VI> ids;
  REP(i,N) ids[find(i)].push_back(i);
  VV<int> ys;
  FORR(kvp,ids) ys.push_back(kvp.second);
  int Z=SZ(ys);
  VI ws(Z),vs(Z);
  REP(i,Z) {
    REP(j,SZ(ys[i])) ws[i]+=B[ys[i][j]],vs[i]+=C[ys[i][j]];
  }
  ZERO(dp);
  REP(i,Z) REPE(w,W) {
    SMAX(dp[i+1][w],dp[i][w]);
    if(w+ws[i]<=W)SMAX(dp[i+1][w+ws[i]],dp[i][w]+vs[i]);
  }
  int res=0;
  REPE(w,W)SMAX(res,dp[Z][w]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>W;
  REP(i,N) uf[i]=i,cin>>B[i]>>C[i];
  
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    unite(u,v);
  }
  solve();
  
  return 0;
}
