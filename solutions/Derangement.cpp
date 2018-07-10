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
 
 7/10/2018
 
 16:40-16:58 1WA
 17:00-17:10 apply ceil(cur/2) but got 2WA
 17:10-17:13 Ok. I missed to fix with ceil outside the loop 😞
 
 Editorials:
  - https://atcoder.jp/img/arc082/editorial.pdf
  - https://youtu.be/P_ZGm7cf3a4?t=1346
  - https://kimiyuki.net/writeup/algo/atcoder/arc-082-d/
  - http://naoyat.hatenablog.jp/entry/ARC082
  - http://phwinx.hatenablog.com/entry/2017/09/03/014204
  - http://kazune-lab.net/contest/2017/09/02/arc082/
 
 Key:
  - One swap resolves at most 2 elements
 
 Summary:
  - I mistakenly thought that N-1 swap is needed to resolve N contiguous sub-array
   - I should have reviewed if my initial idea is really optimal.
   - What we want to achieve is P[i]!=i. One swap acieves it for P[i] and P[i+1].
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL P[MAX_N];
void solve() {
  int res=0;
  int cur=0;
  REP(i,N) {
    if(P[i]==i) ++cur;
    else {
      res+=(cur+1)/2;
      cur=0;
    }
  }
  if(cur) res+=(cur+1)/2;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>P[i],P[i]--;
  solve();
  return 0;
}
