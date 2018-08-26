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
 
 8/25/2018
 
 15:00-15:20 analysis
 15:35 submit and got WA
 15:36-16:10 bug fix and got AC (6WA)
 
 Editorials:
  - https://img.atcoder.jp/apc001/editorial.pdf
  - http://ferin-tech.hatenablog.com/entry/2018/02/06/164811
  - https://www.hamayanhamayan.com/entry/2018/02/04/214751
  - http://mhiroaki.hatenablog.com/entry/2018/02/04/105811
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N;
//LL A[MAX_N];

const string s0="Vacant", s1="Male", s2="Female";
unordered_map<string,int> T={
  {s0,0},{s1,1},{s2,2}
};

string S;

int cnt=0;
int fetch(int i) {
  ++cnt;
  assert(cnt<=20);
  cout<<i<<endl;
  string s; cin>>s;
  return T[s];

//  return S[i]-'0';
}

void solve() {
  int l=0,r=N;
  int x=fetch(0);
  if(x==0) return;
  
  while(abs(r-l)>1) {
    int mid=(l+r)/2;
    int xmid=fetch(mid);

    bool par=abs(mid-l-1)%2;
    
//    dump4(l,r,mid,xmid);
//    dump4(l,r,par,x);
    
    if(xmid==0) return;
    
    if((par&&x==xmid)||(!par&&x!=xmid)) {
      l=mid;
      
      // this should not happen in the other case. I spent 35 mins to find this bug 😡😡😡😡😡😡😡😡😡
      x=xmid;
    } else {
      r=mid+1;
    }
    if(l>r) swap(l,r);
  }

  x=fetch(l);
  assert(x==0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  //cin>>S;
  //N=SZ(S);
  
  solve();
  return 0;
}
