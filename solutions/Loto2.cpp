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
 
 12:45-13:05 give up
 14:10-15:03 read editorials and got AC
 
 Editorials:
  - http://ddcc2016-qual.contest.atcoder.jp/data/other/ddcc2016-qual/editorial.pdf
  - http://baitop.hatenadiary.jp/entry/2018/07/05/222302
  - http://kmjp.hatenablog.jp/entry/2016/11/22/0900
  - https://kimiyuki.net/writeup/algo/atcoder/ddcc-2016-qual-c/
  - http://procon-nenuon61.hatenablog.com/entry/2017/09/23/140802
  - http://beet-aizu.hatenablog.com/entry/2016/11/06/001851
  - http://www.yamitomo.info/index.php/2017/10/19/disco-2016-c/
 
 Naiive brute-force O(N^2) algorithm TLEs.
 Idea is to filter out only relevant elements in array A.
 What we are interested in is relelvant component numbers in A[i].
 If K=2*3, we are not interested in 5 in 10 (=2*5).
 In order to obtain it, we can compute gcd(A[i],K).
 Suppose B[i] = gcd(A[i],K) in i=0..N-1
 
 HCN (=Highly Composit Number) in 10^9 is almost 1440.
 Thus unique set in `B` is upper-bounded by 1440.
 We can brute-force pairs in `B` in 1440*1440 ≈ 2*10^6.
 
 If K | B[i]*B[j], pair of original numbers forms multiple of K.
 
 Suppose gcd(x,K)=a, gcd(y,K)=b
 
 Lemma 1: K|a*b => K|x*y
 
 x is multiple of a, y is multiple of b. Thus x*y should be obviously divisible by K.

 a=6,x=6*p, b=4,y=4*q, K=12 (K|a*b) => x*y=24*p*q which is divisible by K (=12)
 
 Lemma 2: K|x*y => K|a*b
 
 `a` and `b` are intersection of (x and K) and (y and K) in terms of prime factorization.
 They have only `relevant` prime factors to `K`. Thus K|a*b should hold too.
 
 K=12, x=30, y=28 => a=gcd(30,12)=6, b=gcd(28,12)=4, a*b=24 which is divisible by K (=12)

 From lemma 1 and lemma 2, K|a*b <=> K|x*y. Therefore checking `B` is valid.
 
 Key:
  - brute-force after filtering
  - `gcd` filters relevant unique elements which is upper-bounded by HCN
 
 Summary:
  - I tried to solve by prime factorization. However no luck.
  - Counting problem => Map to smaller sets
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
int N,K;
LL A[MAX_N];

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

vector<pair<LL,int>> B;
void solve() {
  MAPII M;
  REP(i,N) M[gcd(A[i],K)]++;
  FORR(kvp,M) B.emplace_back(kvp.first,kvp.second);
  int NN=SZ(B);
  LL res=0;
  REP(j,NN)REP(i,j) {
    LL a,b; LL n,m; tie(a,n)=B[i],tie(b,m)=B[j];
    LL ab=a*b;
    if((ab%K)==0) res+=n*m;
  }
  REP(i,NN) {
    LL a; LL n; tie(a,n)=B[i];
    LL aa=a*a;
    if((aa%K)==0) res+=n*(n-1)/2LL;
  }
  
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
