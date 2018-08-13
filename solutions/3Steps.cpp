#include <iostream>
#include <iomanip>
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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 2018/8/12
 
 14:00-14:39 analysis
 14:40-15:18 design data structure, implement and got AC
 
 I came up with an idea to group by (MOD 4) or (MOD 2) in 20 mins.
 However it took some time to reduce to generic algorithm.
 It would have been more straighforward if I knew property of bipartite graph in terms of parity.
 
 Editorials:
  - https://img.atcoder.jp/code-festival-2017-qualb/editorial.pdf
  - http://ronly.hatenablog.com/entry/2017/10/15/134854
  - http://kmjp.hatenablog.jp/entry/2017/10/09/0900
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2017-qualb-c/
 
 Summary:
  - I didn't know about relation between bipartite graph, parity and cycle. It's nice to learn.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,M;
SETI E[MAX_N];
SETI P[2];

void dfs(int u, int par) {
  if(P[par].count(u)) return;
  P[par].emplace(u);
  FORR(v,E[u]) dfs(v,par^1);
}

void solve() {
  dfs(0,0);
  LL both=0;
  REP(i,N) both+=P[0].count(i)&&P[1].count(i);
  
  LL res=0;
  REP(u,N) {
    bool g0=P[0].count(u),g1=P[1].count(u);
    if(g0&&!g1) res+=SZ(P[1])-SZ(E[u]);
    if(g1&&!g0) res+=SZ(P[0])-SZ(E[u]);
    if(g0&&g1) {
      res+=both-1-SZ(E[u]);
    }
/*
    REP(p,2) if(P[p].count(u)) {
      cnt[p]=SZ(P[p^1])-SZ(E[u]);
    }
    if(P[0].count(u)&&P[1].count(u)) cnt[2]+=both-1-SZ(E[u]);
    dump4(u,cnt[0],cnt[1],cnt[2]);*/
  }
//  LL res=cnt[0]+cnt[1]-cnt[2];
  res/=2;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    E[u].emplace(v);
    E[v].emplace(u);
  }
  solve();
  return 0;
}
