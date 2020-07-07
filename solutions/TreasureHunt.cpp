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

// $ cp-batch TreasureHunt | diff TreasureHunt.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TreasureHunt.cpp && ./a.out

/*

 7/6/2020

 22:09-22:53, 23:35-23:38 AC

 http://www.slideshare.net/chokudai/abc035

 */

const int MAX_N=1e6+1;
LL A[MAX_N],T;
int N,M;

const LL Inf=1e17;
vector<pair<LL,int>> G[MAX_N][2];
LL D[MAX_N][2];
void solve() {
  REP(k,2) {
    REP(i,N) D[i][k]=Inf;
    priority_queue<pair<LL,int>, vector<pair<LL,int>>,greater<pair<LL,int>>> Q;
    Q.emplace(0,0),D[0][k]=0;
    while(SZ(Q)) {
      LL d; int u; tie(d,u)=Q.top(), Q.pop();
      //dump(u,d,D[u][k]);
      if(D[u][k]<d) continue;
      FORR(p,G[u][k]) {
        LL w; int v; tie(w,v)=p;
        //dump(u,v,d+w,D[v][k]);
        if(d+w>D[v][k]) continue;
        D[v][k]=d+w;
        Q.emplace(D[v][k],v);
      }
    }
  }

  LL res=0;
  REP(u,N) {
    LL d=D[u][0]+D[u][1];
    //dump(u,d,T);
    if(d>=T) continue;
    LL rem=T-d;
    //dump(u,D[u],rem,rem*A[u]);
    SMAX(res,rem*A[u]);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>T;
  REP(i,N) cin>>A[i];
  REP(i,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    G[u][0].emplace_back(w,v);
    G[v][1].emplace_back(w,u);
  }
  solve();

  return 0;
}
