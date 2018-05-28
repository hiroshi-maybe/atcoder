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
 
 5/20/2018 AGC024
 
 21:25-22:00 give up
 
 Editorials:
  - https://img.atcoder.jp/agc024/editorial.pdf
  - https://youtu.be/S1IkBhwnuYU?t=1249
 
 Tweets:
  - https://togetter.com/li/1229337
  - https://twitter.com/evima0/status/998205619386568704
  - https://twitter.com/torus711/status/998205681869074433
  - https://twitter.com/beet_aizu/status/998204540418584576
  - https://twitter.com/ei1333/status/998204508047007744
  - https://twitter.com/satanic0258/status/998205046033543170
 
 5/28/2018
 
 24:10-24:43 add solution
 
 Key:
  - We can keep ascending contiguous sequence. Once they are fixed, others must move
 
 Summary:
  - My solution was totally wrong greedy 👎
  - Analysis was not deep enough
  - Try to find counter example if correctness is not obvious
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:59 1WA
const int MAX_N=200010;
int N;
LL P[MAX_N];
LL L[MAX_N],R[MAX_N];

void tol() {
  set<LL> S;
  LL x=0;
  REP(i,N) {
    S.emplace(P[i]);
    LL a=*(S.rbegin());
    if(a>P[i]) SMAX(x,P[i]);
    L[i]=x;
  }
}

void tor() {
  set<LL> S;
  LL x=N+1;
  for(int i=N-1; i>=0; --i) {
    S.emplace(P[i]);
    LL a=*(S.begin());
    if(a<P[i]) SMIN(x,P[i]);
    R[i]=x;
  }
}

void solve_wrong() {
  tol(),tor();
  LL res=min(L[N-1],N-R[0]+1);
  set<LL> S;
  REP(i,N) {
    S.emplace(P[i]);
    LL a=*(S.rbegin());
    if(a==i+1) SMIN(res,L[i]+N-R[i+1]+1);
  }
  cout<<res<<endl;
}

void solve() {
  vector<LL> X(N);
  REP(i,N) X[P[i]-1]=i;
  int res=N==1?0:N;
  int cur=1;
  FOR(i,1,N) {
    if(X[i]>X[i-1]) ++cur;
    else cur=1;
    SMIN(res,N-cur);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>P[i];
  solve();
  return 0;
}
