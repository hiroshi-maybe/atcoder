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
 
 17:20-17:34 analysis
 17:35-17:47 implement and got AC
 
 Editorials:
  - https://img.atcoder.jp/tenka1-2017/editorial.pdf
  - http://ferin-tech.hatenablog.com/entry/2017/10/01/145915
  - http://prd-xxx.hateblo.jp/entry/2017/10/01/015007
  - http://kazune-lab.net/contest/2017/09/30/tenka1-2017/
   - I made same mistake as described in this article
   - If K=1001101, candidate is only 1001101 and 0111111 => this is wrong. 1001011 can be optimal.
  - http://www.yamitomo.info/index.php/2017/10/02/tenka1-programmer-contest-d-integerots/
 
 Summary:
  - Straightforward analysis
   - dp[N][OR{x}] is too many states => I need to reduce complexity => possible mask is not so many
   - If mask is fixed, we can take as many numbers which is subset of the mask as possible
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL K;
LL A[MAX_N],B[MAX_N];
void solve() {
  LL res=0;
  REP(i,N) if((A[i]|K)==K) res+=B[i];
  REPE(i,30) if((K>>i)&1) {
    LL mask=K-(1LL<<i);
    mask|=(1LL<<i)-1LL;
    LL x=0;
    REP(i,N) if((A[i]|mask)==mask) x+=B[i];
    SMAX(res,x);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i]>>B[i];
  solve();
  return 0;
}
