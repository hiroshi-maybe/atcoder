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

// $ cp-batch TakahashiAndCards | diff TakahashiAndCards.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TakahashiAndCards.cpp && ./a.out

/*

 7/16/2020

 9:03-9:22 AC

 https://img.atcoder.jp/data/arc/060/editorial.pdf

 */

const int MAX_N=50+1;
int X[MAX_N];
int N,A;

const int MAX_S=MAX_N*MAX_N;
LL dp[MAX_N][MAX_S];
void solve() {
  dp[0][0]=1;
  REP(i,N)for(int cnt=N-1; cnt>=0; --cnt) for(int sum=MAX_S-1; sum>=0; --sum) {
    //if(dp[cnt][sum]>0) dump(i,cnt,sum,dp[cnt][sum]);
    if(sum+X[i]<MAX_S) dp[cnt+1][sum+X[i]]+=dp[cnt][sum];
  }
  LL res=0;
  FORE(cnt,1,N) {
    res+=dp[cnt][cnt*A];
    //if(dp[cnt][cnt*A]>0) dump(cnt,cnt*A,dp[cnt][cnt*A]);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>A;
  REP(i,N) cin>>X[i];
  solve();

  return 0;
}
