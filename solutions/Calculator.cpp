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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch Calculator | diff Calculator.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Calculator.cpp && ./a.out

/*

 6/12/2021

 6:36-7:00 give up
 11:20-12:38 read editorials and got AC

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.n5iqcprax2x8

 https://atcoder.jp/contests/arc122/editorial/2052
 https://twitter.com/laycrs/status/1403714162887331845
 https://twitter.com/maspy_stars/status/1403715395635146753
 https://mobile.twitter.com/satanic0258/status/1403725450501771269
 https://mobile.twitter.com/ngtkana/status/1403722413049737218

 https://en.wikipedia.org/wiki/Zeckendorf%27s_theorem

 */

LL N;

LL fib[100];
void solve() {
  fib[0]=0,fib[1]=1;
  int n=2;
  while(true) {
    fib[n]=fib[n-1]+fib[n-2];
    if(fib[n]>N) break;
    ++n;
  }
  LL rest=N-fib[n-1];
  dump(n,fib[n-1],rest);
  VI xs;
  while(rest>0) {
    int x=0;
    REP(i,n) if(fib[i]<=rest) x=i;
    xs.push_back(n-x);
    rest-=fib[x];
  }
  dump(n,rest);
  dumpc(xs);
  reverse(ALL(xs));
  assert(rest==0);
  VI res;
  res.push_back(n%2?2:1);
  VI ys;
  if(n%2) ys={4,3};
  else ys={3,4};
  int j=0;
  FOR(fi,1,n) {
    res.push_back(ys[j]),j=1-j;
    if(SZ(xs)&&fi==xs.back()) {
      res.push_back(res.back()==3?1:2);
      xs.pop_back();
    }
  }

  LL x=0,y=0;
  FORR(o,res) {
    if(o==1) ++x;
    if(o==2) ++y;
    if(o==3) x=x+y;
    if(o==4) y=x+y;
    dump(o,x,y);
  }
  assert(x==N);

  cout<<SZ(res)<<endl;
  FORR(o,res) cout<<o<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  solve();

  return 0;
}
