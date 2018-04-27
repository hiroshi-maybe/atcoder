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

// standard IO
template<class T> void _R(T &x) { cin >> x; }
void _R(int &x) { scanf("%d", &x); }
void _R(int64_t &x) { scanf("%lld", &x); }
void _R(double &x) { scanf("%lf", &x); }
void _R(char &x) { scanf(" %c", &x); }
void _R(char *x) { scanf("%s", x); }
void R() {}
template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const int64_t &x) { printf("%lld", x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }
#ifdef HOME
#define DEBUG(...) {printf("# ");printf(__VA_ARGS__);puts("");}
#else
#define DEBUG(...)
#endif

/*
 
 4/27/2018
 
 12:50-13:30 give up
 
 Editorials:
  - https://atcoder.jp/img/agc017/editorial.pdf
  - https://youtu.be/5usHNxVUzqk?t=920
  - http://hamayanhamayan.hatenablog.jp/entry/2017/07/10/020557
  - http://phwinx.hatenablog.com/entry/2017/07/14/014057
  - https://kimiyuki.net/blog/2017/07/09/agc-017-b/
   - clearly mentioning to commutativity
  - http://www.learning-algorithms.com/entry/2017/08/19/222158
  - https://ei1333.hateblo.jp/entry/2017/07/10/235514
  - https://twitter.com/tanakh/status/884051844955111425
  - https://twitter.com/satanic0258/status/884057667529879553
  - https://twitter.com/sigma425/status/884101055193112576
 
 Making formula? Simulation? I have no idea how to come up with this solution 😞
 
 14:00-14:30 read editorials and AC
 
 Key:
  - Two options: up (x[i]<x[i+1]) and down (x[i]>x[i+1])
  - Lower bound and upper bound are determined based on the two sufficient conditions (up or down)
  - Order of decision doesn't matter in terms of aggregated bounds
   - "Commutative"
 
 Summary:
  - Accumulating lower bound and upper bound may be popular as seen in GCJ 2018 R1A
  - Figuring out that two options are sufficient and order doesn't matter is the key though, it was hard for me 😞
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
bool solve(LL N,LL A,LL B,LL C,LL D) {
  REP(x,N-1) {
    LL l=C*x-D*(N-1-x),r=D*x-C*(N-1-x);
    if(l<=B-A&&B-A<=r) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  LL N,A,B,C,D;
  cin>>N>>A>>B>>C>>D;
  string yes="YES",no="NO";
  cout<<(solve(N,A,B,C,D)?yes:no)<<endl;
  return 0;
}
