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
 
 6/3/2018 AGC025B
 
 22:30-22:50 give up
 
 6/4/2018
 
 24:20- read editorials and add solution
 
 Editorial:
  - https://img.atcoder.jp/agc025/editorial.pdf
  - https://youtu.be/Ommfmx2wtuY?t=2568
  - http://seica-at.hatenablog.com/entry/2018/06/04/144925
  - http://yosupo.hatenablog.com/entry/2018/06/04/004619
  - http://drken1215.hatenablog.com/entry/2018/06/04/131800
 
 Tweets:
  - https://togetter.com/li/1233682
  - https://twitter.com/0x19f/status/1003324634547097600
  - https://twitter.com/_TTJR_/status/1003277833244831744
  - https://twitter.com/beet_aizu/status/1003278189601304576
  - https://twitter.com/drken1215/status/1003278214578360320
  - https://twitter.com/ei1333/status/1003278396565016576
  - https://twitter.com/tanakh/status/1003279983647715328
 
 Simple solution by @tourist: https://beta.atcoder.jp/contests/agc025/submissions/2609185
 
 Separating strategy of each person may be a good start.
 Suppose given intervals are fixed. What Takahashi can do?
 Usually edge of interval is sufficient in some of problems.
 This works in one of two cases too.
 
 i) Takahashi is in the middle of next interval
  -> No need to move
 ii) Takahashi is out of next interval
  -> move to left or right edge
 
 Takahashi's optimal strategy is now clear.
 We need to know Aoki's strategy.
 
 Intuitively Aoki wants Takahashi to move left and right alternatively.
 In such a case, result = ∑ { 2*(L[i]-R[i]) : i ∈ S⊆{0,..,N-1} }
 Some of intervals can be ignored to form this optimal result.
 Thus, it's possible to pick L[i] and R[i] greedily.
 
 Key:
  - Optimal stragegy of both players are independent
  - If extremely optimal subset is found, abundant intervals does not destroy it
   - @drken's editorial is pretty impressive
   - This is proving that necessary condition is actually sufficient
   - @yosupo's comment is saying the same thing
    - Figure out upper-bound of the result
    - It's actually possitle to always form it (sufficient)
 
 Summary:
  - I had no idea how to order intervals 😞
  - Showing independence of each action is a key
   - Pin given intervals. Takahashi's stretegy depends on Aoki's strategy? If not, they are independent
  - Another key is showing sufficiency from necessary extreme condition (upper-bound)

 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:40-
const int MAX_N=1e5+1;
int N;
LL L[MAX_N],R[MAX_N];
LL solve() {
  sort(L,L+N,greater<LL>());
//  sort(L+N,L);
  sort(R,R+N);
  
  LL res=0,cur=0;
  REP(i,N) {
    cur+=L[i],SMAX(res,cur);
    cur-=R[i],SMAX(res,cur);
  }
  cur=0;
  REP(i,N) {
    cur-=R[i],SMAX(res,cur);
    cur+=L[i],SMAX(res,cur);
  }
  return 2*res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>L[i]>>R[i];
  cout<<solve()<<endl;
  return 0;
}
