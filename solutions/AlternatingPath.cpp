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

// $ cp-batch AlternatingPath | diff AlternatingPath.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AlternatingPath.cpp && ./a.out

/*
 
 1/17/2019
 
 16:29-16:53 AC
 
 https://img.atcoder.jp/aising2019/editorial.pdf
 https://betrue12.hateblo.jp/entry/2019/01/13/030527
 
 */

const int MAX_N=2e5+1;
VI G[MAX_N];
int H,W;

string S[401];

int viz[MAX_N];

// grid move (clock wise order)
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };

int cnt[2];
void dfs(int u, int col) {
  if(viz[u]) return;
  viz[u]=1;
  cnt[col]++;
  FORR(v,G[u]) dfs(v,col^1);
}
void solve() {
  REP(i,H)REP(j,W) if(S[i][j]=='#') {
    // snippet of board move
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=H||jj<0||jj>=W) continue;
      if(S[ii][jj]=='.') {
        G[i*W+j].push_back(ii*W+jj);
        G[ii*W+jj].push_back(i*W+j);
      }
    }
  }
  LL res=0;
  REP(i,H)REP(j,W) if(S[i][j]=='#'&&!viz[i*W+j]) {
    ZERO(cnt);
    dfs(i*W+j,0);
    res+=cnt[0]*cnt[1];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>H>>W;
  REP(i,H) cin>>S[i];
  solve();
  
  return 0;
}
