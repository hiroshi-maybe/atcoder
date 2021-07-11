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
struct LCA {
public:
  vector<vector<int>> G;
  int V,root;
  int H,t=0;
  vector<vector<int>> P; // parent P[bits][vertices], bits=floor(lg N)+1
  vector<int> D; // depth for LCA query D[vertices]
  vector<int> L,R; // timestamp of Euler tree
  LCA() {}
  LCA(int root, int V) : V(V), root(root) {
    G=vector<vector<int>>(V);
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  LCA(int root, vector<vector<int>> &G) : G(G), root(root) {
    V=G.size();
  }
  void build() {
    D=vector<int>(V,0),L=vector<int>(V,0),R=vector<int>(V,0);
    H=1;
    while((1<<H)<=V) ++H;
    P=vector<vector<int>>(H,vector<int>(V,-1));
    dfs(root,-1,0);
    for(int i=0; i<H-1; ++i) {
      for(int j=0; j<V; ++j) {
        if(P[i][j]!=-1) P[i+1][j]=P[i][P[i][j]];
      }
    }
  }
  // query to find an ancestor with `d` distance
  int ancestor(int u, int d) {
    int cur=u;
    for(int i=H-1; i>=0; --i) if(cur>=0&&(d>>i)&1) cur=P[i][cur];
    return cur;
  }
  int query(int u, int v) { // query to find lca(u,v)
    assert(0<=u&&u<V&&0<=v&&v<V);
    assert(!P.empty()); // call lca.build();
    if(D[u]>D[v]) swap(u,v);
    v=ancestor(v,D[v]-D[u]);
    if(u==v) return u;
    for(int i=H-1; i>=0; --i) {
      if(P[i][u]!=P[i][v]) u=P[i][u],v=P[i][v];
    }
    return P[0][u];
  }
  int dist(int u, int v) { // distance between u and v
    assert(0<=u&&u<V&&0<=v&&v<V);
    int p=query(u,v);
    return D[u]+D[v]-2*D[p];
  }
  vector<int> path(int u, int v) {
    int p=query(u,v);
    vector<int> a,b;
    while(u!=p) a.push_back(u),u=P[0][u];
    while(v!=p) b.push_back(v),v=P[0][v];
    vector<int> res=a;
    res.push_back(p);
    reverse(b.begin(),b.end());
    for(auto u : b) res.push_back(u);
    return res;
  }
private:
  void dfs(int u, int par, int d) {
    P[0][u]=par;
    D[u]=d,L[u]=t++;
    for(int v : G[u]) if(v!=par) dfs(v,u,d+1);
    R[u]=t++;
  }
};
// $ cp-batch Collision | diff Collision.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Collision.cpp && ./a.out

/*

 7/10/2021

 21:19-21:25 AC

 https://atcoder.jp/contests/abc209/editorial/2229

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int Q;
  cin>>N>>Q;
  LCA lca(0,N);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    lca.addEdge(u,v);
  }
  lca.build();
  while(Q--) {
    int c,d; cin>>c>>d;
    --c,--d;
    int di=lca.dist(c,d);
    string res=di%2?"Road":"Town";
    cout<<res<<endl;
  }

  return 0;
}
