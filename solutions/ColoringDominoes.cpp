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
 
 7/11/2018
 
 12:30-12:59 AC
 
 Editorials:
  - https://atcoder.jp/img/arc081/editorial.pdf
  - https://youtu.be/xRYReB8pc2E?t=1717
  - http://hamayanhamayan.hatenablog.jp/entry/2017/08/20/234150
  - https://kimiyuki.net/writeup/algo/atcoder/arc-081-d/
  - https://ei1333.hateblo.jp/entry/2017/08/21/024313
   - dp
  - https://pitsbuffersolution.com/compro/atcoder/arc081d.php
 
 Key:
  - only 2 patterns of how to fill dominos
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 12:30-12:59 AC
int N;
string S[2];
const LL MOD=1000000007;
void solve() {
  LL res=1;
  if(S[0][0]==S[1][0]) res=3;
  else res=6;
  
  FOR(i,1,N) if(S[0][i]!=S[0][i-1]) {
    if(S[0][i]==S[1][i]) {
      // *
      // *
      if(S[0][i-1]==S[1][i-1]) res*=2;
    } else {
      // **
      // @@
      if(S[0][i-1]==S[1][i-1]) res*=2;
      else res*=3;
    }
    res%=MOD;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,2) cin>>S[i];
  solve();
  return 0;
}