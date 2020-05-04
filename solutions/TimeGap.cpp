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
 
 8/12/2018
 
 22:10-22:45 give up
 
 I tried to solve by brute-forcing from 1 to 24 or finding greedy strategy. However no luck.
 
 8/13/2018
 
 14:00-14:39 read editorials and add solution
 
 Editorials:
  - https://img.atcoder.jp/cf17-final/editorial.pdf
  - https://kimiyuki.net/writeup/algo/atcoder/cf17-final-c/
  - https://www.hamayanhamayan.com/entry/2017/11/27/224728
  - http://hamko.hatenadiary.jp/entry/2017/11/25/165036
 
 Cities are mapped to a ring with 24 points.
 We want to maximize distance with adjacent point.
 We can choose T[i] or 24-T[i] for city `i`.
 
 If there are three cities, at least two cities share the same time T[i] or 24-T[i].
  => res = 0
 
 Two cities at T[i]
  => they should be placed at T[i] and 24-T[i] respectively
 
 Otherwise we can choose T[i] or 24-T[i].
 There can exist 2^11 options for those cities. We can brute-force them.
 
 Key:
  - Problem is reduced to ring
  - Three cities with same time => res=0
  - brute-force works
 
 Summary:
  - I didn't have idea of projecting to "ring" (we need to see 18-24 = 6 hours gap too)
  - cycle => ring (abstraction)
 
 5/3/2020
 
 Add solution again
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=50+1;
int N;
int D[MAX_N];
int cnt[13]={};
int solve() {
  cnt[0]=1;
  REP(i,N)cnt[D[i]]++;
  FOR(i,1,12) if(cnt[i]>2) return 0;
  if(cnt[0]>1) return 0;
  if(cnt[12]>1) return 0;
  int res=0;
  REP(mask,1<<11) {
    VI X;
    if(cnt[0]) X.push_back(0);
    if(cnt[12]) X.push_back(12);
    REP(i,11) if(cnt[i+1]>0) {
      int t=i+1;
      if(cnt[t]>1) X.push_back(t),X.push_back(24-t);
      else X.push_back(((mask>>i)&1)?t:24-t);
    }
    sort(X.begin(),X.end());
    X.push_back(24);
    int ming=25;
    REP(i,SZ(X)-1) SMIN(ming,X[i+1]-X[i]);
//    dump(ming);
//    dumpAR(X);
    SMAX(res,ming);
  }
  return res;
}

int solve_greedy() {
  VI cnt(13,0);
  REP(i,N+1) cnt[D[i]]++;
//  dumpc(cnt);
  REP(i,13) if(cnt[i]>2) return 0;
  if(cnt[0]==2||cnt[12]==2) return 0;
  VI B(24,0);
  bool lr=0;
  REP(i,13) {
    if(cnt[i]==2) B[i]=B[i==0?0:(24-i)]=1;
    else if(cnt[i]==1) {
      B[((i==0||lr)?i:(24-i))]=1;
      lr^=1;
    } else if(cnt[i]==0) continue;
    else assert(false);
  }
//  dumpc(B);
  int res=24;
  REP(i,24) if(B[i]) {
    int mind=24;
    REP(j,24) if(i!=j&&B[j]) SMIN(mind,min(abs(i-j),abs(j+24-i)));
    SMIN(res,mind);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>D[i];
  cout<<solve()<<endl;
  return 0;
}
