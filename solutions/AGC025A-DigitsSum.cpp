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
 
 6/3/2018 AGC025 A
 
 21:00-21:05
 
 Editorial:
  - https://img.atcoder.jp/agc025/editorial.pdf
  - https://youtu.be/Ommfmx2wtuY?t=1868
  - http://naoyat.hatenablog.jp/entry/AGC025
  - http://yosupo.hatenablog.com/entry/2018/06/04/004619
  - http://drken1215.hatenablog.com/entry/2018/06/04/120000
 
 Tweets:
  - https://togetter.com/li/1233682
  - https://twitter.com/zunda99999999th/status/1003277679020335104
  - https://twitter.com/_TTJR_/status/1003277771924099077
  - https://twitter.com/drken1215/status/1003278214578360320
  - https://twitter.com/tanakh/status/1003279982544605184
 
 Summary:
  - I didn't come up with greedy solution described in the official editorial
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:00-21:05
int N;
int f(LL x) {
  int res=0;
  while(x>0) res+=x%10,x/=10;
  return res;
}
int solve() {
  int res=1e4;
  FOR(n,1,N) {
    LL m=N-n;
    SMIN(res,f(n)+f(m));
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  cout<<solve()<<endl;
  return 0;
}
