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
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch NearestCardGame | diff NearestCardGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NearestCardGame.cpp && ./a.out

/*
 
 1/17/2019
 
 16:54-18:16 WA
 18:30 give up
 
 Condition of the validity by radius binary search is complex. I couldn't clearly define it.
 
 22:10-24:20 read submit solutions and got AC
 
 It's possible to binary search by `tcnt` # of elements that Takahashi takes.
 Aoki should take `tcnt`-1 within the same radius. We can check validity.
 This is easier way because tie can be resolved without trick.
 
 https://atcoder.jp/contests/aising2019/submissions/3987618
  - Clean solution by @natsugiri
 
 There is a workaround for binary search by radius.
 Problem of radius binary search is that difference `tcnt` and `acnt` could be at most 2 due to tie.
 There are two ways to resolve it.
  1. Use coordinate expansion. Move `x` to slightly left to ensure left is taken by Aoki.
  2. Look at [l,r] by Aoki. Modify those ranges for `tcnt`-`acnt`.
 
 https://atcoder.jp/contests/aising2019/submissions/3987556
  - Solution with radius binary search by @sugim48
  - Coordinate expansion (#1 above) is used

 I also added #2 solution.
 
 Summary:
  - My original binary search was broken because decision problem was not defined by inequality... How many times are you writing binary search? 😡😡😡😡😡😡😡😡😡😡
  - Try different way to make clean math model. In this problem, drop left edge of Aoki's card.
   - ✅ |TATATAT| A |AAAA|TTTTT
   - ❌ |TATATAT| A  AAAA|TTTTT <- this is hard to connect with radius because left most T of contiguous T's card may have same distance to `x` as second left A in A's contiguous cards.
   - If there is nusty model, try to modify it by slightly changing original model.
 
 */

const int MAX_N=1e6+10;
LL A[MAX_N];
int N,Q;

LL cum[MAX_N];
LL cum2[MAX_N];
void prep() {
  cum[0]=0,cum2[0]=cum2[1]=0;
  REP(i,N) {
    cum[i+1]=cum[i]+A[i];
    cum2[i+2]=cum2[i]+A[i];
  }
}

LL solve__(int x) {
  LL good=0,bad=N+1;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    if(N-(2*mid-1)<0) bad=mid; else {
      LL d1=x-A[N-(2*mid-1)],d2=A[N-mid]-x;
//      dump2(mid,d1<=d2);
      (d1<=d2?good:bad)=mid;
    }
  }
  int r=N-good,l=N-(2*good-1);
  LL res=cum[N]-cum[r];
//  dump4(x,good,l,r);
//  dump(N-(2*good-1));
  assert(l>=0);
  res+=cum2[l];
  return res;
}

II f(LL rad, int x) {
  int l=lower_bound(A,A+N,x-rad)-A;
  int r=lower_bound(A,A+N,x+rad)-A;
//  dump3(rad,l,r);
  int tcnt=N-r,acnt=r-l;
  if(acnt<=tcnt) return {l,r};
  return {-10,-10};
}

LL solve_rangemodification(int x) {
  LL good=0,bad=1e10;
  LL l=-1,r=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    II p=f(m,x);
//    dump3(m,p.first,p.second);
    
    if(p.first<-1) bad=m;
    else good=m,l=p.first,r=p.second;
  }
  auto p=f(good,x);
  l=p.first,r=p.second;
  int tcnt=N-r,acnt=r-l;
//  dump4(l,r,tcnt,acnt);
  
  // Range modification is needed
  assert(tcnt-acnt<=2);
  if(tcnt-acnt==0) l++;
  if(tcnt-acnt==2) ++r,++l;
  
  LL res=cum[N]-cum[r];
  if(l>=0)res+=cum2[l];
  return res;
}

// inspired by @sugim48
void prep2() {
  REP(i,N) A[i]*=4LL;
  prep();
}
LL solve(LL x) {
  x=x*4LL-1;
  
  LL good=-1,bad=1e10;
  LL l=-1,r=-1;
  while(abs(good-bad)>1) {
    LL rad=(good+bad)/2;
    int ll=lower_bound(A,A+N,x-rad)-A;
    int rr=upper_bound(A,A+N,x+rad)-A;
    
    int tcnt=N-rr,acnt=rr-ll;
    if(tcnt>=acnt) {
      good=rad;
      l=ll,r=rr;
    } else bad=rad;
  }
  int tcnt=N-r,acnt=r-l;
  dump2(x,good);
  dump4(l,r,tcnt,acnt);
  assert(tcnt-acnt<=1);
//  if(tcnt-acnt==2) l++,r++;
  LL res=cum[N]-cum[r];
  if(acnt-tcnt==0) ++l;
  if(l>=0)res+=cum2[l];
  return res/4;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q;
  REP(i,N) cin>>A[i];
  prep2();
  REP(i,Q) {
    int x; cin>>x;
    cout<<solve(x)<<endl;
  }
  
  return 0;
}
