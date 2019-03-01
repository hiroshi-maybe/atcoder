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

// $ cp-batch Affiches | diff Affiches.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Affiches.cpp && ./a.out

/*
 
 2/22/2019
 
 21:17-22:17 give up
 
 3/1/2019
 
 12:00-13:24 read editorials and got AC
 
 http://drken1215.hatenablog.com/entry/2019/02/23/200900
 https://betrue12.hateblo.jp/entry/2019/02/25/222736
 https://img.atcoder.jp/yahoo-procon2019-final/editorial.pdf
 
 As a prequisite knowledge, probability density function of `x` in [a,b] in uniform distribution is 1/(b-a).
 This satisfies ∫{f(x):x=a..b}dx = 1

 ∫{1/(b-a):x=a..b}dx = [x/(b-a)]{x=a..b} = (b-a)/(b-a) = 1
 
 From independency to choose x coordinate and y coordinate..
 
 res=E[XY]=E[X]E[Y]
 
 E[X]=∫{x*f(x):x=max(0,2A-H)..A}dx
 
 Fix overlapping length `x` and figure out probability density function f(x).
 If `x` is overlapping length, two rectnagles occupy 2A-x out of A.
 2A-x shows up in [0,H-(2A-x)] in uniform distribution.
 f(x) = 2*{H-(2A-x)}/(H-A)^2
 
 E[x] = ∫{x*f(x):x=max(0,2A-H)..A}dx = (H-2A)*(A*A-K*K)/(H-A)(H-A) + 2(A*A*A-K*K*K)/3(H-A)(H-A)
 
 */

int H,W,A,B;

double f(int A, int H) {
  double K=max(0,2*A-H);
  double a=(H-2*A)*(A*A-K*K),b=2.0*(A*A*A-K*K*K)/3.0;
  return (a+b)/(H-A)/(H-A);
}

void solve() {
  if(A>H||B>W) {
    cout<<0<<endl;
  } else {
    double a=f(A,H),b=f(B,W);
    cout<<a*b<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>H>>W>>A>>B;
  solve();
  
  return 0;
}
