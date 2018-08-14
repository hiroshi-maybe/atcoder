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
 
 2018/8/13
 
 15:40-16:05 give up
 
 22:00-22:40 read editorials (1TLE due to full dp array reset)
 22:40-24:41 add solution #2
 
 Editorials:
  - https://img.atcoder.jp/code-thanks-festival-2017-open/editorial.pdf
  - http://ferin-tech.hatenablog.com/entry/2017/12/02/215249
   - very clear explanation of solution #1
  - http://kmjp.hatenablog.jp/entry/2017/12/02/0900
   - clean implementation of solution #2
   - nested loop actually achieves amortized complexity. cool.
  - https://trap.jp/post/435/
 
 Solution #1
 
 Suppose we iterated A[i] i=0..i-1 and got XOR of subset of them
 Generally...
 
  XOR {x} <= OR {x}
 
  0^0=0 <= 0 (=0|0)
  0^1=1 <= 1 (=0|1)
  1^1=0 <= 1 (=1|1)
 
 Result of XOR of subset of them <= logical OR of them.
 
 Thus A[i] ^ XOR { A[k]: k=0..i-1 } <= A[i] | OR { A[k]: k=0..i-1 }
 
 We can reduce computation by this fact.
 
 XOR never makes a carry to higher bit. Thus OR { A[k]: k=0..i-1 } <= 2*A[i-1]
 Total number of dp computation is upper-bounded by...
 
    0 +   A[0] + A[0]|A[1] + .. + OR { A[k] : k=0..N-1 }
 <= 0 + 2*A[0] +    2*A[1] + .. +               2*A[N-1]
 <= 2 * ∑ { A[i] : i=0..N-1 }
 
 => O(sum) ≈ 10^5

 Key:
  - XOR {x} <= OR {x} <= 2*max{x}
  - XOR or OR operation never makes carry. Thus result of those operations has small upper-bound.
  - Amortized complexity has tight bound

 Solution #2
 
 ∑ { A[i] : i=0..N-1 } <= 10^5

 This means some of A[i] should be duplicated.
 Suppose we have number `m` `x`s in `A`.
 We may select `x` i (0<=i<=m) times.
 The result of XOR of `m` `x`s can be either `0` or `x`.
 We can count how many cases we choose of them for those cases:
 
 a) XOR { x } = 0 (number of `x` is even)
 
 A = C(m,0) + C(m,2) + .. + C(m,floor(m/2)*2)
 
 b) XOR { x } = x (number of `x` is odd)
 
 B = C(m,1) + C(m,3) + .. + C(m,floor(m/2)*2+1)
 
 A + B = C(m,0)                     + C(m,1) + C(m,2) + C(m,3) + .. + C(m,m)
       = C(m,0)*1^m*1^0 + C(m,1)*1^(m-1)*1^1 + ...
       = (1+1)^m = 2^m
 A - B = C(m,0)                       - C(m,1) + C(m,2) - C(m,3) + ..
       = C(m,0)*1^m*-1^0 + C(m,1)*1^(m-1)*-1^1 + ...
       = (1-1)^m = 0
 
 <=> A = B = 2^(m-1)
 
 by binomial theorem https://en.wikipedia.org/wiki/Binomial_theorem
 
 Next question is how many unique `x` can appear in sum <= 10^5 constraint?
 In worst case, X = {1,2,3,...}
 
 1+2+3+...n = n(n+1)/2 <=10^5
 446*447/2=99681, 447*448/2=100128>10^5
 
 => maximal `n` is 446
 
 XOR { A } is upper-bounded by 2*sum as seen in solution #2.
 Thus we can solve this problem by O(sum*√sum) time ≈ 446*10^5
 This is kind of coordinate compression because we are processing `non`-continuous numbers
 
 Key:
  - Unique set of number is upperbounded by 446 (coordinate compression)
  - XOR of the same value has only two values {x,0}
  - Possible number of selection can be calculated by binomial theorem
 
 Summary:
  - I came up with dp though, I didn't dig it deeply due to O(N*K) runtime
  - dp + "unnatural" constraint seems to be typical pattern
  - I've not solved this kind of dp problem with analysis-wise lower bound
  - It's pretty creative to find relation XOR S <= OR S <= 2*∑ S
  - Problem reduction is not only of satisfaction properties but also problem constraint
  - I got 1 TLE because I did full dp array reset that produces O(N^2) computation
  - I think score of this problem is 600 or 700 😅
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,K;
const LL MOD=1e9+7;
LL A[MAX_N];
LL dp[2][MAX_N];
void solve_dp1() {
  sort(A,A+N);
  ZERO(dp);
  dp[0][0]=1;
  int U=0;
  REP(i,N) {
    int i1=i&1,i2=i1^1;
    REPE(n,U)dp[i2][n]=0;
    REPE(n,U) {
      (dp[i2][n]+=dp[i1][n])%=MOD;
      (dp[i2][n^A[i]]+=dp[i1][n])%=MOD;
    }
    U|=A[i];
    // below loose bound works too by dp table with doubled size dp[2][2*MAX_N];
    //U=2*A[i];
  }
  cout<<dp[N&1][K]<<endl;
}

LL dpdp[2][2*MAX_N];
LL cnt[MAX_N];
LL P2[MAX_N];
void solve() {
  ZERO(cnt); ZERO(P2); ZERO(dpdp);
  REP(i,N) cnt[A[i]]++;
  P2[0]=1;
  REP(i,MAX_N-1)P2[i+1]=P2[i]*2LL%MOD;
  
  int i1=0;
  dpdp[i1][0]=1;
  REP(x,MAX_N)if(cnt[x]) {
    int m=cnt[x];
    int i2=i1^1;
    REP(i,2*MAX_N) dpdp[i2][i]=0;
    REP(n,2*MAX_N) {
      (dpdp[i2][n]+=P2[m-1]*dpdp[i1][n]%MOD)%=MOD;
      (dpdp[i2][n^x]+=P2[m-1]*dpdp[i1][n]%MOD)%=MOD;
    }
    i1^=1;
  }
  cout<<dpdp[i1][K]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
