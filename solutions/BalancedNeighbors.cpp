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

// $ cp-batch BalancedNeighbors | diff BalancedNeighbors.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BalancedNeighbors.cpp && ./a.out

/*
 
 3/23/2019
 
 22:57-23:30 give up
 
 3/26/2019
 
 14:45-16:21 read editorials and got AC
 
 http://drken1215.hatenablog.com/entry/2019/03/24/110200
 https://img.atcoder.jp/agc032/editorial.pdf
  
 Summary:
  - subtract from complete graph
 
 */

const int MAX_N=1e2+1;
LL A[MAX_N];
int N;

VI G[MAX_N];
bool verify() {
  SETI S;
  REP(i,N) {
    int s=accumulate(ALL(G[i]),0);
    S.emplace(s);
  }
  if (SZ(S)!=1) return false;
  
  VV<int> mx(N,VI(N,0));
  REP(i,N) mx[i][i]=1;
  REP(i,N)FORR(j,G[i]) mx[i][j]=mx[j][i]=1;
  REP(k,N)REP(i,N)REP(j,N) mx[i][j]|=mx[i][k]&&mx[k][j];
  REP(i,N)REP(j,N) if(!mx[i][j]) return false;
  return true;
}

void solve() {
  vector<SETI> G(N+1);
  REP(i,N)REP(j,N)if(i!=j)G[i+1].emplace(j+1);
  int S,end;
  if(N%2) {
    S=N*(N-1)/2,end=N-1;
  } else {
    S=N*(N-1)/2-1,end=N;
  }
  FORE(i,1,N) {
    int sum=accumulate(ALL(G[i]),0);
    if(sum>S) {
      int d=sum-S;
      assert(G[i].count(d));
      G[i].erase(d),G[d].erase(i);
    }
  }
  vector<II> res;
  FORE(i,1,N) FORR(j,G[i]) if(i<j) res.emplace_back(i,j);
  println("%d",SZ(res));
  FORR(p,res)println("%d %d",p.first,p.second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
