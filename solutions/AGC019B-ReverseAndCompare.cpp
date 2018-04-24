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
 
 4/23/2018
 
 11:28-12:00 give up
 
 O(N^2) algorithm doesn't work. I tried to find O(N) or O(N*lg N) algorithms. However no luck.
 What I tried...
  - Fixing one end. Trying to query number of same pattern in O(1)
  - N*(N+1)/2 - { number of duplicated ones }
  - Using palindrome?
 
 I couldn't reach solution from them... 😞
 
 21:30-22:30, 24:00-24:16 Read editorials and add solution
 
 Editorials:
  - https://atcoder.jp/img/agc019/editorial.pdf
  - https://youtu.be/9OiB8ot3a0w?t=700
  - http://hamayanhamayan.hatenablog.jp/entry/2017/08/27/121438
 
 Twitter:
  - https://twitter.com/torus711/status/901455266264174592
  - https://twitter.com/beet_aizu/status/901463218517880837
 
 Suppose we are reversing A[i..j].
 Define that B(i,j) is obtained by reversing A[i..j] (A[i]!=A[j]).

 Reverse is actually series of process of swaps (A[i],A[j]), (A[i+1],A[j-1]), ...
 If we find some properties of the initial swap (A[i],A[j]), it may be helpful.
 Let's look at equality of them.
 
 If A[i]==A[j], the reversed string is same as A[i+1..j-1].
 This is similar process as we check palindrome.
 Note that palindrome property is defined by recursive substructure.
 Now we can "delegate" unique string to sub-problem.
 
 If A[i]!=A[j], it's actually unique.
 The swap of A[i],A[j] happens when reversing A[L..R] (L<i and R>j).
 If there exists A[p]!=A[q] where L<=p<i and j<q<=R, it's different from B(i,j).
 If A[L..i-1]=A[j+1..R], the reversed string is same as B(i,j).
 In this case, the counting of the pattern is "delegated" to B(i,j).
 Thus B(i,j) is uniquly counted when A[i]!=A[j].
 
 From this proof, we can show that counting number of pairs of different characters give expected result 📝
 
 Formal proof in the editorial is using contraposition.
 Editorial is also showing that A[i]!=A[j] is necessary and sufficient for proposition that B(i,j) is unique.
 
 Now we have B(x,y) which is equal to B(i,j) and A[i]!=A[j].
 i and j are the left-most and right-most positions of different characters from original string A.
 This is same for x,y as well. Thus If B(i,j)==B(x,y), i==x and j==y.
 From contraposition of this proposition ...
 if i!=x OR j!=y, B(i,j)!=B(x,y) 📝
 
 Key:
  - If end of characters is mutually different, it's unique string
 
 Summary:
  - Going into search optimization does not reach the proved property
  - Observation -> Hypothesis -> Proof is necessary. The observation needs creativity
  - Property of the edge is necessary condition. The editorial is showing that necessary condition
  - Recursive substructure. Reverse is composed of process of swaps from the center to the edges
   - The left-most or right-most edge is the special case
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL solve(string S) {
  LL C[26]={};
  FORR(c,S) C[c-'a']++;
  LL res=0;
  REP(j,26) REP(i,j) res+=C[i]*C[j];
  return res+1;
}

int main() {
  string S;
  cin >> S;
  cout << solve(S) << endl;
  return 0;
}
