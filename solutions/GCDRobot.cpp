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
 
 15:35-16:18 analysis
 16:19-16:22 implement and got 1AC
 
 We want to make kind of union of x ∈ { gcd(A[i],Z) : i=0..N-1 }
 However prime factorization is not possible.
 We can keep appending missing composite numbers by gcd
 
 Editorials:
  - https://img.atcoder.jp/ddcc2017-final/editorial.pdf
  - https://blog.remin.jp/post/ddcc2017
  - http://prd-xxx.hateblo.jp/entry/2017/12/28/171552
  - http://kazune-lab.net/contest/2017/11/03/ddcc2017-final/
 
 res = G[i]*x for i=0..N-1 where G[i]=gcd(Z,A[i])
 => X = a*L where L=lcm({ G[i] : i=0..N-1 }). Symmetrically Z = b*L
 
 L<=Z => gcd(L,A[i]) <= gcd(Z,A[i])
 At the same time, L>=G[i] = gcd(A[i],Z) in i=0..N-1
 
 Thus L=gcd(A[i],Z) which satisfies expected property for the result.
 
 Summary:
  - I solved by myself though, I didn't have proof based on LCM
  - Minimum union of gcds => LCM is what I must know
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL Z;
LL A[MAX_N];

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

void solve() {
  LL res=1;
  REP(i,N) {
    LL g=gcd(A[i],Z);
    LL a=gcd(res,g);
    res*=g/a;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Z;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
