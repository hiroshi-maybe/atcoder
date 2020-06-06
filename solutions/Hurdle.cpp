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

// $ cp-batch Hurdle | diff Hurdle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Hurdle.cpp && ./a.out

/*

 6/5/2020

 22:23-22:57 AC

 */

const int MAX_N=1e5+10;
int X[MAX_N];
int N,L;
LL T1,T2,T3;

const LL Inf=1e17;
LL dp[MAX_N][4];
void solve() {
  REPE(i,L)REP(j,4) dp[i][j]=Inf;
  dp[0][0]=0;
  REP(i,L) REP(j,4) {
    //dump(i,X[i],j,dp[i][j]);
    if(j==0) {
      SMIN(dp[i+1][0],dp[i][j]+T1+(X[i]?T3:0));
      SMIN(dp[i+1][1],dp[i][j]+(T1+T2)/2+(X[i]?T3:0));
    } else if(j==1) {
      SMIN(dp[i+1][0],dp[i][j]+(T1+T2)/2);
      SMIN(dp[i+1][2],dp[i][j]+T2);
    } else if(j==2) {
      SMIN(dp[i+1][3],dp[i][j]+T2);
    } else {
      SMIN(dp[i+1][0],dp[i][j]+(T1+T2)/2);
    }
  }
  LL res=Inf;
  REP(i,4) SMIN(res,dp[L][i]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>L;
  REP(i,N) {
    int x; cin>>x;
    X[x]=1;
  }
  cin>>T1>>T2>>T3;
  solve();

  return 0;
}
