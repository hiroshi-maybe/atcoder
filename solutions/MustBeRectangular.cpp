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

// $ cp-batch MustBeRectangular | diff MustBeRectangular.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MustBeRectangular.cpp && ./a.out

/*
 
 6/22/2019
 
 6:23-6:40 give up
 
 6/23/2019
 
 14:40-15:20 read editorials and got AC
 
 https://img.atcoder.jp/abc131/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/06/23/004700
 http://kmjp.hatenablog.jp/entry/2019/06/23/0930
 https://twitter.com/satanic0258/status/1142427677829160960
 
 It's typical to represent grid relation by bipartite graph if we match x and y coordinate.
 If we have a point (x,y), we consider only pairs between `x` and `y`.
 We never think about relation between `x`s.
 This implies that reducing to bipartite graph is a good choice.
 
 Adding a point is equal to adding an edge in bipartite graph if there is a path with length `3`.
 We can keep adding edges in each connected component and eventually make complete bipartite graph.
 
 */

const int MAX_N=1e5+1;
int X[MAX_N],Y[MAX_N];
int N;

int viz[2*MAX_N];
VI G[2*MAX_N];

set<int> A,B;
void dfs(int u) {
  if(viz[u]) return;
  viz[u]=1;
  if(u<MAX_N) A.emplace(u);
  else B.emplace(u);
  FORR(v, G[u]) dfs(v);
}

void solve() {
  REP(i,N) {
    int x=X[i],y=Y[i];
    G[MAX_N+x].push_back(y);
    G[y].push_back(MAX_N+x);
  }
  LL res=0;
  REP(i,MAX_N) if(!viz[i]) {
    A.clear(),B.clear();
    dfs(i);
    /*
    if(SZ(A)>1&&SZ(B)>1) {
      LL a=(LL)SZ(A)*SZ(B);
      FORR(x,A) a-=SZ(G[x]);
      res+=a;
    }*/
    res+=(LL)SZ(A)*SZ(B);
  }
  res-=N;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) {
    cin>>X[i]>>Y[i];
    --X[i],--Y[i];
  }
  solve();
  
  return 0;
}
