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
 
 8/13/2018
 
 16:50-17:07 analysis
 17:18 submit and got WA
 17:38 looked at failed test case, fixed bug and got AC
 
 Editorials:
  - https://img.atcoder.jp/code-festival-2017-quala/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2017/09/24/012523
  - https://kimiyuki.net/writeup/algo/atcoder/codefestival-2017-quala-c/
  - http://phwinx.hatenablog.com/entry/2017/09/30/020650
 
 Summary:
  - It took some time to find a bug..
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int H,W;
int cnt[26];
bool solve() {
  int x4=(H/2)*(W/2);
  dump(x4);
  REP(i,26) if(x4>0) {
    int a=min(cnt[i]/4,x4);
    x4-=a,cnt[i]-=4*a;
  }
  dump(x4);
  if(x4>0) return false;
  int x2=0;
  if(H%2==1)x2+=(W/2);
  if(W%2==1)x2+=(H/2);
  dump(x2);
  REP(i,26) if(x2>0) {
    int a=min(cnt[i]/2,x2);
    x2-=a,cnt[i]-=2*a;
  }
  dump(x2);
  if(x2>0) return false;
//  int x1=((H%2==1)&&(W%2==1));
  int x1=(H%2==1&&W%2==1);
  dump(x1);
  return accumulate(cnt,cnt+26,0)==x1;
}

string yes="Yes",no="No";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>H>>W;
  REP(i,H)REP(j,W) {
    char c; cin>>c;
    cnt[c-'a']++;
  }
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
