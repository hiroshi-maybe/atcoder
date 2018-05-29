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
 
 5/12/2018 AtCoder Beginner Contest 097
 
 21:42-22:30 time up
 
 5/29/2018
 
 10:10-11:00,13:30-15:30 read editorial and add solution
 
 Editorials:
  - https://img.atcoder.jp/arc097/editorial.pdf
  - https://youtu.be/5PLS2J4cVmY?t=2641
  - http://yosupo.hatenablog.com/entry/2018/05/12/224611
 
 Tweets:
  - https://togetter.com/li/1226806
  - https://twitter.com/ei1333/status/995297781127393281
  - https://twitter.com/rickytheta/status/995297864891883520
  - https://twitter.com/nebukuro09/status/995298279305887744
  - https://twitter.com/_TTJR_/status/995300715328241664
 
 Submit solutions:
  - https://beta.atcoder.jp/contests/arc097/submissions/2498127 by @sugim48
  - https://beta.atcoder.jp/contests/arc097/submissions/2502752 by @yosupot
 
 Pre-computation of cost between B and W:
 
 BW[a][b] : how many elements of W_0..W_(b-1) is in right side of B[a]?
 
 Iterate from left to right. +1 if pos(B_a) < pos(W_i) where i=0..b-1. This is O(N^3) algorithm.
 We can optimize it to O(N^2) by recurrence relation BW[a][b+1]=BW[a][b] + pos(B_a)<pos(W_b)
 
 Key:
  - Variable final sequence can happen. It's hard to say what is optimal. That means some search is necessary.
  - If i blacks and j whites are put in left, the order in it does not matter -> DP
  - Inversion shows how many times swap needs. That can be pre-computed.
  - Precomputation is possible by optimization of naiive comparison algorithm
 
 Summary:
  - Greedy approach is not clear and in stuck -> Brute-force including DP
  - "Inversion is cross of moves" in editorial video. This is easy to understand inversion.
  - It was very tough for me to even pre-compute 2 dimension inversion. sigh... 😞😞😞😞
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2000;
int N;
VI W,B;

vector<VI> f(VI &a, VI &b) {
  vector<VI> res(N,VI(N+1,0));
  REP(n,N)REP(m,N) res[n][m+1]=res[n][m]+(a[n]<b[m]);
  return res;
}

const int Inf=10*MAX_N*MAX_N;
int dp[MAX_N+5][MAX_N+5];
LL solve() {
  vector<VI> WW=f(W,W),WB=f(W,B),BW=f(B,W),BB=f(B,B);
  REPE(i,N)REPE(j,N) dp[i][j]=Inf;
  dp[0][0]=0;
  REPE(i,N)REPE(j,N) {
//    dump2(i,j);
    if(i<N)SMIN(dp[i+1][j],dp[i][j]+WW[i][i]+WB[i][j]);
    if(j<N)SMIN(dp[i][j+1],dp[i][j]+BB[j][j]+BW[j][i]);
  }
  return dp[N][N];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  W=VI(N),B=VI(N);
  REP(i,2*N) {
    char c; int x;
    cin>>c>>x;
    (c=='W'?W:B)[--x]=i;
  }
  cout<<solve()<<endl;
  return 0;
}
