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
 
 9:15-22:06 AC
 
 5/28/2018
 
 Editorials:
  - https://img.atcoder.jp/arc098/editorial.pdf
  - http://hamayanhamayan.hatenablog.jp/entry/2018/05/26/234740
  - http://koishisolo.hatenablog.com/entry/2018/05/27/012145
  - https://twitter.com/_TTJR_/status/1000401846907715585
 
 Tweets:
  - https://togetter.com/li/1231142
  - https://twitter.com/evima0/status/1000371232053780486
  - https://twitter.com/Darsein/status/1000373922250899457
  - https://twitter.com/ei1333/status/1000371402866806785
  - https://twitter.com/tempura_pp/status/1000371410768879616
  - https://twitter.com/drken1215/status/1000371653220618240
 
 Summary:
  - It took more time to get ACC due to debug code 👎
  - My solution is not strictly using two pointers. Official editorial is mentioning to it too
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 9:15-22:06 AC
const int MAX_N=2e5+1;
int N;
LL A[MAX_N];
int L1[22],L2[22];

string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}

LL solve() {
  /*
  REP(i,N) {
    string x=n2bin(A[i]);
    dump2(i,x);
  }*/
  
  LL res=0;
  MINUS(L1),MINUS(L2);
  REP(i,N) {
    int x=N;
    REP(j,22) {
      int a=(A[i]&(1<<j))?L1[j]:L2[j];
//      dump4(i,L1[j],L2[j],a);
      SMIN(x,i-a);
      if(A[i]&(1<<j)) {
        L2[j]=L1[j];
        L1[j]=i;
      }
    }
//    dump2(i,x);
    res+=x;
/*
    int xx=1;
    REPE(j,i) {
      int ex=0,sum=0;
      FORE(k,j,i) ex^=A[k],sum+=A[k];
      if(ex==sum) {
        xx=i-j+1;
        break;
      }
    }
    if(xx!=x) {
      dumpAR(L2);
      dumpAR(L1);
      dump3(i,xx,x);
    }
    assert(xx==x);*/
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  return 0;
}
