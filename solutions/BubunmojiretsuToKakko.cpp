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
 
 8/18/2018
 
 17:30-17:55 analysis
 
 22:35-22:42 1WA
 23:25 2WA. give up. I couldn't solve "))((())(()"

 8/19/2018
 
 13:55-15:40 read editorials
 
 balanced "()"
 <=> 1. same number of "(" and ")"
     2. more "(" than or equal to ")" in any intermediate position
 
 Editorials:
  - https://img.atcoder.jp/bitflyer2018-final/editorial.pdf
  - http://drken1215.hatenablog.com/entry/2018/07/03/163100
  - https://babcs2035.hateblo.jp/entry/2018/07/18/133627
  - http://betrue12.hateblo.jp/entry/2018/06/30/235952
  - https://kimiyuki.net/writeup/algo/atcoder/bitflyer-2018-final-c/
 
           * *     * *
   ) ) ( ( ( ) ) ( ( )
 d 0-1-2-1 0 1 0-1 0 1 0
 
 String is not balanced.
 Eliminating invalid pairs in the same depth is the key of this problem.
 My wrong algorithm detected above two pairs in the same depth due to ")(" between them.
 However they should not.
 
 ())(()
   ^ we want to detect this and isolate left and right groups
 
 From condition #2, ")" violates property of balanced string.
 Keep tracking depth by "(" and ")".
 If ")" exists in string, it has lower depth than left and right
 
 ( ) ) ( ( )
 1 0-1 0 1 0
 ^   *   ^
 i   k   j
 
 We find d[k] s.t. d[k]<d[i] and d[k]<d[j] (d[i]=d[j], i<j<k) which is violating condition of balanced string.
 We should isolate groups.
 
 Delta of depth is always `1`. We can reset D[x] when depth gets `x-1` from `x`.
 
 Summary:
  - Knowing "necessary and sufficient" condition of balanced "()" helps to remove invalid ones
  - Implementation was not straightforward. It was not clear how to clear depth stack.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL D[2*MAX_N];
string S;

bool ok(string S) {
  int b=0;
  int N=SZ(S);
  REP(i,N) {
    if(S[i]=='(') ++b;
    else {
      --b;
      if(b<0) return false;
    }
  }
  return b==0;
}

void test(string S, int ans) {
  int N=SZ(S);
  LL res=0;
  REP(j,N)REP(i,j) {
    string ss=S.substr(i,j-i+1);
    if(ok(ss)) ++res;
  }
  if(res!=ans) {
    dump(S);
    dump2(res,ans);
  }
  assert(res==ans);
}

void solve_wrong() {
  ZERO(D);
  stack<int> ST;
  LL res=0;
  int d=0;
  int N=SZ(S);
  REP(i,N) {
    if(S[i]==')') {
      --d;
      if(SZ(ST)) {
        dump4(ST.top(),i,d,(MAX_N+d)%MAX_N);
        ST.pop();
        D[(MAX_N+d)%MAX_N]++;
        ++res;
      }
    } else {
      ST.push(i);
      ++d;
    }
  }
  REP(i,MAX_N) if(D[i]>1) res+=1LL*D[i]*(D[i]-1)/2;

  test(S,res);
  
  cout<<res<<endl;
}

void solve() {
  ZERO(D);
  int d=MAX_N;
  //D[d]=1;
  int N=SZ(S);
  LL res=0;
  REP(i,N) {
    if(S[i]=='(') {
      ++d;
      D[d]++;
    } else {
      res+=D[d];
//      dump4(i,d,D[d],res);
      --d;
      D[d+2]=0;
    }
  }
  
//  test(S,res);
  
  cout<<res<<endl;
}

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  /*
  while(true) {
    VI x=genRandSeq(10,0,2);
    S="";
    REP(i,SZ(x)) S+=x[i]==1?'(':')';
    solve();
  }*/

  cin>>S;
  solve();
  
  return 0;
}
