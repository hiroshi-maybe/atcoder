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
 
 8/19/2018
 
 15:50-15:59 analysis
 16:00-16:15 implement and got AC
 
 Editorials:
  - https://img.atcoder.jp/bitflyer2018-final/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2018/07/01/093213
  - http://betrue12.hateblo.jp/entry/2018/06/30/235952
  - https://kimiyuki.net/writeup/algo/atcoder/bitflyer-2018-final-b/
  - http://drken1215.hatenablog.com/entry/2018/07/01/133700
  - https://reqly.hatenablog.com/entry/2018/07/01/022949
  - http://baitop.hatenadiary.jp/entry/2018/06/30/205459
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,Q;
LL X[MAX_N];
LL cum[MAX_N];
LL C[MAX_N],D[MAX_N];
void solve() {
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+X[i];
  REP(i,Q) {
    LL c=C[i],d=D[i];
    int r=lower_bound(X,X+N,c+d)-X;
    int l=lower_bound(X,X+N,c-d)-X;
    int p=lower_bound(X,X+N,c)-X;
    
    LL x=d*(N-(r-l));
    LL y=(cum[r]-cum[p])-c*(r-p);
    LL z=c*(p-l)-(cum[p]-cum[l]);
//    dump4(i,l,p,r);
//    dump4(i,x,y,z);
    LL res=x+y+z;
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Q;
  REP(i,N) cin>>X[i];
  REP(i,Q) cin>>C[i]>>D[i];
  solve();
  return 0;
}
