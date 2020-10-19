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

// $ cp-batch BracketScore | diff BracketScore.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BracketScore.cpp && ./a.out

/*

 10/18/2020

 5:32-7:30 give up
 21:06-21:30 AC
 22:00 add proof in tweets

 https://twitter.com/hanseilimak/status/1318047679612473345
 https://atcoder.jp/contests/agc048/editorial/198

 https://twitter.com/yosupot/status/1317844527579680769
 https://twitter.com/laycrs/status/1317835352342626306
 https://twitter.com/kzyKT_M/status/1317835795554660352
 https://twitter.com/tomerun/status/1317836012458889216
 https://twitter.com/ajis_ka/status/1317836197272539144
 https://twitter.com/beet_aizu/status/1317836349601320961
 https://twitter.com/maspy_stars/status/1317836368425283589
 https://twitter.com/camypaper/status/1317836123830317057
 https://twitter.com/ymatsux_ac/status/1317837289783918597

 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

const LL Inf=1e18;
void solve() {
  LL res=accumulate(A,A+N,0LL);
  VV<LL> xs(2);
  REP(i,N) {
    xs[i%2].push_back(B[i]-A[i]);
  }
  REP(i,2) sort(ALL(xs[i])),reverse(ALL(xs[i]));
  REP(i,SZ(xs[0])) res+=max(xs[0][i]+xs[1][i],0LL);
  cout<<res<<endl;
}

LL dp[MAX_N][10];
void solve_wrong() {
  REPE(i,N)REP(j,10) dp[i][j]=-Inf;
  dp[0][0]=0;
  REP(i,N)REP(j,9) {
    int a=j%3,b=(j/3)%3;
    /*if(a>0&&b>0) {
      if(a==b) continue;
    }*/
    dump(a,b);
    if(i%2) {
      // odd
      if(a%2==0) {
        int aa=a==0?1:0;
        SMAX(dp[i+1][3*b+aa],dp[i][j]+A[i]);
      }
      if(b%2==0) {
        int bb=b==0?1:0;
        SMAX(dp[i+1][3*bb+a],dp[i][j]+B[i]);
      }
    } else {
      // even
      if(a<2) {
        int aa=a==1?0:2;
        SMAX(dp[i+1][3*b+aa],dp[i][j]+A[i]);
      }
      if(b<2) {
        int bb=b==1?0:2;
        SMAX(dp[i+1][3*bb+a],dp[i][j]+B[i]);
      }
    }
  }
  cout<<dp[N][0]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];

  /*
  REP(mask,1<<N) {
    LL res=0;
    REP(i,N) {
      if((mask>>i)&1) res+=A[i];
      else res+=B[i];
    }
    if(res==6629738472) {
      REP(i,N) dump(i,(mask>>i)&1);
    }
  }
  return 0;
  */

  solve();

  return 0;
}
