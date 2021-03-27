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

// $ cp-batch Traveler | diff Traveler.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Traveler.cpp && ./a.out

/*

 3/27/2021

 5:25-6:02 AC

 https://atcoder.jp/contests/abc197/editorial/995
 https://youtu.be/mk8mGugZREg

 https://twitter.com/satanic0258/status/1375805858613919746
 https://twitter.com/ngtkana/status/1375808693141303301
 https://twitter.com/kzyKT_M/status/1375804845517537281
 https://twitter.com/laycrs/status/1375804869139783683
 https://twitter.com/tanakh/status/1375805478417014793
 https://twitter.com/maspy_stars/status/1375805969561579524
 https://twitter.com/kyopro_friends/status/1375838101856088066

 */

const int MAX_N=1e6+1;
LL X[MAX_N];
int N,C[MAX_N];

void solve() {
  VV<int> A(N+2);
  A[0].push_back(0),A[N+1].push_back(0);
  REP(i,N) A[C[i]].push_back(X[i]);
  VV<int> AA;
  REPE(i,N+1) if(SZ(A[i])) {
    AA.push_back({});
    AA.back().push_back(*min_element(ALL(A[i])));
    AA.back().push_back(*max_element(ALL(A[i])));
  }
  int M=SZ(AA);
  const LL Inf=1e17;
  VV<LL> dp(M,vector<LL>(2,Inf));
  dp[0][0]=dp[0][1]=0;
  FOR(i,1,M)REP(j,2) {
    LL dx=abs(AA[i][1]-AA[i][0]);
    LL prex=AA[i-1][j];
    REP(k,2) {
      LL curx=AA[i][1-k];
      SMIN(dp[i][k],dp[i-1][j]+dx+abs(prex-curx));
    }
  }
  cout<<min(dp[M-1][0],dp[M-1][1])<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>X[i]>>C[i];
  solve();

  return 0;
}
