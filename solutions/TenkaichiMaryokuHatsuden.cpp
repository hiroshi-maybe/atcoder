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
 
 8/20/2018
 
 17:20-17:34 analysis
 17:35-17:46 implement and got AC
 
 Editorial:
  - https://tenka1-2016-qualb.contest.atcoder.jp/data/other/tenka1-2016-qualb/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2016/08/29/170808
  - https://ei1333.hateblo.jp/entry/2016/08/28/112119
  - http://mmxsrup.hatenablog.com/entry/2016/08/28/004727
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e2+1;
string S;
int dp[MAX_N][MAX_N][MAX_N];
const int Inf=1e8;
void solve() {
  int N=SZ(S);
  REPE(i,N)REPE(j,N)REPE(k,N) dp[i][j][k]=Inf;
  dp[0][0][0]=0;
  REP(i,N)REP(d,N)REPE(pre,i) {
//    dump4(i,d,pre,dp[i][d][pre]);
    if(S[i]=='(') {
      SMIN(dp[i+1][d+1][pre],dp[i][d][pre]);
      if(d>0) SMIN(dp[i+1][d-1][i],dp[i][d][pre]+1+i-pre);
    } else {
      if(d>0) SMIN(dp[i+1][d-1][pre],dp[i][d][pre]);
      SMIN(dp[i+1][d+1][i],dp[i][d][pre]+1+i-pre);
    }
  }
  int res=Inf;
  REPE(i,N) SMIN(res,dp[N][0][i]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  solve();
  return 0;
}
