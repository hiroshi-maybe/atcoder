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

// $ cp-batch ThreeCircuits | diff ThreeCircuits.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeCircuits.cpp && ./a.out

/*
 
 3/23/2019
 
 23:30-23:52 WA
 
 3/26/2019
 
 16:30-18:50 read editorials and got AC
 
 There is a counter example such that three circuits cannot be built by two verteices with degree 4.
 Hmmmm it's hard to discover the failure case...
 
 https://img.atcoder.jp/agc032/editorial.pdf
 https://twitter.com/gzlcp/status/1109467613157945344
 
 */

const int MAX_N=1e6+1;
VI GG[MAX_N];
VI G[MAX_N];
int N,M;

int viz[MAX_N];
void dfs(int u) {
  if(viz[u]) return;
  viz[u]=true;
  FORR(v,G[u]) dfs(v);
}

void nope() {
  println("No");
  exit(0);
}
void yup() {
  println("Yes");
  exit(0);
}
void solve() {
  dfs(0);
  REP(i,N) if(!viz[i]) nope();
  REP(i,N) if(SZ(G[i])%2==1) nope();
  REP(i,N) if(SZ(G[i])>=6) yup();
  int cnt=0;
  REP(i,N) if(SZ(G[i])==4) {
    ++cnt;
  }
  if(cnt>2) yup();
  if(cnt<2) nope();
  VI us;
  REP(i,N) if(SZ(G[i])==4) us.push_back(i);
  assert(SZ(us)==2);
  int a=us.front(),b=us.back();
  REP(i,N) GG[i]=G[i];
  REP(i,N) G[i].clear();
  REP(u,N)FORR(v,GG[u]) if(u!=b&&v!=b) G[u].push_back(v);
  ZERO(viz);
  dfs(a);
  int cnt2=0;
  REP(i,N) cnt2+=viz[i];
  if(cnt2==N-1) nope();
  else yup();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
