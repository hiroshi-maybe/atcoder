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
const long long Inf=1e17;
const int MAX_V=2e5;
long long D[MAX_V];
using Edge=pair<long long, int>;
vector<Edge> G[MAX_V];
void dijkstra(int V, int st) {
  for(int i=0; i<V; ++i) D[i]=Inf;
  priority_queue<Edge,vector<Edge>,greater<Edge>> Q; Q.emplace(0,st); D[st]=0;
  while(Q.size()>0) {
    long long d; int u;
    tie(d,u)=Q.top(),Q.pop();
    if(d!=D[u]) continue;
    for(auto p : G[u]) {
      long long w; int v; tie(w,v)=p;
      if(d+w<D[v]) D[v]=d+w,Q.emplace(d+w,v);
    }
  }
}
// $ cp-batch ComeBackQuickly | diff ComeBackQuickly.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ComeBackQuickly.cpp && ./a.out

/*

 2/6/2021

 4:55-5:03 AC

 https://atcoder.jp/contests/abc191/editorial/610

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,M;

void solve() {
  VV<LL> ds(N,vector<LL>(N,Inf));
  REP(st,N) {
    dijkstra(N,st);
    //dump(st);
    REP(i,N) ds[st][i]=D[i];
    //dumpc(ds[st]);
  }
  REP(i,N) {
    LL res=Inf;
    FORR(p,G[i]) if(p.second==i) SMIN(res,p.first);
    REP(j,N) if(i!=j) SMIN(res,ds[i][j]+ds[j][i]);
    if(res>=Inf) res=-1;
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    G[u].emplace_back(w,v);
  }
  solve();

  return 0;
}
