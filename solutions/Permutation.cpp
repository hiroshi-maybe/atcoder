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

// $ cp-batch Permutation | diff Permutation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Permutation.cpp && ./a.out

/*

 4/24/2021

 6:02-6:40 give up
 11:20-11:25 read editorials

 4/25/2021

 18:05-18:55 read editorials

 https://atcoder.jp/contests/abc199/editorial/1164
 https://blog.hamayanhamayan.com/entry/2021/04/25/002423
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.j4quronyf9jo

 https://twitter.com/kyopro_friends/status/1385955161302913025
 https://twitter.com/laycrs/status/1385951824931221508

 */

const int MAX_N=18+1;
int N,M;
vector<II> X[MAX_N];

LL dp[1<<MAX_N];
bool ith(int mask, int i) { return (mask>>i)&1; }
bool ok(int mask) {
  int cnt=__builtin_popcount(mask);
  VI cnts(N,0);
  int cur=0;
  REP(i,N) {
    if(ith(mask,i)) cur+=1;
    cnts[i]=cur;
  }
  FORR(x,X[cnt]) if(cnts[x.first-1]>x.second) return false;
  return true;
}

void solve() {
  dp[0]=1;
  REP(mask,1<<N) REP(j,N) if(!ith(mask,j)) {
    int mask2=mask|(1<<j);
    if(ok(mask2)) dp[mask2]+=dp[mask];
  }
  cout<<dp[(1<<N)-1]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int x,y,z; cin>>x>>y>>z;
    X[x].emplace_back(y,z);
  }
  solve();

  return 0;
}
