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
 
 8/13/2018
 
 16:10-16:15 analysis
 16:35 RE
 16:47 bug fix and got AC
 
 Editorials:
  - https://img.atcoder.jp/code-festival-2017-qualc/editorial.pdf
  - https://kimiyuki.net/writeup/algo/atcoder/code-festival-2017-qualc-c/
  - http://prd-xxx.hateblo.jp/entry/2017/10/26/011420
  - http://mhiroaki.hatenablog.com/entry/2017/10/25/182802
 
 Summary:
  - Simply use two pointers without using extra space
  - It's possible to reject invalid string by linear scan
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
//int N;
string S;
//LL A[MAX_N];
int solve() {
  int N=SZ(S);
  vector<pair<char,int>> X={{'#',-1}};
  string t; REP(i,N)if(S[i]!='x') {
    t+=S[i];
    X.emplace_back(S[i],i);
  }
  X.emplace_back('#',N);
  string tt=t; reverse(tt.begin(),tt.end());
  if(tt!=t) return -1;
  int M=SZ(X);
  
//  REP(i,M) dump3(i,X[i].first,X[i].second);
  
  int l=(M-1)/2,r=M%2==0?l+1:l;
  --l,++r;
  int res=0;
  while(l>=0) {
    assert(X[l].first==X[r].first);
    
//    dump4(X[l].first,X[l].second,X[r].first,X[r].second);
    int d1=X[l+1].second-X[l].second,d2=X[r].second-X[r-1].second;
    res+=max(d1,d2)-min(d1,d2);
//    dump3(d1,d2,max(d1,d2)-min(d1,d2));
    --l,++r;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  cout<<solve()<<endl;
  return 0;
}
