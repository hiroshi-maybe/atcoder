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
 
 6/16/2018 ABC100
 
 21:30-23:00 give up
 23:00-23:31 read editorials and add solution
 
 Editorials:
  - https://img.atcoder.jp/abc100/editorial.pdf
  - https://youtu.be/gyJh6k9vOXs?t=1821
 
 What we want to compute is maximum |∑x|+|∑y|+|∑z|
 
 |a| = max { a, -a }
 
 Thus, |∑x| = max { ∑x, -∑x }
 
 => |∑x|+|∑y|+|∑z| = max { ∑x, -∑x } + max { ∑y, -∑y } + max { ∑z, -∑z }
 
 This means we can decide positive or negative independently for X, Y or Z
 Brute-forcing those signs needs 2^3 (=8) computation.
 If tuple of signs e.g. (+,-,+) is fixed, we can select top M greedily.
 
 Tweets:
  - https://togetter.com/li/1237847
  - https://twitter.com/drken1215/status/1008248572368711680
  - https://twitter.com/drken1215/status/1008249922066382848
   - impressive analysis of absolute value
  - https://twitter.com/satanic0258/status/1007986610011496448
   - easy to understand
  - https://twitter.com/tanakh/status/1007985498910937089
  - https://twitter.com/satanic0258/status/1007986610011496448
  - https://twitter.com/tempura_pp/status/1008024965411627008
  - https://twitter.com/_TTJR_/status/1007982375546994688
  - https://twitter.com/satanic0258/status/1007981278346350599
  - https://twitter.com/dermastech/status/1007981217638043648
  - https://twitter.com/dynamis724/status/1007981282179944450
 
 Key:
  - Computation of absolute value is reduced to search of cases of signs (+,-)
 
 Summary:
  - My analysis was totally poor. I couldn't find any clue during the contest 😞
  - Reducing absolute value to two separated cases is interesting
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
const LL Inf=1e17;
int N,M;
LL X[MAX_N][3];

// 21:30-23:00 give up
// 23:00-23:31 read editorials
/*
LL dp[MAX_N][MAX_N][3][8];
LL score(LL x, LL y, LL z) {
  if(x==Inf) return -Inf;
  return abs(x)+abs(y)+abs(z);
}

LL f(int mask) {
  REPE(i,N)REPE(j,N) REP(k,3) {
    LL a=(mask>>k)&1?-Inf:Inf;
    dp[i][j][k][mask]=a;
  }
  REP(k,3)dp[0][0][k][mask]=0;
  REPE(i,N)REPE(j,M) {
    int X[3];
    REP(k,3) X[k]=dp[i][j][k][mask];
    if(abs(X[0])==Inf) continue;
    REP(k,3) X[k]+=X[i][k]
    if(i+1<=N&&j+1<=M) {
      
      tie(xx,yy,zz)=dp[i+1][j+1];
      if(score(xx,yy,zz)<score(x2,y2,z2)) {
        dp[i+1][j+1]={x2,y2,z2};
      }
    }
    if(i+1<=N) {
      LL xx,yy,zz; tie(xx,yy,zz)=dp[i+1][j];
      if(score(xx,yy,zz)<score(x,y,z)) {
        dp[i+1][j]={x,y,z};
      }
    }
  }
  
  LL x,y,z; tie(x,y,z)=dp[N][M];
  cout<<score(x,y,z)<<endl;
}
void solve() {
  LL res=0;
  REP(mask,8) {
    SMAX(res,f(mask));
  }
  cout<<res<<endl;
}*/

void solve() {
  LL res=0;
  REP(mask,8) {
    vector<LL> A(N);
    REP(i,N) {
      LL a=0;
      REP(k,3) {
        LL x=X[i][k];
        if(mask&(1<<k)) x=-x;
        a+=x;
      }
      A[i]=a;
    }
    sort(A.rbegin(),A.rend());
    SMAX(res,accumulate(A.begin(),A.begin()+M,0LL));
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N) cin>>X[i][0]>>X[i][1]>>X[i][2];
  solve();
  return 0;
}

