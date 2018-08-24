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
 
 8/21/2018
 
 20:35-20:56 analysis
 21:27 OMG. maximal total number of kill is 1000 (>100)
 21:35 give up
 
 21:35-23:25 read articles of partition number
 
 8/23/2018
 
 16:30-16:55 implement library of partition number and got AC
 
 Editorials:
  - https://niconare.nicovideo.jp/watch/kn2845
  - http://kmjp.hatenablog.jp/entry/2018/01/16/0900
  - http://ferin-tech.hatenablog.com/entry/2018/01/13/222323
  - http://hamko.hatenadiary.jp/entry/2018/01/17/114214
  - https://www.hamayanhamayan.com/entry/2018/01/14/103600
  - https://kimiyuki.net/writeup/algo/atcoder/dwacon2018-prelims-c/
  - http://fluffyowl.hatenablog.com/entry/2018/01/16/224132
  - http://condensed-matter.hatenablog.com/entry/2018/01/15/182333
  - https://babcs2035.hateblo.jp/entry/2018/06/07/221022
  - https://pitsbuffersolution.com/blog/articles/dwacon2018_prelims.php#editorial_C
 
 References:
  - Partition number
   - http://d.hatena.ne.jp/incognita/20110305/1299344781
   - http://drken1215.hatenablog.com/entry/2018/01/16/222843
   - https://ja.wikipedia.org/wiki/%E5%88%86%E5%89%B2%E6%95%B0#%E8%A3%9C%E5%8A%A9%E5%87%BD%E6%95%B0
   - Ant book section 2-3 dp
  - http://kuno4n.hateblo.jp/entry/2013/12/14/140104#count8
  - https://twitter.com/mamemame_fujita/status/952169916450287616
 
 Summary:
  - I couldn't solve partition function. Approach was correct
  - Read constraints more carefully
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e2+1;
const int MAX_SUM=1e3+1;
int N,M;
VI A,B;

const LL MOD=1e9+7;

/*
 
// TLE code
LL memo[MAX_N][MAX_SUM][MAX_SUM];

LL g(int buck, int rem, int last) {
  if(buck==0) return rem==0;
  if(rem<last) return 0;
  LL &res=memo[buck][rem][last];
  if(res>=0) return res;
  res=0;
  FORE(x,last,rem) {
    res+=g(buck-1,rem-x,x),res%=MOD;
  }
  return res;
}*/

struct Partition {
public:
  long long memo[MAX_SUM][MAX_SUM];
  Partition() {
    memset(memo, -1, sizeof memo);
  }
  long long query(int n, int k) {
    assert(n<MAX_SUM&&k<MAX_SUM);
    return f(n,k);
  }
private:
  long long f(int n, int k) {
    if(n<0) return 0;
    if(k==0) return n==0;
    if(n==0) return 1;
    
    long long &res=memo[n][k];
    if(res>=0) return res;
    
    long long a=f(n-k,k),b=f(n,k-1);
    return res=(a+b)%MOD;
  }
} Part;

VI G;
LL memo2[MAX_N][MAX_SUM];
LL f(int i, int rem) {
  int N=SZ(G);
  if(i==N) return rem==0;
  LL &res=memo2[i][rem];
  if(res>=0) return res;
  res=0;
  REPE(x,rem) {
    //res+=g(G[i],x,0),res%=MOD;
    
    // TLE
    //    LL y=g[i],x,0);
    LL y=Part.query(x,G[i]);
    LL z=f(i+1,rem-x);
//    dump4(i,G[i],x,y);
    y=y*z%MOD;
    (res+=y)%=MOD;
  }
  return res;
}

LL go(VI &X, VI &Y) {
  int sum=accumulate(Y.begin(),Y.end(),0);
  G.clear();
  int cur=X[0],cnt=1;
  FOR(i,1,SZ(X)) {
    if(X[i]==X[i-1]) ++cnt;
    else {
      G.push_back(cnt);
      cnt=1,cur=X[i];
    }
  }
  if(cnt>0) G.push_back(cnt);
//  dump(sum);
//  dumpAR(G);
  MINUS(memo2);
  return f(0,sum);
}

LL solve() {
//  MINUS(memo);
  LL x=go(A,B),y=go(B,A);
//  LL x=1,y=1;
//  dump(g(4,5,0));
//  dump2(x,y);
  return x*y%MOD;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  A.resize(N),B.resize(M);
  REP(i,N) cin>>A[i];
  REP(i,M) cin>>B[i];
  cout<<solve()<<endl;
  return 0;
}
