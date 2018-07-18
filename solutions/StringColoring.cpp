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
 
 7/14/2018 AGC026
 
 23:00-23:30 time is up
 
 7/18/2018
 
 15:45-16:12 Take a look at twitter comments and got AC
 
 Editorials:
  - https://img.atcoder.jp/agc026/editorial.pdf
  - https://youtu.be/eB0eT-948Vw?t=1979
  - http://kmjp.hatenablog.jp/entry/2018/07/16/1030
  - http://hamayanhamayan.hatenablog.jp/entry/2018/07/15/143139
  - http://kazune-lab.net/contest/2018/07/14/agc026/
  - http://sigma425.hatenablog.com/entry/2018/07/14/235324
  - https://qiita.com/nomikura/items/84dcb289919c8fb4e8a0
 
 Tweets:
  - https://togetter.com/li/1246851
  - https://twitter.com/evima0/status/1018141100639322113
  - https://twitter.com/satanic0258/status/1018140826755448832
  - https://twitter.com/beet_aizu/status/1018141795744534528
  - https://twitter.com/_primenumber/status/1018142371639259136
  - https://twitter.com/0x19f/status/1018143357292326912
  - https://twitter.com/furuya1223/status/1018141695081234435
  - https://twitter.com/noimi__/status/1018141369120903168
   - dp
  - https://twitter.com/koyumeishi_/status/1018141526788960257
   - rolling hash
 
 Key:
  - Divide string into two halves
   - { red-left, reverse(blue-left) } = { reverse(blue-right), red-right }
   - Half bitmask determines target string
  - Count pattern of pairs and remember in hash map
 
 Summary:
  - Once half enumeration comes up, it's straightforward. I couldn't solve during the contest though 😡
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N;
string S;
void solve() {
  LL res=0;
  unordered_map<string, unordered_map<string, LL>> M;
  REP(mask,1<<N) {
    string a,b;
    REP(i,N) (((mask>>i)&1)?a:b)+=S[N+i];
    M[a][b]++;
  }
  REP(mask,1<<N) {
    string a,b;
    REP(i,N) (((mask>>i)&1)?a:b)+=S[i];
    reverse(a.begin(),a.end()),reverse(b.begin(),b.end());
//    dump3(a,b,M[b][a]);
    res+=M[b][a];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S;
  solve();
  return 0;
}
