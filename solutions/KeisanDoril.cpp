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
 
 8/20/2018
 
 12:00-12:30 give up
 
 NG condition was trivial.
 However I had no idea to find maximal expression by `x` changes.
 A) digit change
 B) operator change
 
 There are two major approaches
 1. there is greedy optimal strategy
 2. search all the possibilities
 
 #1 => sometimes A) is better. Sometimes B) is better.
 I cannot find optimal strategy.
 
 #2 => 2^52 possibilities. I have no idea to search all the cases
 
 At last I gave up.
 
 13:30-15:55 read editorials and got AC after 11WA
 
 Editorials:
  - https://niconare.nicovideo.jp/watch/kn2189
  - http://kmjp.hatenablog.jp/entry/2017/04/02/0900
  - https://kimiyuki.net/writeup/algo/atcoder/dwacon-2017-finals-a/
  - http://fluffyowl.hatenablog.com/entry/2017/08/08/015259
  - http://hamko.hatenadiary.jp/entry/2018/08/21/003454
 
 Key:
  - Combination of subtraction and addition => both maximal and minimal needed
 
 Summary;
  - I didn't dig search approach. However dp would be hard to come up with by myself
  - "divided into consecutive intervals => interval dp" is typical pattern
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=52+1;
int N,K;

bool viz[MAX_N][MAX_N][MAX_N];
II memo[MAX_N][MAX_N][MAX_N];

const int Inf=1<<20;
string S;
LL A[MAX_N];
const string no="NG",yes="OK";

II f(int l, int r, int k) {
  if(viz[l][r][k]) return memo[l][r][k];
  viz[l][r][k]=true;
  II &res=memo[l][r][k];
  if(r<l) return res;
  if(l==r) {
    if(k>=1) res={0,9};
    else if(isdigit(S[l])) res={S[l]-'0',S[l]-'0'};
    return res;
  }
  if(isdigit(S[r])&&k==0) return res;
  
  int K=S[r]!='+'?k-1:k;
  FOR(x,l,r)REPE(kk,K) {
    II left=f(l,x,kk),right=f(x+1,r-1,K-kk);
      // plus
    SMAX(res.second,left.second+right.second);
    SMIN(res.first,left.first+right.first);
  }
  
  K=S[r]!='-'?k-1:k;
  FOR(x,l,r)REPE(kk,K) {
    II left=f(l,x,kk),right=f(x+1,r-1,K-kk);
      // minus
    SMAX(res.second,left.second-right.first);
    SMIN(res.first,left.first-right.second);
  }
  return res;
}

void solve() {
  N=SZ(S);
  ZERO(viz);
  REP(i,N)REP(j,N)REPE(k,K) memo[i][j][k]={Inf,-Inf};
  int res=-10000;
  REPE(k,K) {
    II ans=f(0,N-1,k);
    SMAX(res,ans.second);
  }

  if(res==-10000) {
    cout<<no<<endl;
  } else {
    cout<<yes<<endl;
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>K>>S;
  solve();
  return 0;
}
