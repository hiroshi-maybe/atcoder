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
 
 5:51-6:17 AC
 
 Editorials:
  - https://img.atcoder.jp/arc102/editorial.pdf
  - https://youtu.be/Jiz6sK6JJNk?t=1302
  - http://drken1215.hatenablog.com/entry/2018/09/02/011000
   - very detailed editorials as usual 👏
  - https://pytoeeei.hatenadiary.jp/entry/2018/09/03/000000
  - http://betrue12.hateblo.jp/entry/2018/09/02/094954
  - https://noss.hatenablog.com/entry/2018/09/02/000500
  - http://naoyat.hatenablog.jp/entry/ARC102
  - https://qiita.com/nomikura/items/590922f179f6f6ce69c2
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N,K;
//LL A[MAX_N];
LL f(int x) {
  return N/K+(x<=(N%K));
}
void solve() {
  LL res=f(K)*f(K)*f(K);
  dump(res);
  FOR(a,1,K) if(2*a%K==0) {
    LL fa=f(a),fb=f(K-a);
    dump4(a,K-a,fa,fb);
    res+=fa*fa*fb;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
//  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
