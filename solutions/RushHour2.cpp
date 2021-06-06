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
const long long Inf=2e18;
const int MAX_V=2e5;
long long D[MAX_V];
using P=pair<long long, int>;
using Edge=tuple<int, long long, long long>;
vector<Edge> G[MAX_V];
void dijkstra(int V, int st) {
  for(int i=0; i<V; ++i) D[i]=Inf;
  priority_queue<P,vector<P>,greater<P>> Q; Q.emplace(0,st); D[st]=0;
  while(Q.size()>0) {
    long long t; int u;
    tie(t,u)=Q.top(),Q.pop();
    if(t!=D[u]) continue;
    for(auto e : G[u]) {
      long long c,d; int v; tie(v,c,d)=e;

      auto f=[&](LL t) -> LL { return t+c+d/(t+1); };

      LL tmin=f(t),m=(LL)sqrt(d+0.5);
      FORE(d,-100,100) if(m+d>=t) {
        SMIN(tmin,f(m+d));
      }

      //dump(u,v,t,tmin);
      if(tmin<D[v]) D[v]=tmin,Q.emplace(tmin,v);
    }
  }
}
// $ cp-batch RushHour2 | diff RushHour2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RushHour2.cpp && ./a.out

/*

 6/6/2021

 14:48-15:48 give up
 16:31 read editorials and got AC

 https://atcoder.jp/contests/ABC204/editorial/224
 https://motsu-xe.hatenablog.com/entry/2021/06/06/224341

 */

int N,M;

void solve() {
  dijkstra(N,0);
  LL res=D[N-1];
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v,c,d; cin>>u>>v>>c>>d;
    --u,--v;
    G[u].emplace_back(v,c,d),G[v].emplace_back(u,c,d);
  }
  solve();

  return 0;
}
