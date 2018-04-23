#include <iostream>
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
 
 4/23/2018
 
 9:10-9:23 analysis
 9:24-9:38 1WA by binary search 🤔
 9:48 2WA
 9:49-10:27 Figured out behavior of the range by simulation and got AC
 
 Editorials:
  - https://img.atcoder.jp/agc020/editorial.pdf
  - http://hamayanhamayan.hatenablog.jp/entry/2018/01/15/003942
  - https://kimiyuki.net/blog/2018/02/22/agc-020-b/
  - http://skbtkey.hatenablog.com/entry/AGC020_B
 
 Summary:
  - It turned out that binary search solution had overflow bug 😞
 
 */

const LL Inf=1e18;

LL high(LL T, LL A) {
  LL good=-1,bad=Inf;
  while(abs(good-bad)>1) {
    if(A==512337211) dump2(good,bad);
    LL mid=(good+bad)/2LL;
    LL fx=mid-mid%A;
    (fx<=T?good:bad)=mid;
  }
  return good;
}

LL low(LL T, LL A) {
  LL good=Inf,bad=-1;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2LL;
    LL fx=mid-mid%A;
    (fx>=T?good:bad)=mid;
  }
  return good;
}

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
vector<LL> solve(int N, vector<LL> A) {
  if(A.back()!=2) return {};
  
  LL l=2,r=2;
  for(int i=N-1; i>=0; --i) {
    l=low(l,A[i]);
    r=high(r,A[i]);
    dump4(i,A[i],l,r);
    if(l>r) return {};
//    if(l<=-1||l>Inf) return {};
//    if(h<=-1||h>Inf) return {};
  }
  return {l,r};
}

vector<LL> solve_linear(int N, vector<LL> A) {
  if(A.back()!=2) return {};
  
  LL l=2,r=2;
  for(int i=N-1; i>=0; --i) {
    LL a=A[i];
    LL k1=(l+a-1)/a,k2=r/a;
    l=a*k1;
    r=a*(k2+1)-1;
    //    dump4(i,A[i],l,r);
    if(l>r) return {};
  }
  return {l,r};
}

int main() {
  int N; scanf("%d", &N);
  vector<LL> A(N);
  REP(i,N) scanf("%lld", &A[i]);
  vector<LL> res=solve(N,A);
  if(res.empty()) printf("-1\n");
  else printf("%lld %lld\n",res[0],res[1]);
  return 0;
}
