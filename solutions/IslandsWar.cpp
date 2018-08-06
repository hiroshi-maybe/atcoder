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
 
 8/5/2018
 
 19:00-19:50 give up
 19:51-20:15 read AC solutions and got ACC
 
 I tried to solve by imos. However it's hard to beat O(N^2) time.
 It was straighforward to reduce to interval problem.
 However I couldn't go out of first approach by imos 😡
 Sorting by end of interval is very typical approach to solve interval problem. Very stupid analsysi skill 😡😡
 
 Editorials:
  - https://img.atcoder.jp/abc103/editorial.pdf
  - https://youtu.be/nVSWen0oM38?t=1942
  - http://drken1215.hatenablog.com/entry/2018/07/21/224200
  - http://kazune-lab.net/contest/2018/07/21/abc103/
  - https://www.hamayanhamayan.com/entry/2018/07/21/225127
  - http://hamko.hatenadiary.jp/entry/2018/07/21/224107
  - http://c-mer.hatenablog.com/entry/2018/07/21/233348
  - http://myblog.s-bullet.com/index.php/2018/07/22/atcoder-bc103-d-islands-war/
  - http://tutuz.hateblo.jp/entry/2018/07/22/084326
  - http://www.kisse-logs.com/2018/07/22/atcoder-beginner-contest-103/
  - https://twitter.com/drken1215/status/1020671160101437445
  - https://twitter.com/evima0/status/1020665424998903809
 
 Duality references:
  - https://en.wikipedia.org/wiki/Duality_(optimization)
  - http://mathtrain.jp/primaldual
  - https://en.wikipedia.org/wiki/Weak_duality
  - https://en.wikipedia.org/wiki/Strong_duality
 
 Summary:
  - DO NOT STICK TO FIRST APPROACH!!!! ARE YOU CRAZY??????????? 😡😡😡😡
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,M;
II A[MAX_N];
void solve() {
  sort(A,A+M,[&](II a, II b) {
    return a.second<b.second;
  });
  int res=0,maxr=0;
  REP(i,M) {
    int l,r; tie(l,r)=A[i];
    if(maxr<=l) {
      maxr=r;
      ++res;
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,M) {
    int a,b; cin>>a>>b;
    A[i]={a,b};
  }
  solve();
  return 0;
}
