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
 
 20:45-21:26 AC
 
 Editorials:
  - https://img.atcoder.jp/arc100/editorial.pdf
   - Pre-computing optimal cut for center cut `i` by two pointers
   - O(N) time algorithm while binary search works in O(N*lg N) time
 
 Tweets:
  - https://togetter.com/li/1242706
  - https://twitter.com/ei1333/status/1013409468955017218
  - https://twitter.com/beet_aizu/status/1013409562953568258
  - https://twitter.com/konjo_p/status/1013409636957818880
  - https://twitter.com/_TTJR_/status/1013409649825964032
  - https://twitter.com/rickytheta/status/1013409676304642048
  - https://twitter.com/_olphe/status/1013409803400384513
  - https://twitter.com/tanakh/status/1013410008002727941
  - https://twitter.com/btk15049/status/1013410235275362304
  - https://twitter.com/satanic0258/status/1013410773215862786
  - https://twitter.com/hamko_intel/status/1013411491041570816
  - https://twitter.com/kuuso1/status/1013412543396638721
 
 Key:
  - brute-force positions of center cut
  - find "equal" cut in left and right segments with binary search or two pointers
 
 Summary:
  - I was not very confident about guess that optimal cut of left/right segment is equal cut. However it worked
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 20:45-21:26 AC
const int MAX_N=2e5+1;
int N;
LL A[MAX_N];
//LL cum[MAX_N+1];
void solve() {
  vector<LL> cum(N+1);
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+A[i];
  
  LL res=1e16;
  FOR(i,2,N-1) {
    LL lsum=cum[i],rsum=cum[N]-cum[i];
    auto it1=lower_bound(cum.begin(),cum.begin()+i,lsum/2);
    int p0=it1-cum.begin();
    int P0[2]={p0,p0-1};
    auto it2=lower_bound(cum.begin()+i,cum.end(),lsum+rsum/2);
    int p1=it2-cum.begin();
    int P1[2]={p1,p1-1};
    
    REP(k1,2) REP(k2,2) {
      int p0=P0[k1],p1=P1[k2];
      if(p0==i||p0==0) continue;
      if(p1==i||p1==N) continue;
      LL P=cum[p0],Q=cum[i]-cum[p0];
//      dump3(i,lsum,rsum);
      LL R=cum[p1]-cum[i],S=cum[N]-cum[p1];
      LL x=max({P,Q,R,S})-min({P,Q,R,S});
//      dump3(i,p0,p1);
//      dump4(P,Q,R,S);
//      dump2(i,x);
      SMIN(res,x);
    }

  }
  cout<<res<<endl;
}

void bf() {
  vector<LL> cum(N+1);
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+A[i];
  
  FOR(i,1,N-1) FOR(j,i+1,N) FOR(k,j+1,N) {
    LL P=cum[i],Q=cum[j]-cum[i],R=cum[k]-cum[j],S=cum[N]-cum[k];
    LL x=max({P,Q,R,S})-min({P,Q,R,S});
    if(x==36) {
      dump4(i,j,k,x);
      dump4(P,Q,R,S);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
//  bf();
  return 0;
}
