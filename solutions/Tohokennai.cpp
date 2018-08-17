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
 
 8/16/2018
 
 11:35-12:06 analysis
 12:32 sample #3 does not pass
 17:40-17:56 fixed algorithm bug and got AC
 
 Editorials:
  - https://img.atcoder.jp/bitflyer2018-qual/editorial.pdf
   - there is typo in conditions
  - http://phyllo-algo.hatenablog.com/entry/2018/06/05/005131
  - http://banboooo.hatenablog.com/entry/2018/06/03/025645
   - same as mine
  - https://www.hamayanhamayan.com/entry/2018/06/02/233953
  - http://betrue12.hateblo.jp/entry/2018/06/03/131350
   - this is pointing wrong points in official editorial
  - http://kazune-lab.net/contest/2018/06/02/bitflyer2018-qual/
 
 Sounds like my solution was complex
 
 U: total C(N,3)
 A: X[k]-X[i]<=D
 B: X[j]-X[i]>D
 C: X[k]-X[i]>D and X[j]-X[k]<=D
 
 res=U-A-B-C
 
 Solution in editorial:
 
 A: X[j]-X[i]<=D and X[k]-X[j]<=D
 B: X[i]-X[k]<=D
 
 res=A-B
 
 Summary:
  - Fixing center if we want three variable indices. This seems to be better approach.
  - Subtracting from universe set is not always better. See solutions in editorials.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL D;
LL A[MAX_N];
//LL cum[MAX_N];
void solve() {
  vector<LL> X(N);
  REP(i,N) X[i]=A[i]-A[0];
//  dumpAR(X);
  LL res=1LL*N*(N-1)*(N-2)/6;
  REP(i,N) {
    auto k=upper_bound(X.begin(),X.end(),X[i]+D)-X.begin();
    if(k>0)--k;
    LL a=1LL*(k-i)*(k-i-1)/2;
    
    LL b=0,c=0;
    auto j=upper_bound(X.begin(),X.end(),X[i]+D)-X.begin();
    if(j<N) {
      b=(N-j-1)*(N-j)/2;
    
      auto x=lower_bound(X.begin(),X.end(),X[i]-D)-X.begin();
      c=(i-x)*(N-j);
    }
//    dump4(i,a,b,c);
    res-=a+b+c;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>D;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
