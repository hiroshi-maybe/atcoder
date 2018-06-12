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
 
 6/11/2018
 
 14:35-15:15 give up
 15:30-16:00 read editorials
 18:45-19:04 pause
 
 6/12/2018
 
 11:00-11:44 got AC
 
 Editorials:
  - https://youtu.be/6ZP8JyGsQBs?t=1094
  - http://agc007.contest.atcoder.jp/data/agc/007/editorial.pdf
  - http://hamko.hatenadiary.jp/entry/2018/01/04/110502
  - http://yousei.hateblo.jp/entry/2016/11/20/202001
  - https://kimiyuki.net/writeup/algo/atcoder/agc-007-b/

 Below gives baseline A[P[i-1]]+B[P[i-1]]=A[P[i]]+B[P[i]]=A[P[i+1]]+B[P[i+1]]=...
 
 A:     a,       a+x,     a+2*x, .. , a+N*x
 B: a+N*x, a+(N-1)*x, a+(N-2)*x, .. ,     a
 ---------------------------------------------
  2*a+N*x,   2*a+N*x,   2*a+N*x, .. , 2*a+N*x
 
 Summary:
  - bucket or inversion. I couldn't figure out => bucket
  - make simple sequence which satisfies part of conditions. Modify the sequence to satisfy the condition
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 14:35-15:15 give up
const int MAX_N=2e4+1;
int N;
LL P[MAX_N];
LL A[MAX_N],B[MAX_N];

LL BU=MAX_N+10;
void test() {
  int prev=-1e9;
  REP(i,N) {
    if(i>0) assert(A[i]>A[i-1]&&B[i]<B[i-1]);
    LL a=A[P[i]],b=B[P[i]],x=a+b;
    assert(1<=a&&a<=1e9);
    assert(1<=b&&b<=1e9);
    assert(prev<x);
    prev=x;
  }
}

void solve() {
  REP(i,N) A[i]=i*BU+1,B[N-i-1]=i*BU+1;
  REP(i,N) A[P[i]]+=i;
  test();
  REP(i,N) cout<<A[i]<<(i==(N-1)?"\n":" ");
  REP(i,N) cout<<B[i]<<(i==(N-1)?"\n":" ");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) {
    int x;
    cin>>x;
    --x;
    //P[x]=i;
    P[i]=x;
  }
    
  solve();
  return 0;
}
