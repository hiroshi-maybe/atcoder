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
 
 5/26/2018
 
 9:00-9:13 AC
 
 5/28/2018
 
 Editorials:
  - https://img.atcoder.jp/arc098/editorial.pdf
 
 Tweets:
  - https://togetter.com/li/1231142
  - https://twitter.com/evima0/status/1000371714499403778
  - https://twitter.com/drken1215/status/1000371653220618240
  - https://twitter.com/tempura_pp/status/1000371410768879616
  - https://twitter.com/ei1333/status/1000371402866806785
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 9:00-9:13 AC
const int MAX_N=3e5+10;
int N;
string S;
int cum[MAX_N];
LL solve() {
  LL res=MAX_N;
  ZERO(cum);
  REP(i,N) cum[i+1]=cum[i]+(S[i]=='E');
  REP(i,N) {
    int le=cum[i],lw=i-le,re=cum[N]-cum[i+1],rw=N-i-1-re;
    LL x=lw+re;
//    dump3(i,le+rw,lw+re);
//    dump4(le,lw,re,rw);
    SMIN(res,x);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S;
  cout<<solve()<<endl;
  return 0;
}
