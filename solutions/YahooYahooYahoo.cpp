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
 
 16:10-16:23 analysis
 16:38 handled insertion and submit
 16:44 bug fix (missed deletion when matched) and got AC
 
 Editorials:
  - https://atcoder.jp/img/yahoo-procon2017-final/editorial.pdf
  - http://noimin.hatenablog.com/entry/2017/12/26/222949
  - https://kimiyuki.net/writeup/algo/atcoder/yahoo-procon-2017-final-a/
  - http://tutuz.hateblo.jp/entry/2018/07/01/110356
  - http://rsujskf.s602.xrea.com/?atcoder_yahoo-procon2017-final_a
  - http://kazune-lab.net/contest/2018/02/10/yahoo-procon2018-qual/
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int dp[MAX_N][5];
string S;
const int Inf=1e7;
const string Y="yahoo";
void solve() {
  int N=SZ(S);
  REPE(i,N)REP(j,5)dp[i][j]=Inf;
  dp[0][0]=0;
  REP(i,N){
    REP(j,5) {
      int jj=(j+1)%5;
      SMIN(dp[i][jj],dp[i][j]+1);
    }
    REP(j,5) {
      int jj=(j+1)%5;
      if(S[i]==Y[j]) {
        SMIN(dp[i+1][jj],dp[i][j]);
        SMIN(dp[i+1][j],dp[i][j]+1);
      } else {
        SMIN(dp[i+1][jj],dp[i][j]+1);
        SMIN(dp[i+1][j],dp[i][j]+1);
      }
    }
  }
  cout<<dp[N][0]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  solve();
  return 0;
}
