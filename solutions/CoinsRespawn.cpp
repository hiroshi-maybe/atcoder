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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch CoinsRespawn | diff CoinsRespawn.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CoinsRespawn.cpp && ./a.out

/*
 
 8/15/2019
 
 15:18-15:49 give up
 
 Very stupid that I've not remembered condition of NP-hardness of longest path problem. If shortest path is not necessarily simple path, it's not NP-hard (Bellman ford works)
 
 8/16/2019
 
 13:40-15:15 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/08/10/0900
 https://youtu.be/1Z6ofKN03_Y?t=5294
 https://twitter.com/torus711/status/1160184875506212864
 
 ABC061 D - Score Attack
  - http://drken1215.hatenablog.com/entry/2019/02/16/075900
  - https://kimiyuki.net/writeup/algo/atcoder/abc-061-d/
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N],W[MAX_N];
int N,M,P;

const LL Inf=1e10;
LL D[MAX_N];
void solve() {
  REP(i,N) D[i]=Inf;
  D[0]=0;
  REP(_,N-1) REP(i,M) {
    int u=A[i],v=B[i],w=W[i];
    SMIN(D[v], D[u]+w);
  }
  dumpC(D,D+N);
  REP(i,M) {
    int u=A[i],v=B[i],w=W[i];
    if(D[u]+w<D[v]&&D[v]<1e9) D[v]=-Inf;
  }
  dumpC(D,D+N);
  REP(_,N-1) REP(i,M) {
    int u=A[i],v=B[i],w=W[i];
    SMIN(D[v], D[u]+w);
  }
  dumpC(D,D+N);
  LL res=D[N-1];
  if(res<=-1e9) res=-1;
  else if(res>0) res=0;
  else res=-res;
  
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>P;
  REP(i,M) {
    cin>>A[i]>>B[i]>>W[i];
    --A[i],--B[i],W[i]=P-W[i];
  }
  solve();
  
  return 0;
}
