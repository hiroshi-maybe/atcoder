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

// $ cp-batch EvenDegrees | diff EvenDegrees.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EvenDegrees.cpp && ./a.out

/*
 
 7/14/2019
 
 6:27-6:58, 7:25-7:46 WA and give up
 
 I tried to color each vertex for ALL IN edges.
 However this may not even construct connected component.
 
 13:15-14:40 read editorial.
 15:20-16:40 read editorial and got AC
 
  https://twitter.com/hanseilimak/status/1150557871358144513
 
 Make a spanning tree. This is the first step. This is typical technique.
 Traversing a tree from leaves vs root. There are two major ways.
 In this problem, we build in a bottom up way from leaves so that we can adjsut parity of each vertices. While traversing vertices in bottom-up, we have one extra edges connected with its parent. We can adjust parity of each vertex by it.
 Adjust by an edge with parent. This is the key insight to solve this problem.
 Finally we need to show this works for any graph with even edges.
 All the vertices except root `r` is now satisfying OUT(u) = even.
 Divide `V` into {r} and V' where V = {r} + V' and ∑ { OUT(u) : u∈V' }
 All the edges should contribute to 1 OUT degree.
 
 M = OUT(r) + ∑ { OUT(u) : u∈V' }
 
 Since OUT(u) is even. ∑ { OUT(u) : u∈V' } is even as well.
 We know that `M` is even.
 
   OUT(r)
 = M - ∑ { OUT(u) : u∈V' }
 = even - even
 = even
 
 Algorithm based on above analysis.
 
 1. For edges outside the tree, put arbitrary directions.
 2. Process vertices bottom-up from leaves and determine direction of edge with parent
 
 https://www.youtube.com/watch?v=mNKkjRFwt0Y
 https://img.atcoder.jp/agc035/editorial.pdf
 https://twitter.com/a3VtYQo/status/1150416142114050049
 https://twitter.com/beet_aizu/status/1150414819612168197
 https://twitter.com/heno_code/status/1150415300996653058
 https://twitter.com/small_onions/status/1150415341006102529
 https://twitter.com/kzyKT_M/status/1150414787660005376
 https://twitter.com/Cinnamon_VR/status/1150493387780321280
 
 */

const int MAX_N=1e6+1;
int N,M;

SETI G[MAX_N];
void nope() {
  cout<<"-1"<<endl;
  exit(0);
}
vector<II> res;
int viz[MAX_N];
int dfs(int u) {
  viz[u]=true;
  int p=0;
  while(SZ(G[u])) {
    auto it=G[u].begin();
    int v=*it;
    G[v].erase(G[v].find(u)),G[u].erase(it);
    if(viz[v]) res.emplace_back(u,v),p^=1;
    else {
      int cp=dfs(v);
      if(cp) res.emplace_back(v,u);
      else res.emplace_back(u,v);
      p^=(1-cp);
    }
  }
  return p;
}
void solve() {
  ZERO(viz);
  res.clear();
  int p=dfs(0);
  assert(p==0);
  FORR(p,res) {
    cout<<p.first+1<<" "<<p.second+1<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  if(M%2==1) nope();
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].emplace(v);
    G[v].emplace(u);
  }
  solve();
  
  return 0;
}
