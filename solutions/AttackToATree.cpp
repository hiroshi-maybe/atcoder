#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch AttackToATree | diff AttackToATree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AttackToATree.cpp && ./a.out

/*
 
 1/17/2019
 
 18:51-19:51 give up
 
 1/18/2019
 
 16:56-21:18 after reading tons of editorials, got AC
 
 https://img.atcoder.jp/aising2019/editorial.pdf
 http://ferin-tech.hatenablog.com/entry/2019/01/13/011705
 http://drken1215.hatenablog.com/entry/2019/01/13/024000
 http://kmjp.hatenablog.jp/entry/2019/01/13/1000
 https://betrue12.hateblo.jp/entry/2019/01/13/030527
 
 https://atcoder.jp/contests/aising2019/submissions/3996371
  - Clean implementation by @betrue12
 
 Result is upper-bounded by N. Add it to dp parameter.
 
 It's hard to keep `dp[u][cost]`=res in state because cost<=1e13.
 Have `dp[u][res]`=min cost instead.
 
 Key:
  - transpose key-val in dp recurrence relation
  - O(N^2) tree dp by children merge
   - https://topcoder.g.hatena.ne.jp/iwiwi/20120428/1335635594
 
 */

const int MAX_N=5e3+1;
LL A[MAX_N];
VI G[MAX_N];
int N;

const LL Inf=1e13;

LL dp[MAX_N][MAX_N][2];
int cnt[MAX_N];

void dfs(int u, int pre) {
//  dump(u);
  cnt[u]=1;
  if(A[u]>0) dp[u][0][0]=A[u];
  dp[u][0][1]=A[u];
  FORR(v,G[u]) if(v!=pre) {
    dfs(v,u);
    int M=cnt[u]+cnt[v];
    VV<LL> dp2(M+1,vector<LL>(2,Inf));
    REP(i,cnt[u])REP(j,cnt[v])REP(k,2)REP(l,2) {
      // no-cut
      SMIN(dp2[i+j][k|l],dp[u][i][k]+dp[v][j][l]);
      
      // cut
      if(l==0&&dp[v][j][l]<Inf) SMIN(dp2[i+j+1][k],dp[u][i][k]);
      if(l==1&&dp[v][j][l]<0) SMIN(dp2[i+j+1][k],dp[u][i][k]);
    }
    REPE(i,M)REP(j,2) dp[u][i][j]=dp2[i][j];
    cnt[u]=M;
  }
}

void solve() {
  REP(i,MAX_N)REP(j,MAX_N)REP(k,2)dp[i][j][k]=Inf;
  dfs(0,-1);
  int res=MAX_N;
  REP(i,N) {
    if(dp[0][i][0]<Inf) res=i;
    if(dp[0][i][1]<0) res=i;
//    dump3(i,dp[0][i][0],dp[0][i][1]);
    if(res<MAX_N) break;
  }
  cout<<res<<endl;
}

/*
LL dpsum[MAX_N][MAX_N];
int dppos[MAX_N][MAX_N];
LL memo[MAX_N][MAX_N];

void prep(int u, int pre) {
  int &allpos=dppos[u][pre];
  if(allpos>=0) return;
  allpos=A[u]>0;
  LL sum=0;
  FORR(v,G[u]) if(v!=pre) {
    prep(v,u);
    sum+=dpsum[v][u];
    allpos&=dppos[v][u];
  }
  dpsum[u][pre]=sum;
  dppos[u][pre]=allpos;
}

LL f(int u, int pre) {
  LL &res=memo[u][pre];
  if(res>=0) return res;
  if(dppos[u][pre]) return 0;
  if(dpsum[u][pre]<0) return 0;
  res=SZ(G[u])-1;
  LL tot=0;
  FORR(v,G[u])if(v!=pre) tot+=f(v,u);
  FORR(v,G[u])if(v!=pre) {
    LL a=f(v,u);
    LL x=tot-a;
    if(dppos[v][u]&&A[u]>0)
  }
}

void solve() {
  int res=MAX_N;
  MINUS(dpsum),MINUS(dppos),MINUS(memo);
  REP(i,N-1) {
    int u=E[i].first,v=E[i].second;
    prep(u,v);
    prep(v,u);
    if(dppos[u][v]&&dppos[v][u]) res=0;
    if(dpsum[u][v]<0&&dpsum[v][u]<0) res=0;
    SMIN(res,1LL+f(u,v)+f(v,u));
  }
  cout<<res<<endl;
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
//    E[i]={u,v};
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
