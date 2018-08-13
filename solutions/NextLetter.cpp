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
 
 8/12/2018
 
 16:00-16:16 submit and got AC
 
 Editorials:
  - http://code-festival-2016-quala.contest.atcoder.jp/data/other/code-festival-2016-quala/editorial.pdf
  - http://kmjp.hatenablog.jp/entry/2016/10/12/0900
  - https://ykmaku.hatenablog.com/entry/2018/07/09/010530
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2016-quala-c/
  - http://competitive-kivantium.hateblo.jp/entry/2016/09/25/003559
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
string S;
int K;
void solve() {
  int N=SZ(S);
  VI X;
  REP(i,N) {
    int a=S[i]-'a';
    int needs=(26-a)%26;
    if(needs<=K) S[i]='a',K-=needs;
    else X.push_back(i);
  }
  if(SZ(X)==0) {
    int a=S[N-1]-'a';
    S[N-1]=('a'+(a+K)%26);
  } else {
    int i=X.back();
    int a=S[i]-'a';
    assert(a+K<26);
    S[i]=('a'+a+K);
  }
  cout<<S<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S>>K;
  solve();
  return 0;
}
