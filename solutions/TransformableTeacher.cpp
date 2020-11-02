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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch TransformableTeacher | diff TransformableTeacher.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TransformableTeacher.cpp && ./a.out

/*

 11/1/2020

 4:32-5:19 AC

 https://twitter.com/hanseilimak/status/1323129818351759361
 https://atcoder.jp/contests/abc181/editorial/261
 https://drken1215.hatenablog.com/entry/2020/11/02/021500
 https://kmjp.hatenablog.jp/entry/2020/11/01/0900

 */

const int MAX_N=1e6+1;
LL H[MAX_N],W[MAX_N];
int N,M;

const LL Inf=1e18;
LL solve() {
  sort(H,H+N),sort(W,W+M);

  if(N==1) {
    LL res=Inf;
    REP(i,M) SMIN(res,abs(H[0]-W[i]));
    return res;
  }

  vector<LL> gs(N),cum(N+10);
  REP(i,N-1) {
    gs[i]=H[i+1]-H[i];
  }
  dumpc(gs);

  REP(i,N) cum[i+2]=cum[i]+gs[i];

  dumpc(cum);

  LL res=Inf;
  REP(i,M) {
    LL w=W[i];
    int k=lower_bound(H,H+N,w)-H;

    LL ans;
    if(k%2) {
      ans=cum[k-1]+abs(w-H[k-1])+cum[N]-cum[k];
      dump(i,w,k,cum[k-1],cum[N]-cum[k-1],ans);
    } else {
      ans=cum[k]+abs(H[k]-w)+cum[N]-cum[k+1];
    }
    SMIN(res,ans);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>H[i];
  REP(i,M) cin>>W[i];
  cout<<solve()<<endl;

  return 0;
}
