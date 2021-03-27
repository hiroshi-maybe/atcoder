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

// $ cp-batch ConstructAPalindrome | diff ConstructAPalindrome.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ConstructAPalindrome.cpp && ./a.out

/*

 3/27/2021

 6:02-6:42 WA
 6:55 AC after the contest

 https://atcoder.jp/contests/abc197/editorial/994
 https://youtu.be/mk8mGugZREg

 https://twitter.com/satanic0258/status/1375805861650571270
 https://twitter.com/ngtkana/status/1375808693141303301
 https://twitter.com/laycrs/status/1375804869139783683
 https://twitter.com/tanakh/status/1375806322705240068
 https://twitter.com/maspy_stars/status/1375805969561579524
 https://twitter.com/kyopro_friends/status/1375842136361369600

 */

const int MAX_N=1e3+1;
LL A[MAX_N];
int N,M;

LL D[MAX_N][MAX_N];
VI G[MAX_N][26];
void solve() {
  const LL Inf=1e17;
  REP(i,N)REP(j,N) D[i][j]=Inf;
  queue<II> Q;
  REP(i,N) Q.emplace(i,i),D[i][i]=0;
  REP(u,N) REP(c,26) FORR(v,G[u][c]) if(u!=v) {
    Q.emplace(u,v),D[u][v]=1;
  }

  while(SZ(Q)) {
    int u1,u2; tie(u1,u2)=Q.front(); Q.pop();
    int d=D[u1][u2];
    REP(c,26) {
      FORR(v1,G[u1][c]) FORR(v2,G[u2][c]) {
        if(D[v1][v2]>d+2) {
          D[v1][v2]=d+2,Q.emplace(v1,v2);
        }
      }
    }
  }

  LL res=D[0][N-1];
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v; char c; cin>>u>>v>>c;
    --u,--v;
    int cc=c-'a';
    G[u][cc].emplace_back(v);
    G[v][cc].emplace_back(u);
  }
  solve();

  return 0;
}
