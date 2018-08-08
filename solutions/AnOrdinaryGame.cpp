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
 
 8/7/2018
 
 13:10-14:00 pause
 14:55-15:30 got ACC
 
 Editorials:
  - https://youtu.be/btAAdZqTCok?t=1573
   - In game problem find "rule". Then it's easy to prove it by following W/L states transition
   - Check there exists W->L and there exits NO L->L. Then it's proved.
  - https://atcoder.jp/img/arc064/editorial.pdf
  - https://twitter.com/kroton_pc/status/956174777235816449
  - https://kimiyuki.net/writeup/algo/atcoder/arc-064-d/
  - http://kmjp.hatenablog.jp/entry/2016/12/04/1030
  - http://procon-nenuon61.hatenablog.com/entry/2017/10/08/163739
  - https://babcs2035.hateblo.jp/entry/2018/06/23/142525
  - http://baitop.hatenadiary.jp/entry/2018/07/12/203724
  - https://qiita.com/honake/items/720256244222a0bc1eb1#d---an-ordinary-game
 
 One important observation is that parity of length for each player is invariant.
 Typical approach of game problem is to find LOSE state and verify if it's possible to keep forcing it.
 There are some explicit lose states as shown below:
 
 ababa (no more possible turns because same characters cannot stay in consecutive position)
 ab (no more possible turns because characters of both ends cannot be taken)
 
 As mentioned earlier, parity is invariant. Also character of both ends is another invariant i.e. "a**a" or "ab".
 
 We can guess that (odd, a*a) and (even, ab) are lose state where (length of given sequence, chars in both ends).
 
 W/L(state id):
      odd  even
      --------
 a*a |L(1)  W(2)
 a*b |W(3)  L(4)
 
 This seems to be correct in experiments as well by following W->L and L->W transitions.
 
 length: seqs
 2: ab(L-4)
 3: abc(W-3), aba(L-1)
 4: abcd(L-4), abab(L-4), abca(W-2), abcb(L-4)
 
 Below is showing how each state eventually reaches:
 
 L(1): a***a (odd) -> even steps -> ababa (odd)
  => player with #1 reaches lost (look at parity of length)
 W(2): a**a (even) -> odd steps -> ababa (odd)
  => player with #2 reaches win
 W(3): a***b (odd) -> odd steps -> abab (even)
  => player with #3 reaches win
 L(4): a**b (even) -> even steps -> abab (even)
  => player with #4 reaches lost
 
 Summary:
  - It was not easy to reach right analysis. However I made it 👍
  - Video was pretty impressive to understand typical flow to solve game problem
   1. find rule (find final "lost" state and invariant properties)
   2. prove sufficiency by confirming W->L state transition and NO L->L transition
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
//int N;
string S;
const string p1="First",p2="Second";
bool solve() {
  int N=SZ(S);
  if(N%2==0) return S.front()==S.back();
  if(S.front()==S.back()) return false;
  set<char> X(S.begin(),S.end());
  
  // this is actually always true because length of string in state "W(3)" cannot be odd
  return SZ(X)!=2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  cout<<(solve()?p1:p2)<<endl;
  return 0;
}
