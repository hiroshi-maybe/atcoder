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

// $ cp-batch GraphPartition | diff GraphPartition.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GraphPartition.cpp && ./a.out

/*
 
 10/5/2019
 
 14:58-16:24 AC
 
 Problem condition <=> bipartite graph
 Unknown <=> Diameter of bipartite graph
 
 Very cool problem reduction.
 
 https://img.atcoder.jp/agc039/editorial.pdf
 
 5/9/2020
 
 17:43-18:10 solve again
 
 */

const int MAX_N=200+1;
string S[MAX_N];
int mx[MAX_N][MAX_N];
int N;

bool ans=true;
const int Inf=1e7;
int viz[MAX_N];
void dfs(int u, int col) {
  if(viz[u]!=-1) {
    if(viz[u]!=col) ans=false;
    return;
  }
  viz[u]=col;
  REP(v,N)if(u!=v&&S[u][v]=='1') dfs(v,col^1);
}
void solve() {
  REP(i,N)REP(j,N) mx[i][j]=i==j?0:Inf;
  REP(i,N)REP(j,N)if(S[i][j]=='1') mx[i][j]=1;

  REP(k,N)REP(i,N)REP(j,N) SMIN(mx[i][j],mx[i][k]+mx[k][j]);
  int res=0;
  REP(i,N)REP(j,N)SMAX(res,mx[i][j]+1);
  MINUS(viz);
  dfs(0,0);
  if(!ans) res=-1;
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
