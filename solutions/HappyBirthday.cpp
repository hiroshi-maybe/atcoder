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
 
 6/16/2018 ABC100
 
 21:00-21:10 ACC
 
 Editorials:
  - https://img.atcoder.jp/abc100/editorial.pdf
  - https://youtu.be/gyJh6k9vOXs?t=685
 
 Key:
  - putting A's is independent of B's
 
 Summary:
  - I simulated without further analysis though, res = A<=8&&B<=8
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int A,B;
const string yes="Yay!",no=":(";
int X[16];
void solve_org() {
  MINUS(X);
  if(A<B) swap(A,B);
  X[0]=0,--A;
  FOR(i,1,16) {
    if(X[i-1]==0&&B>0) X[i]=1,--B;
    else if(X[i-1]==1&&A>0) X[i]=0,--A;
    else if(X[i-1]==-1&&A>0) X[i]=0,--A;
    else if(X[i-1]==-1&&B>0) X[i]=1,--B;
  }
  dump2(A,B);
  dumpAR(X);
  if(A>0||B>0) cout<<no<<endl;
  else if(X[15]==X[0]) cout<<no<<endl;
  else cout<<yes<<endl;
}

void solve() {
  cout<<(A<=8&&B<=8?yes:no)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>A>>B;
  solve();
  return 0;
}
