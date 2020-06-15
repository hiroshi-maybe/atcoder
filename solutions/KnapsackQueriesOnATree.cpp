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

// $ cp-batch KnapsackQueriesOnATree | diff KnapsackQueriesOnATree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KnapsackQueriesOnATree.cpp && ./a.out

/*

 6/13/2020

 5:57-6:10 give up

 6/14/2020

 14:10-14:24, 15:15-18:15 AC after looking at editorials

 https://twitter.com/hanseilimak/status/1272391606604140544
 https://img.atcoder.jp/tokiomarine2020/editorial.pdf
 https://youtu.be/Kjk26wgMSQ8?t=2286
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.tb0msy32svc9

 https://twitter.com/satanic0258/status/1271807919785295872
 https://twitter.com/kyort0n/status/1271851466064400384
 https://twitter.com/chokudai/status/1271808513593929729
 https://twitter.com/kyopro_friends/status/1271807533762531328
 https://twitter.com/ei1333/status/1271806944735490052
 https://twitter.com/semiexp/status/1271805208650149888
 https://twitter.com/maspy_stars/status/1271805358801997825
 https://twitter.com/yosupot/status/1271805134150881282
 https://twitter.com/HIR180/status/1271804701663625216

 https://ngtkana.growi.cloud/solutions/contests/tokiomarine2020
 https://hir180.hateblo.jp/entry/2020/06/14/132815



 */

const int MAX_N=(1<<18)+1,MAX_W=1e5+1;
LL V[MAX_N];
int W[MAX_N];
int N,Q;

const int midd=10;
LL dp[1<<(midd+1)][MAX_W];
void dfs1(int i, int d) {
  if(d>midd||i>N) return;
  //dump(i,d);
  REP(w,MAX_W) {
    LL pval=i==0?0:dp[i/2][w];
    if(w+W[i]<MAX_W) SMAX(dp[i][w+W[i]], pval+V[i]);
    SMAX(dp[i][w],pval);
  }
  FORE(c,2*i,2*i+1) dfs1(c,d+1);
}
int midroot(int i) {
  while(i>=(1<<midd)) i>>=1;
  return i;
}

const LL Inf=1e17;
LL dfs2(int i, LL cur, int w, int L, int T, int pos) {
  if(w>L) return -Inf;
  if(i>T) {
    LL res=dp[midroot(i)][L-w]+cur;
    if(res==0) { dump(i,cur,w,L,midroot(i),dp[midroot(i)][L-w]); }
    return dp[midroot(i)][L-w]+cur;
  }
  LL res=-Inf;
  int c=2*i+((T>>pos)&1);
  //dump(i,2*i,(T>>pos)&1,c,T);
  LL a=dfs2(c,cur,w,L,T,pos-1),b=dfs2(c,cur+V[i],w+W[i],L,T,pos-1);
  SMAX(res,max(a,b));

  return res;
}

void solve() {
  dfs1(1,1);
  while(Q--) {
    int u,L; cin>>u>>L;
    LL res=0;
    if(u<(1<<midd)) {
      //dump(u,L,dp[u][L]);
      res=dp[u][L];
    } else {
      int maxd=0;
      int uu=u;
      while(uu>0) maxd++,uu>>=1;
      int pos=maxd-midd-1;
      int c=2*midroot(u)+((u>>pos)&1);
      //dump(u,c);
      res=dfs2(c,0,0,L,u,pos-1);
    }
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>V[i+1]>>W[i+1];
  cin>>Q;
  solve();

  return 0;
}
