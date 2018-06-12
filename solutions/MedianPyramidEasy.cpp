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
 
 6/12/2018
 
 14:00-14:50 AC
 
 Editorials:
  - http://agc006.contest.atcoder.jp/data/agc/006/editorial.pdf
  - https://youtu.be/VX8cGy7kNTE?t=957
  - https://kimiyuki.net/writeup/algo/atcoder/agc-006-b/
  - http://beet-aizu.hatenablog.com/entry/2016/11/04/001139
  - http://logfiles.hatenablog.com/entry/2016/10/31/181221
  - http://hamko.hatenadiary.jp/entry/2018/01/04/104450
 
 Key:
  - Force two `X`s at the middle of the array
 
 Summary:
  - I firstly missed doubled number's win (only N can win in such a case)
  - I found counter-example by myself and got AC
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 14:00-14:50 AC
int N,X;
const string yes="Yes",no="No";
const int MAX_N=1e5;
int res[2*MAX_N-1];
int viz[2*MAX_N];
void put(int i, int n) {
  assert(viz[n]==0);
  viz[n]=true;
  res[i]=n;
}

void solve() {
  if(X==2*N-1||X==1) {
    cout<<no<<endl;
    return;
  }
  ZERO(viz);
  MINUS(res);
  put(N-1,X);
  if(X==2) {
    put(N,1);
    put(N-2,3);
    put(N+1,4);
  } else {
    put(N,X+1);
    put(N-2,X-1);
    put(N+1,X-2);
  }
  int cur=1;
  REP(i,2*N-1) if(res[i]==-1) {
    while(viz[cur]) ++cur;
    put(i,cur++);
  }
  cout<<yes<<endl;
  REP(i,2*N-1) cout<<res[i]<<endl;
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>X;
  solve();
  return 0;
}
