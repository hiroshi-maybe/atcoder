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

// $ cp-batch WeightsOnVerticesAndEdges | diff WeightsOnVerticesAndEdges.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WeightsOnVerticesAndEdges.cpp && ./a.out

/*
 
 2/4/2019
 
 21:05-22:05 I figured out misunderstanding of problem. Sum of edge weight doesn't matter. Shit 🖕
 22:20 pause
 
 2/5/2019
 
 8:40-10:00 give up
 
 Basically keep merging smaller weights by union-find tree.
 In each connected component, it may be "valid" (∀j∈C, ∑{x[i]:i∈C}>=Y[j]) or may not.
 It gets valid once. However large edge weight may break it later.
 Each component grows up independently. We want to know maximum # of edges in each component at different time.
 Thus we need some query of history => persistent union find? => I don't quite understand it. I gave up.
 
 16:20-17:33 read editorials and got AC
 
 https://img.atcoder.jp/nikkei2019-qual/editorial.pdf
 https://youtu.be/x5x2Xg_gVWY?t=3498
 https://betrue12.hateblo.jp/entry/2019/01/28/215129
 https://twitter.com/rickytheta/status/1089525870534905856
 
 It's typical to move backward by adding edges if edges are being removed.
 We can keep adding edges from edges with smaller weight in union-find like Kruskal's algorithm.
 At some moment, we know maximum edges in a connected component.
 However it may be broken later by ading an edge with larger weight than sum of vertices weight.
 I had no idea how to resolve it to find maximum edges..
 
 After reading @betrue12's editorial, I figured out that we can keep previous contribution.
 When the connected component is back to valid state, we can subtract previous contribution and add new one. Then `res` is always correct value.
 (Code by @betrue12 is doing batch update of only difference. When back to valid, resetting current contribution to zero. It makes implementation simpler)
 
 */

const int MAX_N=1e6+1;
vector<pair<LL,int>> G[MAX_N];
tuple<LL,int,int> E[MAX_N];
LL X[MAX_N];
int N,M;

struct UF {
public:
  int N,G/* # of disjoint sets */;
  vector<LL> maxY,sumX;
  VI cntE;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1),maxY=vector<LL>(N,0),sumX=vector<LL>(N,0),cntE=VI(N,0);
    for(int i=0; i<N; ++i) par[i]=i,rank[i]=0,cnt[i]=1,sumX[i]=X[i],cntE[i]=0;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int count(int x) { return cnt[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y, LL w) {
    x=find(x),y=find(y);
    if(x==y) {
      SMAX(maxY[x],w);
      cntE[x]++;
      return x;
    }
    G--,cnt[x]=cnt[y]=cnt[x]+cnt[y];
    int p=x,c=y;
    if(rank[p]>rank[c]) swap(p,c);
    else rank[p]+=rank[p]==rank[c];
    par[c]=p;
    sumX[p]+=sumX[c],maxY[p]=max(maxY[c],w),cntE[p]+=cntE[c]+1;
    return p;
  }
  bool ok(int u) {
    int p=find(u);
    return sumX[p]>=maxY[p];
  }
private:
  vector<int> par,rank,cnt;
};

void bruteforce() {
  int res=MAX_N,rmask=-1;
  REP(mask,1<<M) {
    REP(i,N) G[i].clear();
    UF uf(N);
    REP(i,M) if((mask>>i)&1) {
      LL y; int u,v; tie(y,u,v)=E[i];
      G[u].emplace_back(y,v);
      G[v].emplace_back(y,u);
//      uf.unite(u,v);
      if(mask==2) dump(u,v);
    }
    map<int,LL> xsum;
    REP(i,N) xsum[uf.find(i)]+=X[i];
    bool ok=true;
    REP(i,M) if((mask>>i)&1) {
      LL y; int u,v; tie(y,u,v)=E[i];
      ok&=(xsum[uf.find(u)]>=y);
      if(mask==15) dump(mask,i,u,v,xsum[uf.find(u)],y,xsum[uf.find(u)]>=y);
    }
    if(mask==15) {
      dump(mask,ok);
    }
    if(ok&&M-__builtin_popcount(mask)<res) rmask=mask,res=M-__builtin_popcount(mask);
  }
  dump(res,rmask);
}

void solve_org() {
//  bruteforce();
  VI cont(N,0);
  UF uf(N);
  sort(E,E+M);
  int res=0;
  REP(i,M) {
    LL y; int u,v; tie(y,u,v)=E[i];
    int p1=uf.find(u),p2=uf.find(v);
    bool merged=p1!=p2;
    int p=uf.unite(u,v,y);
    if(merged) cont[p]=cont[p1]+cont[p2];
    if(uf.ok(p)) {
      res-=cont[p];
      cont[p]=uf.cntE[p];
      res+=cont[p];
    }
  }
  cout<<M-res<<endl;
}

set<II> viz;
void dfs(int u, LL Y) {
  FORR(p,G[u]) {
    LL y; int v; tie(y,v)=p;
    int uu=u,vv=v;
    if(uu>vv) swap(uu,vv);
    if(viz.count({uu,vv})) continue;
    if(y<=Y) {
      viz.emplace(uu,vv);
      dfs(v,Y);
    }
  }
}
// dfs from edges with large weight greedily as explained in the official editorial
void solve() {
  VI cont(N,0);
  UF uf(N);
  sort(E,E+M);
  VI cand;
  REP(i,M) {
    LL y; int u,v; tie(y,u,v)=E[i];
    int p=uf.unite(u,v,y);
    if(uf.ok(p)) cand.push_back(i);
    G[u].emplace_back(y,v);
    G[v].emplace_back(y,u);
  }
  reverse(ALL(cand));
  FORR(i,cand) {
    int u; LL y; tie(y,u,ignore)=E[i];
    dfs(u,y);
  }
  cout<<M-SZ(viz)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>X[i];
  REP(i,M) {
    int u,v; LL y; cin>>u>>v>>y;
    --u,--v;
    E[i]=make_tuple(y,u,v);
  }
  solve();
  
  return 0;
}
