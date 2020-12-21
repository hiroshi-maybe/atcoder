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
template <typename Integer>
tuple<Integer,Integer,Integer> extended_euclid(Integer a, Integer b) {
  assert(a>=0&&b>=0);
  if (b==0) return make_tuple(a, 1, 0);

  Integer d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}
template <typename Integer>
Integer inv(Integer a, Integer M) {
  return get<1>(extended_euclid(a,M));
}

// $ cp-batch Throne | diff Throne.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Throne.cpp && ./a.out

/*

 12/19/2020

 21:23-22:57 WA
 23:00 give up

 12/21/2020

 15:30-17:45 AC after reading editorials

 https://atcoder.jp/contests/abc186/editorial/401
 https://youtu.be/hY2FicqnAcc?t=2691
 https://drken1215.hatenablog.com/entry/2020/12/20/015100

 https://twitter.com/torus711/status/1340292125473210370
 https://twitter.com/kiri8128/status/1340292074805968896
 https://twitter.com/drken1215/status/1340290928091643904
 https://twitter.com/laycrs/status/1340290965672656896

 https://qiita.com/drken/items/b97ff231e43bce50199a

 */

LL N,S,K;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
void solve() {
  LL g=gcd(N,K);
  if(S%g!=0) {
    cout<<-1<<endl;
    return;
  }

  LL n=N/g,s=S/g,k=K/g;
  auto kinv=inv(k,n);
  //dump(k,kinv,(k*kinv%n+n)%n);
  assert((k*kinv%n+n)%n==1);
  LL res=(-s*kinv%n+n)%n;
  cout<<res<<endl;
}

void solve_wrong() {
  LL gg=gcd(N,K);
  dump(N,K,gg);
  if(S%gg!=0) {
    cout<<-1<<endl;
    return;
  }

  LL n=N,s=S,k=K;
  k=(-k%n+n)%n;
  auto t=extended_euclid(n,k);
  int g,x,y; tie(g,x,y)=t;
  dump(n,k,s,g,x,y);
  dump((LL)x*n+(LL)k*y,((LL)x*n+(LL)k*y)%n);
  assert(((LL)n*x+(LL)k*y)%n==g);
  y=(y%n+n)%n;
  dump((LL)y*s,(LL)y*s%n);
  cout<<(LL)y*s/g%n<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>S>>K;
    solve();
  }

  return 0;
}
