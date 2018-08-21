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
 
 8/21/2018
 
 13:30-14:37 give up
 15:19 read editorials and got AC
 
 Editorials:
  - https://www.hamayanhamayan.com/entry/2018/02/05/015056
  - http://ferin-tech.hatenablog.com/entry/2018/02/07/053155
  - https://kimiyuki.net/writeup/algo/atcoder/dwacon2018-final-a/
 
 Summary:
  - boring simulation
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int H,M,S;
int C1,C2;

II f(int s, int m, int C) {
  int args=60*s,argm=m;
  if(args<argm) {
    int t=(argm-args+58)/59;
    return {
      max(t+60*(C-1),0),
      t+60*C
    };
  } else {
    int t=(argm-args+3600+58)/59;
    return {
      t+60*C,
      t+60*(C+1)
    };
  }
}

II g(int m, int h, int C) {
  int argm=720*m,argh=h;
  if(argm<argh) {
    int t=(argh-argm+718)/719;
    return {
      max(t+3600*(C-1),0),
      t+3600*C
    };
  } else {
    int t=(argh-argm+43200+718)/719;
    return {
      t+3600*C,
      t+3600*(C+1)
    };
  }
}

void solve_wrong() {
  if(C1<C2) {
    cout<<-1<<endl;
    return;
  }
  II x=f(S,M,C1),y=g(M,H,C2);
  int l1=x.first,r1=x.second,l2=y.first,r2=y.second;
  dump4(l1,r1,l2,r2);
  int l=max(l1,l2),r=min(r1,r2);
  if(r<l) {
    cout<<-1<<endl;
  } else {
    cout<<l<<" "<<r<<endl;
  }
}

const int MOD=43200;

III f(int t) {
  return {720*t%MOD,12*t%MOD,t%MOD};
}

void solve() {
  H=H%12;
  int t0=S+60*M+3600*H;
  int t=t0;
  
  int t1l=1e9,t1r=-1;
  int t2l=1e9,t2r=-1;
  int cnt1=0,cnt2=0;
  while(cnt1<=C1||cnt2<=C2) {
    int s1,m1,h1; tie(s1,m1,h1)=f(t);
    int s2,m2,h2; tie(s2,m2,h2)=f(t+1);
    
    if (s1!=m1&&m1!=h1&&h1!=s1) {
      if(cnt1==C1) t1l=min(t1l,t),t1r=max(t1r,t);
      if(cnt2==C2) t2l=min(t2l,t),t2r=max(t2r,t);
    }
    
    if(s1<=m1&&s2>m2) ++cnt1;
    if(m1<=h1&&m2>h2) ++cnt2;

/*    if(t-t0<5) {
      dump4(t,s1,m1,h1);
    }*/
    
    ++t;
    //dump3(t,cnt1,cnt2);
  }
  
  int l=max(t1l,t2l),r=min(t1r,t2r);
  if(r<l) {
    cout<<-1<<endl;
  } else {
    cout<<l-t0<<" "<<r-t0<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>H>>M>>S>>C1>>C2;
  solve();
  return 0;
}
