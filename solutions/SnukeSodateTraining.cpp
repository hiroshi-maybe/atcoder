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
 
 14:25-15:10 give up
 18:20-18:40, 21:30-22:25 read editorials and got AC

 I came up with dp with state dp[i][times][stamina] or dp[i][prev][times].
 However obviously they don't fit in the constraint.
 By some experiments, two observations..
  - first one and last one should be taken
  - time which divides T[0..N-1] equally seems better
 I tried to find some greedy strategy. However no luck 😞
 
 Editorials:
  - https://img.atcoder.jp/colopl2018-qual/editorial.pdf
  - http://seica-at.hatenablog.com/entry/2017/12/10/173410
  - http://kurkur.hatenablog.com/entry/2017/12/12/024221
  - http://kmjp.hatenablog.jp/entry/2017/12/15/0900
  - http://hamko.hatenadiary.jp/entry/2017/12/10/031653

 In editorial's design, we can greedily transition as below:
 
  T[i] -> T[j],T[j+1] s.t. j = max { j: i<j, T[i]+x>=T[j] }
 
 Lemma 1: T[j] s.t. T[i]+x>=T[j] is optimal if we gain new stamina y<=X
 
 Suppose we use time `k` s.t. T[k]<T[j].
 
 Gain by transitioning T[k]->T[j] is T[k]-T[i] + T[j]-T[k] = T[j]-T[i]
 This is actually same as T[i]->T[j]. Also we have loss of available game launch.
 Thus T[i]->T[j] is better than T[i]->T[k] if we gain new stamina y<=x
 
 Lemma 2: T[j+1] s.t. T[i]+x>T[j] is optimal if we fully recover
 
 Suppose we use time `k` s.t. T[j+1]<T[k].
 We gain `X` in eigher T[j+1] or T[k]. Also in next transition, earlier time has more chances to recover stamina.
 Thus T[i]->T[j+1] is better if we fully recover
 
 From Lemma 1 and Lemma 2, transition to T[j] or T[j+1] is optimal.
 
 Now we can drop `i` from my own original dp state `dp[i][prev][times]`
 
 Summary:
  - Combination of greedy and dp 😞
  - O(1) transition may prevent from other approach. Reducing states may help.
   - I caught up the observation described in the editorial by myself
   - However I couldn't associate it with enhancement of naiive dp due to three dimension state
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=5e3+1;
int N;
LL X;
vector<LL> T;
LL dp[MAX_N][MAX_N];
void solve() {
  ZERO(dp);
  T.push_back(1e10);
  REP(i,N) {
    int j=upper_bound(T.begin(),T.end(),T[i]+X)-T.begin(); --j;
    j=min(j,N-1);
    REP(t,N) {
      if(j>i)SMAX(dp[j][t+1],dp[i][t]+min(T[j]-T[i],X));
      if(j+1>i)SMAX(dp[j+1][t+1],dp[i][t]+min(T[j+1]-T[i],X));
    }
  }
  
  vector<LL> res(N);
  LL pre=0;
  FORE(i,1,N) {
    res[i-1]=pre;
    REPE(j,N) SMAX(res[i-1],dp[j][i]);
    pre=res[i-1];
  }
  REP(i,N) cout<<res[i]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>X;
  T.resize(N);
  REP(i,N) cin>>T[i];
  solve();
  return 0;
}
