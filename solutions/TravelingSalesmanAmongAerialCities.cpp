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

// $ cp-batch TravelingSalesmanAmongAerialCities | diff TravelingSalesmanAmongAerialCities.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TravelingSalesmanAmongAerialCities.cpp && ./a.out

/*

 10/17/2020

 4:25-5:35 give up
 22:10-22:30 AC by reordering loop

 https://twitter.com/hanseilimak/status/1317984440904159232
 https://youtu.be/r4ujcFBDBw4?t=3212
 https://atcoder.jp/contests/abc180/editorial/154

 */

const int MAX_N=20+1;
LL X[MAX_N],Y[MAX_N],Z[MAX_N];
int N;

const LL Inf=1e18;
LL mx[MAX_N][MAX_N];
LL dp[MAX_N][(1<<17)+1];
bool ith(int i, int mask) { return (mask>>i)&1; }
void solve() {
  auto dist=[&](int i, int j) {
    return abs(X[i]-X[j])+abs(Y[i]-Y[j])+max(0LL,Z[j]-Z[i]);
  };
  /*
  REP(i,N)REP(j,N) mx[i][j]=(i==j)?0:dist(i,j);
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx[i][j],mx[i][k]+mx[k][j]);*/
  //REP(i,N)REP(j,N) dump(i,j,mx[i][j]);

  int full=1<<N;
  REP(i,N)REP(mask,full) dp[i][mask]=Inf;
  dp[0][0]=0;
  REP(i,N)REP(mask,full) if(dp[i][mask]<Inf) {
    REP(j,N) if(!ith(j,mask)) {
      SMIN(dp[j][mask|(1<<j)], dp[i][mask]+dist(i,j));
    }
  }

  REP(i,N) dump(i,dp[i][full-1]);

  LL res=dp[0][full-1];
  //FOR(i,1,N) SMIN(res, dp[i][full-2]+mx[i][0]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i]>>Z[i];
  solve();

  return 0;
}
