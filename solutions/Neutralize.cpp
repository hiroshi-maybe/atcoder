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
 
 8/25/2018
 
 14:35-14:49 analysis
 14:50-14:56 submit and got AC
 
 Editorials:
  - https://img.atcoder.jp/soundhound2018-summer-final/editorial.pdf
  - http://baitop.hatenadiary.jp/entry/2018/07/29/204143
  - http://drken1215.hatenablog.com/entry/2018/07/29/133800
  - https://www.hamayanhamayan.com/entry/2018/07/28/215201
  - http://tutuz.hateblo.jp/entry/2018/07/29/155249
  - http://betrue12.hateblo.jp/entry/2018/07/31/001823
  - 
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
int N,K;
LL B[MAX_N];
LL dp[MAX_N];
LL X[MAX_N];

//const LL Inf=1e15;
void solve() {
  X[0]=0,dp[0]=0;
  FORE(i,1,N) {
    dp[i]=dp[i-1]+B[i-1];
    if(i>=K) {
      SMAX(dp[i],dp[i-K]);
      SMAX(dp[i],X[i-K]);
    }
    X[i]=max(X[i-1],dp[i]);
//    dump3(i,dp[i],X[i]);
  }
  cout<<dp[N]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>B[i];
  solve();
  return 0;
}
