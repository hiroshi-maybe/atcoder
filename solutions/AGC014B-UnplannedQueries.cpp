#include <iostream>
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
 
 4/24/2018
 
 10:00-11:00 analysis
 
 Looks like form of the tree doesn't matter to know the result? However I had no proof.
 
 23:30 Looked at editorial and figured out my assumption was correct.
 
 4/25/2018
 
 10:30-10:42 Evaluated parity with the simplest tree by imos. Got AC.
 
 Editorials:
  - https://atcoder.jp/img/agc014/editorial.pdf
  - https://youtu.be/UHfTqvaD0pk?t=1524
  - http://hamko.hatenadiary.jp/entry/2017/07/28/122321
  - https://kimiyuki.net/blog/2017/05/07/agc-014-b/
  - http://hamayanhamayan.hatenablog.jp/entry/2017/05/06/232930
 
 Proposition: If Endpoint of vertices show up even times iff edge's label is even
 
 If we assign arbitrary vertex `r` as root of the tree, query q(a,b) is shown as below:
 
 q(a,b) => q(l,a), q(l,b), 2*q(r,l) => q(r,a), q(r,b) where `l` = LCA(a,b)

 Now query q(a,b) is decomposed to q(r,a) and q(r,b).
 We are interested in parity of nodes in queries.
 If vertex `a` shows up even times, parity of e ∈ a↝r is clearly even.
 Thus "Endpoint of vertices show up even times => edge's label is even" is shown.
 
 Next we want to show "Endpoint of vertices show up even times <= edge's label is even"
 The contraposition of this proposition is "Endpoint of vertices show up odd times => edge's label is odd"
 
 This is not so hard to prove. Suppose parent vertex of `a` is `p`.
 If `p` is the bottom vertex which shows up odd times in the query, the final label in edge (a,p) is odd.
 Thus there exists an edge whose label is odd 📝
 
 Key:
  - Endpoint of vertices show up even times iff edge's label is even
  - Path between (u,v) in a tree is decomposed to (root,u) and (root,v)
 
 Summary:
  - N is large. I assumed that there is an easy solution where the tree structure doesn't matter.
  - Very impressive to reduce to rooted tree and cancel redundant path 👏
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
string yes="YES",no="NO";
bool solve(int N, int M, VI &A, VI &B) {
  map<int,int> im;
  REP(i,M) im[A[i]]++,im[B[i]]--;
  int p=0;
  FORR(kvp,im) {
    p=(p+kvp.second)%2;
    if(p==1) return false;
  }
  return true;
}

int main() {
  int N,M; scanf("%d %d",&N,&M);
  vector<int> A(M),B(M);
  REP(i,M) scanf("%d %d",&A[i],&B[i]);
  string res=solve(N,M,A,B)?yes:no;
  printf("%s\n",res.c_str());
}
