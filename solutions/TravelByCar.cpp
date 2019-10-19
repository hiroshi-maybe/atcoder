#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<LL,int,int> III;
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

// $ cp-batch TravelByCar | diff TravelByCar.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TravelByCar.cpp && ./a.out

/*
 
 10/19/2019
 
 6:04-6:40 give up
 12:54-15:01 read editorials
 
 https://img.atcoder.jp/abc143/editorial.pdf
 https://youtu.be/3U_N7zelnMM?t=3895
 https://twitter.com/hanseilimak/status/1185649867797880832
 http://kmjp.hatenablog.jp/entry/2019/10/19/0900
 https://twitter.com/torus711/status/1185551918933823488?s=20
 https://twitter.com/tanakh/status/1185551439348633600?s=20
 https://twitter.com/kyopro_friends/status/1185553269159972864?s=20
 
 */

const int MAX_N=300+1;
int N,M,Q;
LL L;

using T=pair<int,LL>;
vector<T> G[MAX_N];
//LL mx[MAX_N][MAX_N];
//void solve(int s, int t) {
  
//}

//const LL Inf=1e10;
T ans[MAX_N][MAX_N];
void f(int s) {
  using TT=pair<T,int>;
  priority_queue<TT,vector<TT>,greater<TT>> Q;
  T d0=make_pair<int,LL>(0,0LL);
  Q.emplace(d0,s),ans[s][s]=d0;
  while(SZ(Q)) {
//    auto it=Q.begin();
//    int u,t; tie(u,t)=*it,Q.erase(it);
    T d; int u; tie(d,u)=Q.top(),Q.pop();
    if(d!=ans[s][u]) continue;
//    if(s==2)dump(u,t,d,SZ(G[u]));
    FORR(p,G[u]) {
      LL w; int v; tie(v,w)=p;
      T dd=d;
      dd.second+=w;
      if(dd.second>L) dd.first+=1,dd.second=w;
      if(ans[s][v]>dd) {
//        if(s==2)dump(u,t,d,v,dd,tt);
//        auto it2=Q.find({v,tt});
//        if(it2!=Q.end()) Q.erase(it2);
        ans[s][v]=dd,Q.emplace(dd,v);
      }
    }
  }
}

LL mx1[MAX_N][MAX_N],mx2[MAX_N][MAX_N];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  const LL Inf=1e10;
  cin>>N>>M>>L;
  REP(i,N)REP(j,N) mx1[i][j]=mx2[i][j]=i==j?0:Inf;
  REP(i,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    mx1[u][v]=mx1[v][u]=w;
  }
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx1[i][j],mx1[i][k]+mx1[k][j]);
  REP(i,N)REP(j,N) if(i!=j&&mx1[i][j]<=L) mx2[i][j]=1;
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx2[i][j],mx2[i][k]+mx2[k][j]);
  cin>>Q;
  REP(i,Q) {
    int s,t; cin>>s>>t;
    --s,--t;
    LL res=mx2[s][t];
    if(res>=Inf) res=-1;
    else res-=1;
    cout<<res<<endl;
  }
  
  return 0;
}


int main_dijkstra() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>L;
  REP(i,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    if(w>L) continue;
    G[u].emplace_back(v,w);
    G[v].emplace_back(u,w);
  }
  const int Inf=1e7;
  REP(i,N)REP(j,N)ans[i][j]={Inf,0};
  REP(i,N) f(i);
  cin>>Q;
  REP(i,Q) {
    int s,t; cin>>s>>t;
    --s,--t;
    int res=ans[s][t].first;
    if(res>=Inf) res=-1;
    cout<<res<<endl;
  }
  
  return 0;
}
