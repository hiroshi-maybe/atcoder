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
 
 4/28/2018
 
 11:30-11:50 pause
 
 6/7/2018
 
 20:05-20:46 AC
 
 Editorials:
  - https://atcoder.jp/img/agc008/editorial.pdf
  - https://kimiyuki.net/blog/2016/12/25/agc-008-b/
  - http://beet-aizu.hatenablog.com/entry/2016/12/31/200220
  - http://hkr-i.hatenablog.com/entry/2017/02/27/233911
  - http://hamko.hatenadiary.jp/entry/2017/10/17/131425
  - https://twitter.com/wakaba_me/status/950410350909800453
 
 Key:
  - The last paint shows black/white contiguous subsequence
  - It's possible to have arbitrary color outside the sequence of the last paint
 
 Summary:
  - I figured out greedy strategy from samples
  - I should have figured out greedy more quickly
   - I missed to try backward simulation 😵
   - It's clear that the last paint leaves black/white contiguous interval
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,K;
LL A[MAX_N];
LL cum[MAX_N];
LL solve() {
  LL res=0;
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+(A[i]>0?A[i]:0);
  LL cur=accumulate(A,A+K,0LL);
  REPE(i,N-K) {
    LL a=cum[i]+(cum[N]-cum[i+K]);
    LL b=a+cur;
    res=max({res,a,b});
    
//    dump4(i,a,cur,b);
    
    cur-=A[i];
    if(i+K<N) cur+=A[i+K];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  return 0;
}
