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

// $ cp-batch TrafficInAtcoderKingdom | diff TrafficInAtcoderKingdom.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TrafficInAtcoderKingdom.cpp && ./a.out

/*

 10/8/2020

 8:44-9:12 AC

 https://www.slideshare.net/chokudai/arc035

 */

const LL Inf=1e18;
const int MAX_N=400+1;
LL mx[MAX_N][MAX_N];
int N,M;

void solve() {
  REP(k,N)REP(i,N)REP(j,N) SMIN(mx[i][j],mx[i][k]+mx[k][j]);
  int Q; cin>>Q;
  LL res=0;
  REP(j,N)REP(i,j) res+=mx[i][j];
  //dump(res);
  while(Q--) {
    int u,v,w; cin>>u>>v>>w;
    --u,--v;
    //dump(Q,mx[u][v],w);
    REP(j,N)REP(i,j) {
      LL dif=max(mx[i][j]-(mx[i][u]+w+mx[v][j]),mx[i][j]-(mx[i][v]+w+mx[u][j]));
      if(dif>0) {
        //dump(Q,u,v,w,i,j,dif,res);
        res-=dif,mx[i][j]-=dif,mx[j][i]-=dif;
      }
    }
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N)REP(j,N) mx[i][j]=i==j?0:Inf;
  REP(i,M) {
    int u,v,w; cin>>u>>v>>w;
    --u,--v;
    mx[u][v]=mx[v][u]=w;
  }
  solve();

  return 0;
}
