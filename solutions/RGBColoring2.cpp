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

// $ cp-batch RGBColoring2 | diff RGBColoring2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RGBColoring2.cpp && ./a.out

/*

 4/24/2021

 5:28-6:01 AC

 https://atcoder.jp/contests/abc199/editorial/1163

 https://twitter.com/kzyKT_M/status/1385951707922800645
 https://twitter.com/kyopro_friends/status/1385954017562398727
 https://twitter.com/laycrs/status/1385951824931221508

 */

const int MAX_N=20+1;
LL A[MAX_N];
int N,M;

VI G[MAX_N];

LL res=0;
void dfs(int i, VI &vs, VI &cols, int cnt) {
  if(cnt==SZ(vs)) {
    ++res;
    return;
  }

  int u=vs[i];
  assert(cols[u]==-1);

  VI used(3);
  FORR(v,G[vs[i]]) if(cols[v]!=-1) used[cols[v]]=1;
  REP(c,3) if(!used[c]) {
    cols[u]=c;
    dfs(i+1,vs,cols,cnt+1);
    cols[u]=-1;
  }
}

void solve() {
  VI viz(N);
  LL ans=1;
  REP(u,N) if(!viz[u]) {
    queue<int> Q;
    VI vs;
    Q.emplace(u), vs.push_back(u), viz[u]=1;
    while(SZ(Q)) {
      int u=Q.front(); Q.pop();
      FORR(v,G[u]) if(!viz[v]) {
        Q.emplace(v), vs.emplace_back(v),viz[v]=1;
      }
    }

    res=0;
    VI cols(N,-1);
    dfs(0,vs,cols,0);

    ans*=res;
  }

  cout<<ans<<endl;
}

void solve_tle() {
  VI cols(N,-1);
  //dfs(0,cols,0);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();

  return 0;
}
