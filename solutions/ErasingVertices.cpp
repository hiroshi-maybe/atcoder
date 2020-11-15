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
struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int size(int x) { return sz[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    int p=x,c=y;
    if(sz[p]<sz[c]) swap(p,c);
    G--,sz[p]=sz[c]=sz[p]+sz[c];
    par[c]=p;
    return p;
  }
private:
  vector<int> par,sz;
};
// $ cp-batch ErasingVertices | diff ErasingVertices.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ErasingVertices.cpp && ./a.out

/*

 11/15/2020

 6:45-7:15, 11:05-12:35, 14:45-15:36 give up
 17:06 AC

 https://atcoder.jp/contests/agc049/editorial/281
 https://drken1215.hatenablog.com/entry/2020/11/15/104400
 https://twitter.com/hanseilimak/status/1327883092107825152

 */

const int MAX_N=100+1;
string S[MAX_N];
int N;

const int Inf=1e8;
int mx[MAX_N][MAX_N];
void solve() {
  REP(i,N)REP(j,N) mx[i][j]=S[i][j]=='1'?1:Inf;
  REP(i,N) mx[i][i]=0;
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx[i][j],mx[i][k]+mx[k][j]);

  double res=0;
  REP(i,N) {
    int cnt=0;
    REP(j,N) if(mx[j][i]<Inf) ++cnt;
    //dump(i,cnt);
    res+=1.0/cnt;
  }
  cout<<res<<endl;
}

void solve_wrong() {
  REP(i,N)REP(j,N) mx[i][j]=S[i][j]=='1'?1:Inf;
  REP(i,N) mx[i][i]=0;
  REP(k,N)REP(i,N)REP(j,N) if(S[i][j]=='1') SMIN(mx[i][j],mx[i][k]+mx[k][j]);

  //REP(i,N) dumpC(mx[i],mx[i]+N);

  UF uf1(N),uf2(N);
  REP(j,N)REP(i,j) if(mx[i][j]<Inf&&mx[j][i]<Inf) uf2.unite(i,j);
  REP(i,N)REP(j,N) if(S[i][j]=='1') uf1.unite(i,j);

  vector<double> es(N);
  REP(i,N) if(uf2.find(i)==i) es[i]=(double)uf2.size(i)/uf1.size(i);

  //dumpc(es);

  double res=0;
  VI viz(N);
  auto dfs=[&](auto &&self, int u) {
    if(viz[u]) return;
    viz[u]=1;
    REP(v,N) if(S[u][v]=='1') {
      self(self, v);
    }
  };

  REP(i,N) if(uf2.find(i)==i) {
    viz=VI(N,0);
    dfs(dfs,i);
    int cnt=0;
    REP(j,N) if(viz[j]&&uf2.find(j)!=i) ++cnt;
    //dump(i,cnt,es[i]);
    //dumpc(viz);
    res+=es[i]*(cnt+1);
  }

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>S[i];
  solve();

  return 0;
}
