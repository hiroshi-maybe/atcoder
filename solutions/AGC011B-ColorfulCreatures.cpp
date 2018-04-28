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
 
 4/28/2018

 10:15-10:33 analysis
 10:34-10:37 implement and got AC
 
 Edigorials:
  - https://atcoder.jp/img/agc015/editorial.pdf
  - https://youtu.be/cJ-WjtA34GQ?t=818
  - https://kimiyuki.net/blog/2017/03/12/agc-011-b/
  - http://mtsd-programming.hatenablog.com/entry/2017/03/12/234923
  - http://hamayanhamayan.hatenablog.jp/entry/2017/03/13/002224
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int N;
const int MAX_N=100001;
LL A[MAX_N];
LL solve() {
  sort(A,A+N);
  LL sum=A[0];
  int res=1;
  FOR(i,1,N) {
    if(2*sum<A[i]) res=1;
    else res+=1;
    sum+=A[i];
  }
  return res;
}

int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  return 0;
}
