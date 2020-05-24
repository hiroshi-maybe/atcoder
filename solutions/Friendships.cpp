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

// $ cp-batch Friendships | diff Friendships.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Friendships.cpp && ./a.out

/*

 6/22/2019

 5:50-6:23 AC

 https://img.atcoder.jp/abc131/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/06/22/232000

 5/24/2020

 15:28-16:00 solve again

 */

const int MAX_N=101+1;
int N,K;

void nope() {
  cout<<-1<<endl;
  exit(0);
}
void solve_2nd() {
  if(K>(N-1)*(N-2)/2) nope();
  vector<II> es;
  REP(j,N)REP(i,j) es.emplace_back(i,j);
  sort(ALL(es));
  int k=K;
  while(k--) es.pop_back();
  cout<<SZ(es)<<endl;
  FORR(p,es) cout<<p.first+1<<" "<<p.second+1<<endl;
}

int mx[MAX_N][MAX_N],mx2[MAX_N][MAX_N];
void check() {
  const int Inf=1e5;
  REP(i,N)REP(j,N) {
    mx2[i][j]=mx[i][j]?1:Inf;
  }
  REP(k,N)REP(i,N)REP(j,N) {
    SMIN(mx2[i][j],mx2[i][k]+mx2[k][j]);
  }
  int res=0;
  REP(j,N)REP(i,j) if(mx2[i][j]==2) ++res;
  assert(res==K);
}
void solve() {
  if(K>(N-1)*(N-2)/2) {
    println("-1");
    return;
  }
  REP(i,N)REP(j,N)if(i!=j) mx[i][j]=1;
  int k=K,u=1,v=u+1;
  while(k--) {
    mx[u][v]=mx[v][u]=0;
    if(++v>=N) ++u,v=u+1;
  }
  check();
  vector<II> res;
  REP(j,N)REP(i,j)if(mx[i][j]==1) res.emplace_back(i,j);
  println("%d", SZ(res));
  REP(i,SZ(res)) println("%d %d", res[i].first+1,res[i].second+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  solve();

  return 0;
}
