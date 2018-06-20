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
 
 6/20/2018
 
 12:45-13:20 1WA
 13:21-13:24 fix to look at smaller value around middle and got AC
 
 Theorem: C(max{a},k) is maximal
 
 Define two elements as n1 = max{ a : a∈A }, n2∈A, n2<n1
 Suppose there exists some k s.t. C(n1,k1)<C(n2,k2), k1,k2∈A
 Note that `k1` is maximal for `n1` (closest to n1/2 in set `A`)
 
 i) k1!=k2
 
 In this case, k2!=n2. Otherwise, C(n2,k2)=1 which cannot be larger than C(n1,k1)
 However C(n1,k2)>C(n2,k2) which contradicts that C(n1,k1) is maximal for n1
 
 ii) k1==k2
 
 Apparently C(n1,k1)>C(n2,k2) holds. That is contradiction.
 
 From above discussion, C(n1,k1) is maximal. `k1` can be chosen from two values closest to n1/2
 
 Editorials:
  - https://img.atcoder.jp/arc095/editorial.pdf
  - https://youtu.be/RwWljbtCrPA?t=1553
   - fixing `k` in analysis is impressive
 
 Key:
  - C(n,k) is maximal when k is closest to n/2
  - Maximal value can be chosen from max {a:a∈A}
 
 Summary:
  - I tried to solve by iterating from A[0] to A[N-1]. However it's hard to solve in runtime
  - It took much time to start looking for greedy solution. I should discard search approach earlier
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
vector<int> A(MAX_N);
void solve() {
  sort(A.begin(),A.end());
  int n=A.back();
  auto it=lower_bound(A.begin(),A.end(),n/2);
  if(*it==n) --it;
  int k1=*it,k2=0;
  if(it!=A.begin()) k2=*(--it);
  int k=abs(k1-n/2)>abs(k2-n/2)?k2:k1;
  cout<<n<<' '<<k<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
