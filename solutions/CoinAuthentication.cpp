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
 
 8/14/2018
 
 16:00-16:33 analysis
 16:49 submit and got WA (output format error)
 17:03 fix output format and got AC
 
 Editorials:
  - https://img.atcoder.jp/code-thanks-festival-2017-open/editorial.pdf
 
 Summary:
  - my first interactive problem in atcoder
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N;
void solve() {
  VI res(N);
  REP(i,(N+4)/5) {
    vector<LL> X(N,0);
    LL base=1;
    LL ext=0;
    int M=0;
    FOR(j,5*i,min(5*(i+1),N)) {
      X[j]=base*1;
      ext+=8*base;
      base*=5LL;
      ++M;
    }
    cout<<"? ";
    REP(j,N) cout<<X[j]<<(j==N-1?'\n':' ');
    fflush(stdout);
    
    LL ans;
    cin>>ans;
    ans-=ext;
//    dump(ans);
    REP(j,M) {
      LL x=ans%5; ans/=5LL;
//      dump4(i,j,5*i+j,x);
      res[5*i+j]=(x%2==1);
    }
  }
  cout<<"! ";
  REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
  fflush(stdout);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  solve();
  return 0;
}
