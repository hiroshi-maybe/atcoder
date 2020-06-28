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

// $ cp-batch DivisionOrSubtraction | diff DivisionOrSubtraction.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DivisionOrSubtraction.cpp && ./a.out

/*

 4/30/2020

 21:29-22:24 WA
 22:54 AC

 https://img.atcoder.jp/abc161/editorial.pdf
 https://youtu.be/q-mrqE2Q7JQ?t=6494
 https://twitter.com/hanseilimak/status/1256103004014440451

 6/28/2020

 9:00-9:25 solve again

 */

LL N;

bool ok(LL n, LL k) {
  while(n%k==0) n/=k;
  return (n-1)%k==0;
}

int solve() {
  set<LL> res;
  LL n=N-1;
  auto add=[&](LL k) {
    if(k>=2&&k<=N) res.emplace(k);
  };
  for(LL p=1; p*p<=n; ++p) if(n%p==0) {
    add(p),add(n/p);
  }
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    if(p!=1&&ok(N,p)) add(p);
    if(ok(N,N/p)) add(N/p);
  }
  return SZ(res);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  N=genRandNum(1,100);
  LL act=solve();
  VI exp;
  for(LL k=2; k<=N; ++k) {
    LL n=N;
    while(n>=k) {
      if(n%k==0) n/=k;
      else n-=k;
    }
    if(n==1) exp.push_back(k);
  }
  dump(N,SZ(exp),act);
  dumpc(exp);
  assert(SZ(exp)==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

//  while(true) test();

  cin>>N;
  cout<<solve()<<endl;

  return 0;
}
