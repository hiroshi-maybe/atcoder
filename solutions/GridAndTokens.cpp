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
template<class V> class Dinic {
public:
  int N;
  Dinic(int N) : N(N) {
    E=vector<vector<Edge>>(N),dist=vector<int>(N),iter=vector<int>(N);
  }
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }

  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      bfs(s);
      if(dist[t]<0) return res; // t is unreachable
      iter=vector<int>(N,0);
      V f;
      while((f=dfs(s,t,Inf))>0) res+=f;
    }

    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<vector<Edge>> E; // Graph
  vector<int> dist; // distance from `s`
  vector<int> iter;

  // initialize shoftest path and store in `level`
  void bfs(int s) {
    dist=vector<int>(N,-1);

    queue<int> Q;
    dist[s]=0;
    Q.push(s);

    while(Q.size()) {
      int u=Q.front(); Q.pop();

      for(int i=0; i<E[u].size(); ++i) {
        Edge &e=E[u][i];
        int v=e.to;
        if(e.cap<=0) continue;
        if(dist[v]>=0) continue; // visited

        dist[v]=dist[u]+1;
        Q.push(v);
      }
    }
  }

  // find augmenting path in residual network and update f
  V dfs(int u, int t, V f) {
    if(u==t) return f;
    for(int &i=iter[u]; i<E[u].size(); ++i) { // visit E[u] only once
      Edge &e=E[u][i];
      int v=e.to;
      if(e.cap<=0) continue;
      if(dist[u]>=dist[v]) continue;

      V d=dfs(v,t,min(f,e.cap));
      if(d<=0) continue;
      e.cap-=d;
      E[v][e.rev].cap+=d; // cancellation increases
      return d;
    }

    return 0;
  }
};
// $ cp-batch GridAndTokens | diff GridAndTokens.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GridAndTokens.cpp && ./a.out

/*

 6/13/2021

 6:05-6:30 give up
 16:00-17:10 read editorials and got AC

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.pomwdajagx2a
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.a90y9rtagi53

 https://atcoder.jp/contests/abc205/editorial/2057
 https://youtu.be/jEXwZnK-tN8?t=5028

 https://twitter.com/ngtkana/status/1404071875966242819
 https://twitter.com/satanic0258/status/1404071509077811212
 https://twitter.com/torus711/status/1404071736790773763
 https://twitter.com/maspy_stars/status/1404071760652247047
 https://twitter.com/Rubikun_pro/status/1404071735687741442
 https://twitter.com/ei1333/status/1404071578640412676

 */

const int MAX_N=1e2+1;
int minr[MAX_N],maxr[MAX_N],minc[MAX_N],maxc[MAX_N];
int H,W,N;

void solve() {
  Dinic<int> dinic(402);
  int source=0,sink=401;
  FORE(h,1,H) dinic.addEdge(source,h,1);
  FORE(i,1,N) {
    FORE(r,minr[i-1],maxr[i-1]) dinic.addEdge(r,200+i,1);
    dinic.addEdge(200+i,300+i,1);
    FORE(c,minc[i-1],maxc[i-1]) dinic.addEdge(300+i,100+c,1);
  }
  FORE(w,1,W) dinic.addEdge(100+w,sink,1);

  int res=dinic.maxFlow(source, sink);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>H>>W>>N;
  REP(i,N) cin>>minr[i]>>minc[i]>>maxr[i]>>maxc[i];
  solve();

  return 0;
}
