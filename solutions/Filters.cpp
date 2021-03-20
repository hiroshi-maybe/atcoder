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

// $ cp-batch Filters | diff Filters.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Filters.cpp && ./a.out

/*

 3/20/2021

 6:05-6:41 WA and give up
 8:50-10:20 read editorials and got AC

 https://atcoder.jp/contests/abc196/editorial/948
 https://www.youtube.com/watch?v=3W_dK_pNOc4

 https://twitter.com/kyopro_friends/status/1373269973276061697
 https://twitter.com/kzyKT_M/status/1373268176776007684
 https://twitter.com/maspy_stars/status/1373268713877643264
 https://twitter.com/drken1215/status/1373268449674231808
 https://twitter.com/laycrs/status/1373268207717347329
 https://twitter.com/prd_xxx/status/1373269946726109190
 https://twitter.com/tanakh/status/1373269752827711492
 https://twitter.com/kiri8128/status/1373269438049316864
 https://twitter.com/tanakh/status/1373268914377945088
 https://twitter.com/ngtkana/status/1373271321874817028

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int T[MAX_N];
int N,Q;

LL Inf=1e17;

void solve() {
  cin>>Q;
  LL lb=-Inf,hb=Inf,cum=0;
  REP(i,N) {
    if(T[i]==1) lb+=A[i],hb+=A[i],cum+=A[i];
    if(T[i]==2) SMAX(lb,A[i]),SMAX(hb,A[i]);
    if(T[i]==3) SMIN(lb,A[i]),SMIN(hb,A[i]);
  }
  while(Q--) {
    LL x; cin>>x;
    LL res=x+cum;
    SMIN(res,hb);
    SMAX(res,lb);
    cout<<res<<endl;
  }
}

void pr(LL x) {
  REP(i,Q) cout<<x<<endl;
  exit(0);
}
void solve_org() {
  cin>>Q;
  LL lb=-Inf,hb=Inf,cum=0;
  for(int i=N-1; i>=0; --i) {
    if(T[i]==1) lb-=A[i],hb-=A[i],cum+=A[i];
    else if(T[i]==2) {
      SMAX(lb,A[i]);
      if(lb>hb) pr(hb+cum);
    } else if(T[i]==3) {
      SMIN(hb,A[i]);
      if(lb>hb) pr(lb+cum);
    }
  }

  LL lb2=-Inf,hb2=Inf;
  REP(i,N) {
    if(T[i]==1) lb2+=A[i],hb2+=A[i];
    else if(T[i]==2) SMAX(lb2,A[i]);
    else if(T[i]==3) SMIN(hb2,A[i]);
  }

  while(Q--) {
    LL x; cin>>x;
    if(x<=lb) cout<<lb2<<endl;
    else if(x>=hb) cout<<hb2<<endl;
    else cout<<x+cum<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i]>>T[i];
  solve();

  return 0;
}
