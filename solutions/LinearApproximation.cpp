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
 
 7/2/2018 ARC100
 
 20:34-20:43 AC
 
 Editorials:
  - https://img.atcoder.jp/arc100/editorial.pdf
  - https://yamakasa3.hatenablog.com/entry/2018/07/02/041604
  - https://qiita.com/prtoku/items/98a6203422ef1599d7eb#c---linear-approximation
 
 Tweets:
  - https://togetter.com/li/1242706
  - https://twitter.com/ei1333/status/1013409468955017218
  - https://twitter.com/beet_aizu/status/1013409562953568258
  - https://twitter.com/konjo_p/status/1013409636957818880
  - https://twitter.com/_TTJR_/status/1013409649825964032
  - https://twitter.com/rickytheta/status/1013409676304642048
  - https://twitter.com/_olphe/status/1013409803400384513
  - https://twitter.com/tanakh/status/1013410008002727941
  - https://twitter.com/ei1333/status/1013410030236794885
  - https://twitter.com/btk15049/status/1013410235275362304
  - https://twitter.com/tempura_pp/status/1013410662481997825
  - https://twitter.com/satanic0258/status/1013410773215862786
  - https://twitter.com/hamko_intel/status/1013411491041570816
  - https://twitter.com/kuuso1/status/1013412543396638721
 
 Key:
  - median or trinary search
 
 Summary:
  - After `A[i]-i`, this is typical problem
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 20:34-20:43 AC
const int MAX_N=2e5+1;
int N;
LL A[MAX_N];
void solve() {
//  LL res=1e18;
  sort(A,A+N);
  LL mid=A[N/2];
  LL res=0;
  REP(i,N) res+=abs(A[i]-mid);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i],A[i]-=(i+1);
  solve();
  return 0;
}
