#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch Triangle | diff Triangle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Triangle.cpp && ./a.out

/*
 
 7/21/2019
 
 5:00-6:06 give up
 6:50-7:08 AC
 
 I tried to construct S by a*(a+x)-1*y where 0<=x<=1
 However 1e9*a-1*b in the editorial is even simpler!
 
 https://img.atcoder.jp/agc036/editorial.pdf
 
 */

LL S;

LL isqrt(LL x) {
  assert(x>0);
  LL y=(LL)(sqrtl((long double) x)+0.5);
//  while(y*y<x) ++y;
//  while(y*y>x) --y;
  return y;
}

void pr(LL a, LL b, LL c, LL d) {
  assert(a<=1e9&&b<=1e9&&c<=1e9&&d<=1e9);
  assert(a*d-b*c==S);
  println("%lld %lld %lld %lld %lld %lld", 0LL,0LL,a,b,c,d);
}
void solve() {
  LL a=1e9;
  LL d=(S+a-1)/a;
//  dump(a,d,a*d);
  assert(a*d>=S);
  LL c=a*d-S;
  pr(a,1,c,d);
}

void solve_org() {
  LL a=isqrt(S);
  dump(a,a*a,S);
  LL d=a;
  while(a*d<S) ++d;
  if(a*d==S) {
    pr(a,0,0,d);
    return;
  }
  dump(a,d,a*d,S);
  LL bc=a*d-S;
  pr(a,bc,1,d);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S;
  solve();
  
  return 0;
}
