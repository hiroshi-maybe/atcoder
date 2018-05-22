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
 
 5/20/2018 AGC 24
 
 21:04-21:20 AC
 
 n)   A: B+x    , B:      B, C:       C, f(A,B)= x
 n+1) A: B+C    , B:  B+C+x, C:    2B+x, f(A,B)=-x
 n+2) A: 3B+C+2x, B: 3B+C+x, C: 2B+2C+x, f(A,B)= x
 
 Editorials:
  - https://img.atcoder.jp/agc024/editorial.pdf
  - https://youtu.be/S1IkBhwnuYU?t=957
 
 Tweets:
  - https://togetter.com/li/1229337
  - https://twitter.com/evima0/status/998205250052866048
  - https://twitter.com/satanic0258/status/998205046033543170
 
 Summary:
  - I tried repeated squaring first though, I changed my mind due to its point 300
  - Eventually figured out that there are two cases based on parity of K
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL A,B,C,K;
const string no="Unfair";
void solve() {
  LL res=0;
  if(K%2==0) res=A-B;
  else res=B-A;
  
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>A>>B>>C>>K;
  solve();
  return 0;
}
