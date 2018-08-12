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
 
 8/11/2018
 
 15:15-16:00 time is up
 17:30-17:50 read editorials
 
 23:00-24:00 read editorials
 
 Editorials:
  - https://cf16-final.contest.atcoder.jp//data/other/cf16-exhibition-final/editorial.pdf
  - http://wk1080id.hatenablog.com/entry/2018/02/05/123131
  - http://ferin-tech.hatenablog.com/entry/2017/12/18/211329
  - https://kimiyuki.net/writeup/algo/atcoder/codefestival-2016-grand-final-a/
 
 1,2,3,5
 4,5,6,7
 
 In the algorithm in editorials, 6 is matched with 3 and 5 in the buffer.
 However, actually 6 can be matched with 1 and 2. I cannot understand why this algorithm works.
 
 Summary:
  - I cannot understand this solution
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
const LL MOD=1e9+7;
LL A[MAX_N],B[MAX_N];
void solve() {
  vector<pair<LL,int>> imos;
  REP(i,N) imos.emplace_back(A[i],-1),imos.emplace_back(B[i],1);
  sort(imos.begin(),imos.end());
  LL res=1;
  int bal=0;
  REP(i,2*N) {
    LL x; int b; tie(x,b)=imos[i];
    int dt=b;
    if(bal!=0&&(bal>0!=dt>0)) {
      res=res*abs(bal)%MOD;
    }
    bal+=dt;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  solve();
  return 0;
}
