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
 
 23:05-23:17 anslysis
 23:28 got AC after 1RE fix (path compression bug)
 
 Editorials:
  - http://competitive-kivantium.hateblo.jp/entry/2016/11/26/201016
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2016-final-c/
 
 Summary:
  - I didn't have idea to reduce to bipartite graph
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,M;
VI L[MAX_N];

int G;
int uf[MAX_N];
int find(int x) { return x==uf[x]?x:uf[x]=find(uf[x]); }
void unite(int x, int y) {
  int xx=find(x),yy=find(y);
  if(xx!=yy) {
    uf[xx]=yy;
    --G;
  }
}
bool solve() {
  G=N;
  REP(i,N) uf[i]=i;
  REP(i,M) REP(j,SZ(L[i])-1) unite(L[i][j],L[i][j+1]);
//  dump(G);
//  REP(i,N)dump2(i,find(i));
  return G==1;
}

const string yes="YES",no="NO";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N) {
    int K; cin>>K;
    REP(j,K) {
      int l; cin>>l;
      L[l-1].push_back(i);
    }
  }
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
