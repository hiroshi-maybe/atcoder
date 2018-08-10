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
 
 8/9/2018
 
 15:45-15:53 AC
 
 Editorials:
  - https://atcoder.jp/img/abc073/editorial.pdf
  - https://youtu.be/7ctPpofZdJ4?t=2173
  - https://www.hamayanhamayan.com/entry/2017/09/10/002511
  - http://ymduu.hatenablog.com/entry/2018/05/04/231945
  - http://nocotan.github.io/%E7%AB%B6%E6%8A%80%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0/2017/09/09/abc073-copy.html
  - http://tutuz.hateblo.jp/entry/2018/06/08/212225
  - http://kazune-lab.net/contest/2017/09/09/abc073/#d---joisinos-travel
  - https://freestylewiki.xyz/fswiki/wiki.cgi?page=AtCoder+Beginner+Contest+073
  - http://www.geocities.jp/oraclesqlpuzzle/kyoupro/kyoupro-08-073-d.html
 
 Key:
  - All pairs shortest path + permutation
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const LL Inf=1e15;
const int MAX_N=200+1;
int V,M,R;
LL mx[MAX_N][MAX_N];
int rs[8];

void solve() {
  REP(k,V)REP(i,V)REP(j,V) SMIN(mx[i][j],mx[i][k]+mx[k][j]);
  VI P(R);REP(i,R)P[i]=i;
  LL res=Inf;
  do {
    LL d=0;
    REP(i,R-1) {
      int u=rs[P[i]],v=rs[P[i+1]];
      d+=mx[u][v];
    }
    SMIN(res,d);
  } while(next_permutation(P.begin(),P.end()));
  
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>V>>M>>R;
  
  REP(i,V)REP(j,V)mx[i][j]=i==j?0:Inf;
  
  REP(i,R) cin>>rs[i],rs[i]--;
  REP(i,M) {
    int u,v; LL d; cin>>u>>v>>d;
    --u,--v;
    mx[u][v]=mx[v][u]=d;
  }
  solve();
  return 0;
}
