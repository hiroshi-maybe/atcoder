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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/19/2018
 
 19:50-20:05 analysis
 20:33 Ok. Finally I understood the problem statement.
 21:07 reimplement with fast zeta transform and got AC
 
 Editorials:
  - https://img.atcoder.jp/yahoo-procon2018-qual/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2018/02/11/101334
  - http://algon-320.hatenablog.com/entry/2018/02/11/022639
  - https://kimiyuki.net/writeup/algo/atcoder/yahoo-procon2018-qual-c/
  - http://kazune-lab.net/contest/2018/02/10/yahoo-procon2018-qual/
 
 Summary:
  - I firstly had redundant state in dp. mask is sufficient
  - Nice to come up with fast zeta transform 👍
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=18+1;
int N;
LL X[MAX_N],C[MAX_N],V[MAX_N];
LL memo[1<<18];
LL F[1<<18][MAX_N];

LL f(int mask) {
  LL &res=memo[mask];
  if(res>=0) return res;
  int m=__builtin_popcount(mask);
  int cmask=((1<<N)-1)^mask;
  LL val=F[cmask][m];
  
  dump3(m,mask,val);
  res=val;
  if(m==N-1) {
    dump3(m,mask,val);
    return res=val;
  }
  LL a=1e18;
  REP(i,N) if(((mask>>i)&1)==0) {
    LL b=f(mask|(1LL<<i));
//    dump4(x,mask,i,b);
    SMIN(a,b);
  }
  dump4(m,mask,val,a);
  SMAX(res,a);
  return res;
}

void ztransform_subset(int N, int x) {
  for(int i=0; i<N; ++i) {
    for(int T=0; T<(1<<N); ++T) {
      if ((T>>i)&1) SMAX(F[T][x],F[T^(1<<i)][x]);
    }
  }
}

LL solve() {
  LL bud=0;
  ZERO(F);
  REP(i,N) {
    bud+=X[i];
    REP(mask,1<<N) {
      LL cost=0,val=0;
      REP(i,N) if((mask>>i)&1) {
        cost+=C[i],val+=V[i];
      }
      F[mask][i+1]=cost<=bud?val:0;
    }
    ztransform_subset(N,i+1);
  }
  MINUS(memo);
  return f(0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>X[i];
  REP(i,N) cin>>C[i];
  REP(i,N) cin>>V[i];
  cout<<solve()<<endl;
  return 0;
}
