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
 
 7/28/2018
 
 24:30-25:25 1WA. Looked at failed test case.
 
 7/29/2018
 
 15:30-16:40 AC
 
 Editorials:
  - https://img.atcoder.jp/arc088/editorial.pdf
  - https://youtu.be/WpUkC4-hyLE?t=2171
  - http://kazune-lab.net/contest/2017/12/23/abc083/#d---wide-flip
  - http://kurkur.hatenablog.com/entry/2017/12/30/190030
  - http://hamayanhamayan.hatenablog.jp/entry/2017/12/23/230229
  - https://kimiyuki.net/writeup/algo/atcoder/arc-088-d/
  - http://baitop.hatenadiary.jp/entry/2018/07/18/203159
 
 I've solved "Convert to Ones" in Codeforces.
  - https://codeforces.com/problemset/problem/997/A
 
 So I know that I knew that I don't need to break an homogeneous interval (=group).
 I showed that sum of two consecutive groups flips to 0s. However it's not optimal 😞.
 
 After looking at failed test case, I figured out that there is better strategy.
 We can convert left-most/right-most groups one by one by flipping up to right/left edges.
 It shows that center of the given string is bottle-necked.
 
 Building arbitrary operation from smaller operation is sometimes a key of
 
 Summary:
  - Problem is asking to find "maximum" K. So I should have tried to seek for large K in sample experiment
  - I'm wondering how I can figure out that my solution is NOT optimal by myself. Finding counter-example is the only way? 🤔
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int Inf=1e5+1;
string S;
void solve_wrong() {
  int N=SZ(S);

  int G0=0,G1=0;
  int len0=0,len1=0,res=Inf;
  
  int i=0;
  while(i<N&&S[i]==S[0]) (S[i]=='0'?len0:len1)++,++i;
  if(i==N) res=S[0]=='1'?1:0;
  else {
    for(; i<N; ++i) {
      if(S[i-1]!=S[i]) {
        (S[i-1]=='0'?G0:G1)++;
//        dump3(i,len0,len1);
        if(G0>0&&G1>0)SMIN(res,len0+len1);
        if(S[i-1]=='0') len1=0;
        else len0=0;
      }
      (S[i]=='0'?len0:len1)++;
    }
    SMIN(res,len0+len1);
    (S[N-1]=='0'?G0:G1)++;
    assert(G0+G1>=2);
//    dump2(G0,G1);
    if(G0==1&&G1==1) res=max(len1,len0);
  }
  cout<<res<<endl;
}

void solve() {
  int N=SZ(S);
  int res=0;
  REP(d,2) {
    int K=N/2+d;
    int L=Inf;
    int i=K;
    while(i<N&&S[i]==S[K]) ++i;
    SMIN(L,i);
    i=K;
    while(i>=0&&S[i]==S[K]) --i;
    SMIN(L,N-i-1);
    SMAX(res,L);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  solve();
  return 0;
}
