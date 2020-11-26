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

// $ cp-batch ProgrammingContest | diff ProgrammingContest.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ProgrammingContest.cpp && ./a.out

/*

 11/22/2020

 22:00-22:12 AC

 https://atcoder.jp/contests/abc184/editorial/354
 https://youtu.be/iWS5WCvMMak?t=6302

 https://kmjp.hatenablog.jp/entry/2020/11/22/1030
 https://drken1215.hatenablog.com/entry/2020/11/22/224100

 https://twitter.com/ngtkana/status/1330506565900791808
 https://twitter.com/laycrs/status/1330506557428154368
 https://twitter.com/satanic0258/status/1330506505939013633
 https://twitter.com/kzyKT_M/status/1330506434384187399
 https://twitter.com/kyopro_friends/status/1330513003217788928
 https://twitter.com/torus711/status/1330507311232806919

 */

const int MAX_N=40+1;
LL A[MAX_N],T;
int N;

bool ith(int mask, int i) { return (mask>>i)&1; }
void solve() {
  VV<LL> as(2);
  REP(i,N) as[i<N/2].push_back(A[i]);
  VV<LL> xs(2);
  REP(g,2) {
    int M=SZ(as[g]);
    REP(mask,1<<M) {
      LL sum=0;
      REP(i,M) if(ith(mask,i)) {
        sum+=as[g][i];
      }
      xs[g].push_back(sum);
    }
  }

  LL res=0;
  REP(g,2) sort(ALL(xs[g]));
  REP(i,SZ(xs[0])) {
    LL t1=xs[0][i];
    if(t1>T) continue;
    LL rem=T-t1;
    auto it=upper_bound(ALL(xs[1]),rem);
    int j=it-xs[1].begin();
    if(j>0) --j;
    LL t=t1+xs[1][j];
    assert(t<=T);
    SMAX(res,t);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>T;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
