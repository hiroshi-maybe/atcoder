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
 
 8/9/2018
 
 12:50-13:22 analysis
 13:37 1WA
 13:45 pause
 16:10-16:12 restore my first version and got AC. Why my original first version did not pass sample #2? bug?
 
 Editorials:
  - http://code-festival-2016-quala.contest.atcoder.jp/data/other/code-festival-2016-qualb/editorial.pdf
  - http://kmjp.hatenablog.jp/entry/2016/10/10/0900
  - http://ncastar.hatenablog.com/entry/2016/10/12/224425
 
 Modification of Kruskal's algorithm.
 If one edge is added between x=i and i+1, we don't need to put edges on both y=i and y=i+1.
 
 Summary:
  - We need at least one edge between x=i and i+1
  - I found greedy algorithm by experiment
 
 */


// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int H,W;
LL A[MAX_N],B[MAX_N];
void solve_wrong() {
  priority_queue<LL, vector<LL>, greater<LL>> Q1,Q2;
  REP(i,W) Q1.emplace(A[i]);
  REP(i,H) Q2.emplace(B[i]);
  LL res=0;
  while(SZ(Q1)||SZ(Q2)) {
    const LL Inf=1e15;
    int r=H-SZ(Q2),c=W-SZ(Q1);
    
    LL cost1=Inf,cost2=Inf;
    if(SZ(Q1)) {
      cost1=Q1.top()*(1LL*H+1-r);
    }
    if(SZ(Q2)) {
      cost2=Q2.top()*(1LL*W+1-c);
    }
    if(cost1<cost2) Q1.pop();
    else Q2.pop();
    res+=min(cost1,cost2);
  }
  cout<<res<<endl;
}

void solve() {
  priority_queue<pair<LL,int>, vector<pair<LL,int>>, greater<pair<LL,int>>> Q;
  REP(i,W) Q.emplace(A[i],i);
  REP(i,H) Q.emplace(B[i],i+W);
  LL res=0;
  int r=0,c=0;
  while(SZ(Q)) {
    LL d; int p; tie(d,p)=Q.top(); Q.pop();
    if(p<W) {
      res+=d*(1LL*H+1-r);
      ++c;
    } else {
      res+=d*(1LL*W+1-c);
      ++r;
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>W>>H;
  REP(i,W) cin>>A[i];
  REP(i,H) cin>>B[i];
  solve();
  return 0;
}
