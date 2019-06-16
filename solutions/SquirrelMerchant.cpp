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

// $ cp-batch SquirrelMerchant | diff SquirrelMerchant.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SquirrelMerchant.cpp && ./a.out

/*
 
 6/15/2019
 
 6:01-7:00 give up
 14:45-15:40, 16:12-16:30 read editorial and got AC
 
 https://img.atcoder.jp/diverta2019-2/editorial.pdf
 
 I tried to reduce to brute-force though, I could not figure out optimal buy/sell patterns.
 
 General pattern is below (I figured out this at the end of contest):
 1. d->m[3] at A
 2. m[3]->d at B (maximize `d`)
 3. d->m[3] at B
 4. m[3]->d at A (maximize `d`)
 
 I also tried to apply dp though...
 1. I thought dp[5000][5000][5000] states
 2. I was not confident to connect above 4 steps to dp
 
 Concern #1 can be avoided by coupling step #1 and #2 above.
 
 Step 1 and 2: d->m[3]->d
 Step 3 and 4: d->m[3]->d
 
 By reducing problem to those two problems, we can solve each by general knapsack problem.
 This approach solved concern #2 as well.
 Write diagram how metal resources are converted. Then dp should show up.
 
 dp
 https://naoyat.hatenablog.jp/entry/diverta2019-2
 https://twitter.com/small_onions/status/1139895519176622085
 https://twitter.com/kyort0n/status/1139896722308472837
 
 Greedy and brute-force
 http://drken1215.hatenablog.com/entry/2019/06/16/020500
 https://twitter.com/rickytheta/status/1139900637028556800
 https://twitter.com/drafear/status/1139902042556653570
 https://twitter.com/armeria_betrue/status/1139901435993137153
 https://twitter.com/beet_aizu/status/1139901642017402881
 https://twitter.com/satanic0258/status/1139899111128223747
 https://twitter.com/ajis_ka/status/1139897063905214464
 https://twitter.com/beet_aizu/status/1139895576521109504
 
 */
const int MAX_N=5010;
LL A[2][3];
int N;

LL dp[MAX_N*MAX_N];
LL f(int st, int t) {
  ZERO(dp);
  REP(x,MAX_N*MAX_N) REP(i,3) {
    LL a=x>=A[t][i]?dp[x-A[t][i]]+A[1-t][i]:0;
    SMAX(dp[x],max((LL)x,a));
  }
  return dp[st];
}
void solve() {
  ZERO(dp);
  LL d=f(N,0);
  LL res=f(d,1);
  cout<<res<<endl;
}

void solve_wrong() {
  LL res=0;
  REP(j,3) {
    REP(i,2) {
      LL m=N/A[i][j],d=N-m*A[i][j];
      int ii=1-i;
      d+=m*A[ii][j];
//      dump(j,i,m,d);
      SMAX(res,d);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,2)REP(j,3) cin>>A[i][j];
  solve();
  
  return 0;
}
