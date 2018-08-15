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
 
 2018/8/14
 
 15:20-15:55 give up
 
 Euler's totient function doesn't work due to large N constraint.
 I tried to solve by inclusion-exclusion principle. However I could not complete it.
 
 17:45-18:23 read editorials and got AC
 
 Editorials:
  - https://img.atcoder.jp/colopl2018-qual/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2017/12/10/031120
  - http://kurkur.hatenablog.com/entry/2017/12/10/024320
   - mentioning to dp solution
  - http://mhiroaki.hatenablog.com/entry/2017/12/25/201143
  - http://ferin-tech.hatenablog.com/entry/2017/12/09/235610
  - https://pitsbuffersolution.com/blog/articles/colocon2018_qual.php
  - http://tookunn.hatenablog.com/entry/2017/12/10/095326
 
 2^35 is not tight upper-bound of the result.
 What we can figure out from constraint B-A<=35
  - Half of them is even. They cannot be paired each other => 2^36 -> 2^18
   - 1/3 of them is divisible by 3 (18 = ceil(36/3))
   - 1/5 of them is divisible by 5 (8 = ceil(36/5))
   - ...
  - Common prime of them is less than 35
   - If x and x+k has common divisor D, k should be <= D
   - dp works based on this analysis (11 primes in [2..35])
 
 Key:
  - few mutually co-prime pairs in consecutive numbers
 
 Summary:
  - Hmmm I didn't come up with brute-force. Poor math taste 😞
  - B-A<=35 is weird
   - I should have tried simpler solution than inclusion-exclusion principle
   - Deep analysis is usually needed to give tight upper-bound which simplifies solution
   - How many times are you deceived by those special constraints? Sigh 😞
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

LL A,B;
vector<LL> X;
LL res=0;
void dfs(int s, vector<LL> &cur) {
  int N=SZ(X);
  if(s==N) {
    ++res;
    return;
  }
  bool ok=true;
  FORR(n,cur) if(gcd(n,X[s])!=1) ok=false;
  if(ok) {
    cur.push_back(X[s]);
    dfs(s+1,cur);
    cur.pop_back();
  }
  dfs(s+1,cur);
}
void solve() {
  for(LL n=A; n<=B; ++n) X.push_back(n);
  vector<LL> cur;
  dfs(0,cur);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>A>>B;
  solve();
  return 0;
}
