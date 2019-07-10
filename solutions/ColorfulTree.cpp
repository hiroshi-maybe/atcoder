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

// $ cp-batch ColorfulTree | diff ColorfulTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ColorfulTree.cpp && ./a.out

/*
 
 7/7/2019
 
 6:24-6:40 give up
 
 20:05-22:35 read editorials and got AC
 
 https://img.atcoder.jp/abc133/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/07/07/1030
 http://sigma1113.hatenablog.com/entry/2019/07/08/140243
 https://twitter.com/xuzijian629/status/1147865525495558146
 https://twitter.com/satanic0258/status/1147870013753135104
 
 Eulerian tour on tree edges
  - http://beet-aizu.hatenablog.com/entry/2019/07/08/174727
 
 */

struct BinaryLifting {
public:
  vector<vector<int>> G;
  vector<vector<int>> C;
  vector<vector<LL>> W;
  
  int V,root;
  int H,t=0;
  vector<vector<int>> P; // parent P[bits][vertices], bits=floor(lg N)+1
  vector<int> D; // depth for LCA query D[vertices]
  vector<int> L,R; // timestamp of Euler tree
  vector<LL> dist;
  BinaryLifting() {}
  BinaryLifting(int root, int V) : V(V), root(root) {
    G=vector<vector<int>>(V);
    C=vector<vector<int>>(V);
    W=vector<vector<LL>>(V);
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  BinaryLifting(int root, vector<vector<int>> &G) : G(G), root(root) {
    V=G.size();
  }
  void buildLiftingTable() {
    D=vector<int>(V,0),L=vector<int>(V,0),R=vector<int>(V,0);
    dist=vector<LL>(V,0);
    H=1;
    while((1<<H)<=V) ++H;
    P=vector<vector<int>>(H,vector<int>(V,-1));
    this->dfs(root,-1,0,0);
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
  // query to find lca(u,v)
  int lca(int u, int v) {
    assert(u<V&&v<V);
    if(D[u]>D[v]) swap(u,v);
    v=ancestor(v,D[v]-D[u]);
    if(u==v) return u;
    for(int i=H-1; i>=0; --i) {
      if(P[i][u]!=P[i][v]) u=P[i][u],v=P[i][v];
    }
    return P[0][u];
  }
private:
  void dfs(int u, int par, int d, LL curd) {
    P[0][u]=par;
    dist[u]=curd;
    D[u]=d,L[u]=t++;
    for(int i=0; i<G[u].size(); ++i)if(G[u][i]!=par) {
      int w=W[u][i];
      dfs(G[u][i],u,d+1,curd+w);
    }
    R[u]=t++;
  }
};

const int MAX_N=1e6+1;
vector<tuple<int,int,int,LL>> Q[MAX_N];
int N,QN;
LL res[MAX_N];

BinaryLifting tree;

int cnt[MAX_N],sum[MAX_N];

void dfs(int u, int par) {
  FORR(q, Q[u]) {
    int c,id,coef; LL d; tie(c,id,coef,d)=q;
    LL x=-sum[c]+d*cnt[c];
    res[id]+=x*coef;
  }
  REP(i,SZ(tree.G[u])) if(tree.G[u][i]!=par) {
    int c=tree.C[u][i];
    cnt[c]++,sum[c]+=tree.W[u][i];
    dfs(tree.G[u][i],u);
    cnt[c]--,sum[c]-=tree.W[u][i];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>QN;
  tree=BinaryLifting(0, N);
  REP(i,N-1) {
    int u,v,c,w; cin>>u>>v>>c>>w;
    --u,--v;
    tree.addEdge(u,v);
    tree.C[u].push_back(c),tree.C[v].push_back(c);
    tree.W[u].push_back(w),tree.W[v].push_back(w);
  }
  tree.buildLiftingTable();
  REP(i,QN) {
    int c,d,u,v; cin>>c>>d>>u>>v;
    --u,--v;
    int l=tree.lca(u,v);
    res[i]=tree.dist[u]+tree.dist[v]-2*tree.dist[l];
    Q[u].emplace_back(c,i,1,d);
    Q[v].emplace_back(c,i,1,d);
    Q[l].emplace_back(c,i,-2,d);
  }
  dfs(0,-1);
  REP(i,QN) println("%lld", res[i]);

  return 0;
}
