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

 8/23/2018

 22:05-22:18 analysis
 22:19-22:24 implement and got AC

 Editorials:
  - http://agc002.contest.atcoder.jp/data/agc/002/editorial.pdf
  - https://kimiyuki.net/writeup/algo/atcoder/agc-002-c/
  - http://kmjp.hatenablog.jp/entry/2016/08/11/0900
  - http://hamko.hatenadiary.jp/entry/2017/02/10/160200

 7/6/2020

 9:09-9:36 solve again

 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL L;
LL A[MAX_N];

const string yes="Possible",no="Impossible";
void solve() {
  int x=-1;
  REP(i,N-1) if(A[i]+A[i+1]>=L) {
    x=i;
    break;
  }
  if(x==-1) {
    cout<<no<<endl;
    return;
  }
  cout<<yes<<endl;
  REP(i,x) cout<<i+1<<endl;
  for(int i=N-2; i>=x; --i) cout<<i+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N>>L;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
