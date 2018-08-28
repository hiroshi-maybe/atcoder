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
 
 8/27/2018
 
 15:55-16:24 submit and got AC
 
 Editorials:
  - https://img.atcoder.jp/mujin-pc-2018/editorial.pdf
  - https://youtu.be/2ZfEcgV8Sso?t=2633
  - http://betrue12.hateblo.jp/entry/2018/08/05/032043
  - https://kimiyuki.net/writeup/algo/atcoder/mujin-pc-2018-d/
  - https://www.hamayanhamayan.com/entry/2018/08/05/092606
  - http://hamko.hatenadiary.jp/entry/2018/08/05/011642
  - https://31536000.hatenablog.com/entry/2018/08/05/002002
  - http://xxxasdfghjk999.hatenablog.jp/entry/2018/08/05/001828
  - http://d.hatena.ne.jp/merom686/20180804/1533397455
  - http://tutuz.hateblo.jp/entry/2018/08/05/130334
 
 Beautiful implementations:
  - https://mujin-pc-2018.contest.atcoder.jp/submissions/2943150 by @IH19980412
  - https://mujin-pc-2018.contest.atcoder.jp/submissions/2943393 by @kmjp
 
 Add code with reverse edge.
 
 Summary:
  - I haven't imagined backward graph...
  - If last state is obvious, starting dfs from it seems to be easier. Nice to learn.
  - rev(999)<1000. Thus tight bound is 1000 rather than 2000
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e3+1;
int N,M;
int F[MAX_N][MAX_N];
int viz[MAX_N][MAX_N];

int rev(int x) {
  string s=to_string(x);
  reverse(s.begin(),s.end());
  int res=0;
  REP(i,SZ(s)) {
    res=10*res+s[i]-'0';
  }
  return res;
}

II f(int x, int y) {
  if(x<y) x=rev(x);
  else y=rev(y);
  if(x<y) return {x,y-x};
  else return {x-y,y};
}

int dfs(int x, int y) {
  if(viz[x][y]==2) return F[x][y];
  if(viz[x][y]==1) return true;
  viz[x][y]=1;
  if(x==0||y==0) {
    viz[x][y]=2;
    return F[x][y]=false;
  }
  
  int xx,yy; tie(xx,yy)=f(x,y);
  F[x][y]=dfs(xx,yy);
  viz[x][y]=2;
  return F[x][y];
}

void solve_org() {
  ZERO(viz),ZERO(F);
  int res=0;
  FORE(i,1,N)FORE(j,1,M) res+=dfs(i,j);
  cout<<res<<endl;
}

vector<II> E[MAX_N][MAX_N];

void dfsdfs(int x, int y) {
  if(viz[x][y]) return;
  viz[x][y]=1;
  FORR(p,E[x][y]) dfsdfs(p.first,p.second);
}

void solve() {
  ZERO(viz);
  
  FORE(x,1,999)FORE(y,1,999) {
    int xx,yy; tie(xx,yy)=f(x,y);
    if(xx==0||yy==0) E[0][0].emplace_back(x,y);
    else E[xx][yy].emplace_back(x,y);
  }
  dfsdfs(0,0);
  int res=0;
  FORE(i,1,N)FORE(j,1,M) res+=!viz[i][j];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  solve();
  return 0;
}
