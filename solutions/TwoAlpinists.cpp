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
 
 15:25-15:42 got AC
 
 Editorials:
  - http://code-festival-2016-qualc.contest.atcoder.jp/data/other/code-festival-2016-qualc/editorial.pdf
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2016-qualc-c/
  - http://hamko.hatenadiary.jp/entry/2017/07/28/110610
  - https://ykmaku.hatenablog.com/entry/2018/07/15/223228
  - http://competitive-kivantium.hateblo.jp/entry/2016/10/24/135521
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL A[MAX_N],T[MAX_N];
const LL MOD=1e9+7;
LL L[MAX_N],R[MAX_N];
void solve() {
  REP(i,N) {
    if(i==0||A[i-1]<A[i]) L[i]=R[i]=A[i];
    else L[i]=1,R[i]=A[i];
  }
  LL res=1;
  for(int i=N-1; i>=0; --i) {
    LL l,r;
    if(i==N-1||T[i]>T[i+1]) l=r=T[i];
    else l=1,r=T[i];
    LL d=min(r,R[i])-max(l,L[i])+1;
    d=max(d,0LL);
    if(d<0) res=0;
//    dump2(i,d);
    res*=d,res%=MOD;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>T[i];
  solve();
  return 0;
}
