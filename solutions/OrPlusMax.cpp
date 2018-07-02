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
 
 7/1/2018 ARC100
 
 21:30-22:10 time is up
 
 7/2/2018
 
 17:30-18:32 Read editorials and add solution
 
 Editorials:
  - https://img.atcoder.jp/arc100/editorial.pdf
 
 Tweets:
  - https://togetter.com/li/1242706
  - Fast Zeta Transform
   - https://twitter.com/kroton_pc/status/1013420327076970497
    - Analysis process by relaxation of conditions 👍
   - https://twitter.com/satanic0258/status/1013410773215862786
   - https://twitter.com/satanic0258/status/1013411764925394944
   - https://twitter.com/rickytheta/status/1013409676304642048
   - https://twitter.com/ei1333/status/1013411675607724032
   - https://twitter.com/osrehun/status/1013412125245562883
   - https://twitter.com/konjo_p/status/1013409636957818880
   - https://twitter.com/btk15049/status/1013410235275362304
  - O(3^N) bit dp
   - https://twitter.com/beet_aizu/status/1013409562953568258
   - https://twitter.com/tempura_pp/status/1013410662481997825
 
 Fast zeta transform
  - https://topcoder.g.hatena.ne.jp/iwiwi/20120422/1335065228
   - most famous article
  - http://d.hatena.ne.jp/todo314/20120614/1339695202
   - walk through
  - https://www.slideshare.net/wata_orz/ss-12131479
   - original article
  - http://d.hatena.ne.jp/simezi_tan/20130522/1369203086
   - proof
 
 @yosupo's solution: https://beta.atcoder.jp/contests/arc100/submissions/2776687
 
 Key:
  - i|j ⊆ K => i ⊆ K && j ⊆ K
 
 Summary:
  - I had some of random ideas though, I couldn't solve
   - inclusion exclusion principle
   - keeping only two bits
   - recurrence relation with subset
   - 3^N subset enumeration
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:30-22:10 time is up
const int MAX_N=(1<<18)+1;
int N;
LL A[MAX_N];
II dp[MAX_N][2];
void solve() {
  ZERO(dp);
  REP(i,1<<N) dp[i][0]={A[i],i},dp[i][1]={0,-1};
  REP(i,N) REP(mask,1<<N) if((mask>>i)&1) {
    II a=dp[mask][0],b=dp[mask][1],c=dp[mask^(1<<i)][0],d=dp[mask^(1<<i)][1];
    if(a==c||b==c) c={0,-1};
    if(a==d||b==d) d={-1,-2};
    if(b<c) swap(b,c);
    if(a<b) swap(a,b);
    if(d>c) swap(c,d);
    if(c>b) swap(b,c);
    dp[mask][0]=a,dp[mask][1]=b;
  }
  
  int cur=0;
  FOR(mask,1,1<<N) {
//    dump4(mask,dp[mask][0].first,dp[mask][0].second,dp[mask][0].first+dp[mask][1].first);
//    dump3(mask,dp[mask][1].first,dp[mask][1].second);
    cur=SMAX(cur,dp[mask][0].first+dp[mask][1].first);
    cout<<cur<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,1<<N) cin>>A[i];
  solve();
  return 0;
}
