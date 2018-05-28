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
 
 5/26/2018
 
 22:10-22:30 give up
 
 5/28/2018
 
 17:20-17:53 read editorials and add solution
 
 Editorials:
  - https://img.atcoder.jp/arc098/editorial.pdf
  - http://yosupo.hatenablog.com/entry/2018/05/26/225352
   - great description about process 👍
  - http://kazune-lab.net/contest/2018/05/26/arc098/
 
 Tweets:
  - https://togetter.com/li/1231142
  - https://twitter.com/evima0/status/1000371884280627200
  - https://twitter.com/Darsein/status/1000373922250899457
  - https://twitter.com/satanic0258/status/1000372821275504640
  - https://twitter.com/rickytheta/status/1000373068110315522
  - https://twitter.com/beet_aizu/status/1000373328463319041
  - https://twitter.com/ei1333/status/1000371402866806785
  - https://twitter.com/tempura_pp/status/1000371410768879616
  - https://twitter.com/drken1215/status/1000371653220618240
 
 There are two variables X and Y. Also N is small. N^2 works.
 One plan is fixing X or Y and solve the subproblem in O(N) or O(N*lg N).
 Fixing X or Y which is preferred? Fixing Y will make some split sub sequences.
 In a subsequence S, we can select at most |S|-K+1 smallest numbers greedily.
 => select them, concatenate, sort and pick up Q-th smallest one.
 
 Key:
  - There exists two variables. Also N^2 works -> fixing one variable
  - In split sequence, we can greedily select smallest Q - 1 numbers
 
 Summary:
  - @yosupo's analysis to associate two variables with size constraint is quite impressive 🤔
  - I was wondering if it's a DP to remove and concatenate. However it was not correct.
  - Fixing approach is by depth first thinking does not work in many cases
  - Try more variable approaches if in stuck. Fixing one variable is typical approach too.
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2001;
int N,K,Q;
LL A[MAX_N];
const LL Inf=1e10;
LL f(int p) {
  LL piv=A[p];
  vector<vector<LL>> X;
  vector<LL> cur;
  REP(i,N) {
    if(A[i]<piv) {
      if(SZ(cur)>=K) X.push_back(cur);
      cur.clear();
    } else {
      cur.push_back(A[i]);
    }
  }
  if(SZ(cur)>=K) X.push_back(cur);
//  dump2(p,piv);
  vector<LL> Y;
  FORR(x,X) {
    sort(x.begin(),x.end());
//    dumpAR(x);
    REP(i,SZ(x)-K+1) Y.push_back(x[i]);
  }
  sort(Y.begin(),Y.end());
//  dumpAR(Y);
  return SZ(Y)<Q?Inf:Y[Q-1]-piv;
}

LL solve() {
  LL res=Inf;
  REP(i,N) SMIN(res,f(i));
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K>>Q;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  return 0;
}
