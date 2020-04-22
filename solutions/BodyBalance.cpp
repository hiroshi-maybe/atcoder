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

// $ cp-batch BodyBalance | diff BodyBalance.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BodyBalance.cpp && ./a.out

/*
 
 4/22/2020
 
 9:56-10:16 WA
 10:22 AC
 
 https://kmjp.hatenablog.jp/entry/2014/11/10/1000
 
 */

const int MAX_N=1e3+1;
int N,M,S,T;
vector<pair<int,LL>> G[MAX_N];

const LL Inf=1e17;
LL D[MAX_N];
bool ok(int s) {
  REP(i,N) D[i]=Inf;
  set<pair<LL,int>> Q;
  Q.emplace(0,s); D[s]=0;
  while(SZ(Q)) {
    auto it=Q.begin();
    LL d; int u; tie(d,u)=*it; Q.erase(it);
    FORR(p,G[u]) {
      LL delta=p.second; int v=p.first;
      LL dd=D[v];
      if(d+delta<dd) {
        auto itit=Q.find({dd,v});
        if(itit!=Q.end()) Q.erase(itit);
        D[v]=d+delta,Q.emplace(D[v],v);
      }
    }
  }
  if(D[S]==Inf||D[T]==Inf) return false;
  return D[S]==D[T];
}
void solve() {
  int res=-1;
  REP(u,N) if(u!=S&&u!=T) {
    if(ok(u)) res=u;
  }
  if(res>=0) ++res;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>S>>T;
  --S,--T;
  REP(i,M) {
    int u,v; LL d; cin>>u>>v>>d;
    --u,--v;
    G[u].emplace_back(v,d),G[v].emplace_back(u,d);
  }
  solve();
  
  return 0;
}
