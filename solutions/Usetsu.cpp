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
 
 8/28/2018
 
 16:25-16:50 analysis
 17:23 submit and got WA
 17:32 fix overflow bug and got AC
 
 Editorials:
  - https://img.atcoder.jp/mujin-pc-2018/editorial.pdf
  - https://youtu.be/2ZfEcgV8Sso?t=2222
  - http://betrue12.hateblo.jp/entry/2018/08/05/032043
  - http://hamko.hatenadiary.jp/entry/2018/08/05/011621
  - https://kimiyuki.net/writeup/algo/atcoder/mujin-pc-2018-c/
  - http://xxxasdfghjk999.hatenablog.jp/entry/2018/08/05/001828
  - https://www.hamayanhamayan.com/entry/2018/08/05/091026
  - http://naoyat.hatenablog.jp/entry/mujin-pc-2018
  - http://d.hatena.ne.jp/merom686/20180804/1533397455
  - https://31536000.hatenablog.com/entry/2018/08/05/002002
  - https://babcs2035.hateblo.jp/entry/2018/08/17/083751
 
 Clean implementation:
  - https://mujin-pc-2018.contest.atcoder.jp/submissions/2946543
 
      *
      *
      *
 *****x
 
 a*b from above path was clear for me. I should have figured out (a+b)*(c+d) from symmetric property.
 Also adjusting index to calc by (U[i][j]+D[i][j])*(L[i][j]+R[i][j]) is very clean. I should use it from next time.
 
 Summary:
  - implementation was not light
  - Computing four directions at once as described in editorial is smart and easier
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2000+10;
int N,M;
string G[MAX_N];
LL mx2[MAX_N][MAX_N];
LL mx[MAX_N][MAX_N];
LL cum[MAX_N][MAX_N];
LL cum2[MAX_N][MAX_N];

const LL Inf=1e17;
LL f(int H, int W) {
  ZERO(cum);
  REP(j,W) {
    cum[0][j]=max(0LL,mx[0][j]);
    FOR(i,1,H) cum[i][j]=max(0LL,cum[i-1][j]+mx[i][j]);
  }
  ZERO(cum2);
  REP(i,H) {
    cum2[i][0]=max(0LL,mx[i][0]);
    FOR(j,1,W) cum2[i][j]=max(0LL,cum2[i][j-1]+mx[i][j]);
  }
/*
  REP(i,H) {
    REP(j,W) cout<<cum[i][j]<<" ";
    cout<<endl;
  }*/
  
  LL res=0;
  FOR(i,1,H) {
    FOR(j,1,W) {
      LL x=max(0LL,cum2[i][j-1]*cum[i-1][j]);
//      dump4(i,j,cum2[i][j-1],cum[i-1][j]);
      if(mx[i][j]!=-Inf)res+=x;
    }
  }
//  dump(res);
  return res;
}

void rotate(int N, int M) {
  ZERO(mx2);
  REP(i,N)REP(j,M) mx2[M-j-1][i]=mx[i][j];
  swap(mx2,mx);
}

void solve_org() {
  REP(i,N)REP(j,M) mx[i][j]=G[i][j]=='#'?-Inf:1;
  LL res=0;
  REP(i,4) {
    int H=i%2==0?N:M;
    int W=i%2==0?M:N;
    LL x=f(H,W);
    res+=x;
//    dump2(i,res);
    rotate(H,W);
  }
  cout<<res<<endl;
}

int U[MAX_N][MAX_N],D[MAX_N][MAX_N],L[MAX_N][MAX_N],R[MAX_N][MAX_N];

void solve() {
  ZERO(U),ZERO(D),ZERO(L),ZERO(R);

  REP(j,M) for(int i=N-1; i>0; --i) if(G[i][j]=='.') U[i-1][j]=U[i][j]+1;
  REP(j,M) REP(i,N-1) if(G[i][j]=='.') D[i+1][j]=D[i][j]+1;
  REP(i,N) for(int j=M-1; j>0; --j) if(G[i][j]=='.') R[i][j-1]=R[i][j]+1;
  REP(i,N) REP(j,M-1) if(G[i][j]=='.') L[i][j+1]=L[i][j]+1;

  LL res=0;
  REP(i,N)REP(j,M) if(G[i][j]=='.')res+=(U[i][j]+D[i][j])*(L[i][j]+R[i][j]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N) cin>>G[i];
  solve();
  return 0;
}
