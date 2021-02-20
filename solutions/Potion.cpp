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

// $ cp-batch Potion | diff Potion.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Potion.cpp && ./a.out

/*

 2/20/2021

 5:11-5:25 give up
 10:10-11:20 AC

 https://atcoder.jp/contests/abc192/editorial/705
 https://youtu.be/ZF_TAJRAZIY?t=5836

 https://twitter.com/laycrs/status/1363121371199410176
 https://twitter.com/tanakh/status/1363121719486128132
 https://twitter.com/kiri8128/status/1363121449213464580
 https://twitter.com/ajis_ka/status/1363123586567835649
 https://twitter.com/kyopro_friends/status/1363126636263010312
 https://scrapbox.io/nishio/ABC192

 */

const int MAX_N=100+3;
LL A[MAX_N],X;
int N;

LL dp[MAX_N][MAX_N][MAX_N][MAX_N];
void solve() {
  const LL Inf=1e18;
  REPE(i,N)REPE(j,N)REPE(k,N)REPE(l,N) dp[i][j][k][l]=-Inf;
  REPE(m,N)dp[0][0][m][0]=0;
  REP(i,N)REPE(cnt,N)FORE(base,1,N)REP(m,base) {
    LL cur=dp[i][cnt][base][m];
    //if(cur>=0) dump(i,cnt,base,m,cur);
    SMAX(dp[i+1][cnt][base][m],cur);
    SMAX(dp[i+1][cnt+1][base][(cur+A[i])%base],cur+A[i]);
  }

  //dump(dp[N][1][1][0]);
  LL res=Inf;
  FORE(cnt,1,N) REPE(m,N) if(dp[N][cnt][cnt][m]>0&&(X-m)%cnt==0) {
    //dump(cnt,m,X-m,(X-m)%cnt,dp[N][cnt][cnt][m]);
    SMIN(res,(X-dp[N][cnt][cnt][m])/cnt);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>X;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
