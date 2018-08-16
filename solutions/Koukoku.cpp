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
 
 8/15/2018
 
 18:05-18:10 analysis
 18:12 I got 2WAs
 18:31 OK below test case does not pass
 
 3 6
 *.**.*
 ......
 *.**.*

 => 7 is optimal
 
 19:30-20:03 resubmit and got another WA. Gave up.
 
 22:00-23:22 read editorials and implement. Got RE
 23:25 fixed bug of matching size initialization and got AC
 
 Editorials:
  - https://img.atcoder.jp/soundhound2018/editorial.pdf
  - http://ferin-tech.hatenablog.com/entry/2018/01/28/004856
  - https://www.hamayanhamayan.com/entry/2018/01/28/172047
  - http://hamko.hatenadiary.jp/entry/2018/01/27/223035
  - http://tutuz.hateblo.jp/entry/2018/08/15/213658
 
 If I try to classify vertices into parity with (mod 2), it may be reduced to bipartite graph.
 It's equal to 2-coloring problem.
 If it's bipartite graph, we may leverage flow in below aspects:
  - Matching can be solved by max-flow algorithm in polynomial time
  - Maximum independent set = V - maximum matching
    (number of vertices part of matching + extra vertices = maximum independent set)
 
 References:
  - https://qiita.com/drken/items/7f98315b56c95a6181a4
 
 Summary:
  - I should have come up with bipartite graph from grid and parity...
  - Remembering by coloring problem equal to maximum independent set is easier for me 😛
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=40+1;
int R,C;
char mx[MAX_N][MAX_N];
int viz[MAX_N][MAX_N];
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
void dfs(int r, int c, set<II> &S) {
  if(viz[r][c]||mx[r][c]=='*') return;
  viz[r][c]=true;
  S.emplace(r,c);
  FORR(m,moves) {
    int rr=r+m.first,cc=c+m.second;
    if(rr<0||rr>=R||cc<0||cc>=C) continue;
    dfs(rr,cc,S);
  }
}

int cnt[2];
int viz2[MAX_N][MAX_N];
void dfs2(int r, int c, set<II> &S) {
  if(viz2[r][c]||S.count({r,c})==0) return;
  viz2[r][c]=true;
  cnt[(r+c)%2]++;
  FORR(m,moves) {
    int rr=r+m.first,cc=c+m.second;
    if(rr<0||rr>=R||cc<0||cc>=C) continue;
    dfs2(rr,cc,S);
  }
}

void solve_wrong() {
  int res=0;
  REP(i,R)REP(j,C)if(mx[i][j]=='.'&&!viz[i][j]) {
    ZERO(cnt);
    set<II> S;
    dfs(i,j,S);
    
    ZERO(cnt); ZERO(viz2);
    assert(SZ(S));
    II p=*S.begin();
    dfs2(p.first,p.second,S);
    int s=max(cnt[0],cnt[1]);
    vector<II> SS(S.begin(),S.end());
    REP(i,SZ(SS)) {
      S.erase(SS[i]);
      ZERO(viz2);
      int t=0;
      FORR(p,S) if(!viz2[p.first][p.second]) {
        ZERO(cnt);
        dfs2(p.first,p.second,S);
        t+=max(cnt[0],cnt[1]);
      }
      
      SMAX(s,t);
      S.emplace(SS[i]);
    }
    res+=s;
  }
  cout<<res<<endl;
}

const int MAX_V=1600;
class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {}
  
  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  int match[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

vector< pair < int, int > >  moves2 = { {0,1}/*R*/,{1,0}/*D*/};
MaxBipartiteMatching BM(MAX_N*MAX_N);
void makeG(int r, int c) {
  if(viz[r][c]||mx[r][c]=='*') return;
  viz[r][c]=true;
  FORR(m,moves2) {
    int rr=r+m.first,cc=c+m.second;
    if(rr<0||rr>=R||cc<0||cc>=C||mx[rr][cc]=='*') continue;
    BM.addEdge(r*C+c,rr*C+cc);
    makeG(rr,cc);
  }
}

void solve() {
  REP(i,R)REP(j,C) if(mx[i][j]=='.') {
    FORR(m,moves2) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=R||jj<0||jj>=C||mx[ii][jj]=='*') continue;
      BM.addEdge(i*C+j,ii*C+jj);
    }
  }
  int maxm=BM.solve();
  int V=0;
  REP(i,R)REP(j,C)V+=mx[i][j]=='.';
  cout<<V-maxm<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>R>>C;
  REP(i,R)REP(j,C) cin>>mx[i][j];
  solve();
  return 0;
}
