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

// $ cp-batch Lamps | diff Lamps.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Lamps.cpp && ./a.out

/*

 6/13/2020

 5:07-5:57, 6:11-6:49 AC

 https://img.atcoder.jp/tokiomarine2020/editorial.pdf
 https://youtu.be/Kjk26wgMSQ8?t=876

 https://ngtkana.growi.cloud/solutions/contests/tokiomarine2020
 https://twitter.com/maspy_stars/status/1271806414315327489
 https://twitter.com/kyopro_friends/status/1271807198448902145
 https://twitter.com/HIR180/status/1271804701663625216
 https://twitter.com/semiexp/status/1271805208650149888
 https://twitter.com/satanic0258/status/1271807917155483648

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N,K;

void solve() {
  REP(k,K) {
    VI as(N,0);
    VI imos(2*N+1,0);
    REP(i,N) {
      imos[max(0,i-A[i])]++,imos[i+A[i]+1]--;
    }
    int cur=0;
    REP(i,N) as[i]=cur+imos[i],cur=as[i];
    //dump(k);
    //dumpc(as);
    REP(i,N) A[i]=as[i];
    if(count(ALL(as),N)==N) {
      //dumpc(as);
      break;
    }
  }
  REP(i,N) cout<<A[i]<<" ";
  cout<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=2e5,K=N;
  VI as=genRandSeq(N,0,1);
  //dumpc(as);
  REP(i,N)A[i]=as[i];
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //REP(_,1) test();

  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
