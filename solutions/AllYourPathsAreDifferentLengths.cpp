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
 
 9/1/2018
 
 6:20-7:00 give up
 
 9/2/2018
 
 I also tried to represent 0..L-1 in n-ary number.
 However I couldn't find generic way to make arbitrary number.
 
 23:00-23:40 read editorials
 
 9/3/2018
 
 22:50-23:36 add solution

 Editorials:
  - https://img.atcoder.jp/arc102/editorial.pdf
  - https://youtu.be/Jiz6sK6JJNk?t=1831
  - http://betrue12.hateblo.jp/entry/2018/09/02/094954
  - http://naoyat.hatenablog.jp/entry/ARC102
  - http://kmjp.hatenablog.jp/entry/2018/09/02/1000
  - https://minus9d.hatenablog.com/entry/2018/09/02/004610
  - https://creep06.hatenablog.com/entry/20180902/1535844729
   - focusing digit dp technique is good point
 
 It's straighforward to make [0,2^x) numbers by x+1 nodes.
 
 Adding additional edges to complement numbers corresponding to lower bit was not straighforward for me.
 Suppose we have L=10001001010. [0,10000000000) is already buildt.
 Now we want to make [10000000000,10001001010).
 We can add numbers to arbitrary [0,2^x) numbers (2^x<=L).
 If we look at ON bit, we can fill all the numbers with full lower bits.
 In L=10001001010 example...
 
 10001001010
     ^
 We find this ON bit when we look from more significant bit.
 It's possible to represent "111111" from graph that we built.
 Thus we can add edge from node 6 to N with weight "10000000000".
 Now we covered [10000000000,10001000000). We can keep same process for lower ON bits as well.
 
 By looking from left to right bits, filling by focusing on ON bit is similar to digit dp.
 
 Summary:
  - making arbitrary number with binary representation is very typical
  - from special case 2^x-1, greedily make arbitrary number y (<2^(x+1)) is also typical
  - If we are reducing problems to binary digits, focusing on ON bit may be useful.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG AllYourPathsAreDifferentLengths.cpp && ./a.out
//const int MAX_N=1e5+1;
int L;
//LL A[MAX_N];
void solve() {
  vector<III> E;
  int n=0,l=L;
  while(l>0) l/=2,++n;
  --n;
//  dump(n);
  REP(i,n) {
    E.emplace_back(i,i+1,0);
    E.emplace_back(i,i+1,1<<i);
  }
  int w=1<<n;
  for(int i=n-1; i>=0; --i) {
    if((L>>i)&1) {
      E.emplace_back(i,n,w);
//      dump3(i,n,w);
      w|=1<<i;
    }
  }
  assert(n<20);
  assert(SZ(E)<=60);
  cout<<n+1<<" "<<SZ(E)<<endl;
  FORR(t,E) {
    int u,v,w; tie(u,v,w)=t;
    cout<<u+1<<" "<<v+1<<" "<<w<<endl;
  }
}

void test() {
  FORE(l,2,1e6) {
    bool ok=false;
    FORE(x,1,60)FOR(y,1,20) {
      int rem=l-pow(x,y);
      if(rem<0) continue;
      if(rem>60-x*y)  continue;
      dump4(l,x,y,rem);
      ok=true;
      goto done;
    }
  done:
    assert(ok);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  cin>>L;
//  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
