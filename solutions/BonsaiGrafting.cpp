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

// $ cp-batch BonsaiGrafting | diff BonsaiGrafting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BonsaiGrafting.cpp && ./a.out

/*
 
 2/22/2019
 
 22:30-24:10 WA
 24:40 The last test case throws RE...
 
 2/28/2019
 
 22:00-22:35 got AC by using array instead of vector...
 
 https://img.atcoder.jp/yahoo-procon2019-final/editorial.pdf
 https://www.hamayanhamayan.com/entry/2019/02/24/012304
 
 */

const int MAX_N=1e5+10;
VI G[2][MAX_N];
int N[2];

const int Inf=1e7;
int far[2][MAX_N];
int D[2][MAX_N];
void dfs(int t, int u, int pre) {
  D[t][u]=0;
  FORR(v,G[t][u])if(v!=pre) {
    dfs(t,v,u);
    SMAX(D[t][u],D[t][v]+1);
  }
  dump(t,u,D[t][u]);
}
void dfs2(int t, int u, int pre, int d) {
  II maxd1={d+1,pre},maxd2={-Inf,-1};
//  dump(t,u,pre,d);
  FORR(v,G[t][u])if(v!=pre) {
    II a={D[t][v]+1,v};
    if(maxd2<a) maxd2=a;
    if(maxd1<maxd2) swap(maxd1,maxd2);
  }
  far[t][u]=maxd1.first;
  assert(far[t][u]<N[t]);
//  far[t][u]=min(N[t]-1,maxd1.first);
  FORR(v,G[t][u])if(v!=pre) {
    if(maxd1.second==v) dfs2(t,v,u,maxd2.first);
    else dfs2(t,v,u,maxd1.first);
  }
//  dump(t,u,far[t][u]);
}

int compDiameter(int t, int u=0) {
  int V=N[t];
  vector<int> D(V,0);
  function<void(int,int,int)> dfs=[&](int u, int pre, int d) -> void {
    D[u]=d;
    for(auto v: G[t][u]) if(v!=pre) dfs(v,u,d+1);
  };
  dfs(u,-1,0);
  int a=max_element(D.begin(),D.end())-D.begin();
  
  D=vector<int>(V,0);
  dfs(a,-1,0);
  int b=max_element(D.begin(),D.end())-D.begin();;
  
  // (a,b) is pair of vertices which form diameter
  //  printf("%d-%d: %d\n",a,b,D[b]);
  return D[b];
}

int dia[2];
void solve() {
  REP(t,2) dfs(t,0,-1);
  REP(t,2) dfs2(t,0,-1,-1);

  int M=N[1],maxd=max(N[0],N[1]);
  vector<LL> cnt(maxd+1,0);
  vector<LL> sums(maxd+1,0);
  REP(u,M) {
    int dist=far[1][u];
    assert(dist<=M);
    cnt[dist]++;
    sums[dist]+=dist;
  }
  
  vector<LL> cntcum(maxd+2,0),sumcum(maxd+2,0);
  REP(i,SZ(cnt)) cntcum[i+1]=cntcum[i]+cnt[i];
  REP(i,SZ(sums)) sumcum[i+1]=sumcum[i]+sums[i];
  
  REP(t,2)dia[t]=compDiameter(t);
  int dd=max(dia[0],dia[1]);
  LL res=0;
  REP(u,N[0]) {
    int lb=dd-far[0][u]-1;
    lb=max(lb,-1);
    dump(u,far[0][u],lb);
    LL a=(sumcum[M]-sumcum[lb+1])+(cntcum[M]-cntcum[lb+1])*((LL)far[0][u]+1);
    LL b=cntcum[lb+1]*dd;
    res+=a+b;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(t,2)REP(i,MAX_N)G[t][i].clear();
  ZERO(N),ZERO(far),ZERO(D);
  
  cin>>N[0];
  REP(i,N[0]-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[0][u].push_back(v);
    G[0][v].push_back(u);
  }
  
  cin>>N[1];
  REP(i,N[1]-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[1][u].push_back(v);
    G[1][v].push_back(u);
  }
  solve();
  
  return 0;
}
