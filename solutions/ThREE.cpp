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

// $ cp-batch ThREE | diff ThREE.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThREE.cpp && ./a.out

/*
 
 3/8/2020
 
 11:29-12:29 give up
 12:47-13:00, 13:30-13:42, 14:18-16:34 read editorials and got AC
 
 https://youtu.be/z9zEs79hHPE?t=605
 https://img.atcoder.jp/hitachi2020/editorial.pdf
 https://atcoder.jp/contests/hitachi2020/submissions/10678122
 https://twitter.com/hanseilimak/status/1236801493073719297
 
 */

const int MAX_N=1e6+1;
VI G[MAX_N];
int N;

VI C[2];
void dfs(int u, int pre, int d) {
  dump(u,d,pre);
  C[d].push_back(u);
  FORR(v,G[u]) if(v!=pre) dfs(v,u,d^1);
}

VI P[3];
void solve() {
  dfs(0,-1,0);
  FORE(i,1,N) P[i%3].push_back(i);
  if(SZ(C[0])<SZ(C[1])) swap(C[0],C[1]);
  assert(SZ(C[0])>=SZ(P[1]));
  VI res(N,-1);
  while(SZ(P[1])) {
    res[C[0].back()]=P[1].back();
    C[0].pop_back(),P[1].pop_back();
  }
  if(SZ(C[0])<SZ(C[1])) swap(C[0],C[1]);
  assert(SZ(C[0])>=SZ(P[2]));
  while(SZ(P[2])) {
    res[C[0].back()]=P[2].back();
    C[0].pop_back(),P[2].pop_back();
  }
  REP(c,2) {
    while(SZ(C[c])) {
      res[C[c].back()]=P[0].back();
      C[c].pop_back(),P[0].pop_back();
    }
  }

  REP(i,N) printf("%d ", res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();
  
  return 0;
}
