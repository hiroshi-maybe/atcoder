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
 
 8/14/2018
 
 23:20-23:56 submti and got AC
 
 Editorials:
  - https://img.atcoder.jp/colopl2018-final/editorial.pdf
  - https://lab-2-g.hatenablog.com/entry/2018/05/16/215830
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
string SS;

bool isops(string s) {
  return s=="*"||s=="+"||s=="/"||s=="-";
}
bool isop(char c) {
  string x(1,c);
  return isops(x);
}

void solve() {
  int N=SZ(SS);
  
  string n="";
  stack<string> S;
  
  auto mergeop = [&]() {
    vector<string> as;
    while(SZ(S)&&!isops(S.top())) as.push_back(S.top()),S.pop();
    reverse(as.begin(),as.end());
    assert(isops(S.top()));
    string op=S.top(); S.pop();
//    dump(op);
//    dumpAR(as);
    if(op=="/"||op=="-") {
      if(SZ(as)!=2) dumpAR(as);
      assert(SZ(as)==2);
    }
    string ex="(";
    REP(i,SZ(as)) {
      ex+=as[i];
      if(i!=SZ(as)-1) ex+=op;
    }
    ex+=")";
    assert(SZ(ex));
    S.push(ex);
  };
  
  REP(i,N) {
    char c=SS[i];
    auto procNum = [&]() {
      if(SZ(n))S.push(n);
      n="";
    };
    if(isop(c)) {
      string x(1,c);
      S.push(x);
    } else if(isdigit(c)) {
      n+=c;
    } else if(c=='(') {
      if(!isdigit(SS[i+1])&&!isop(SS[i+1])) dump3(SS,i,SS[i+1]);
      assert(isdigit(SS[i+1])||isop(SS[i+1]));
    } else if(c==')') {
      procNum();
      mergeop();
    } else if(c==',') {
      procNum();
    }
  }
  if(SZ(n)) S.push(n);
  assert(SZ(S)==1);
  string res=S.top();
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>SS;
  solve();
  return 0;
}
