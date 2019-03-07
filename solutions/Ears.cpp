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

// $ cp-batch Ears | diff Ears.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Ears.cpp && ./a.out

/*
 
 3/3/2019
 
 21:01-22:08 give up
 
 3/6/2019
 
 17:45-18:20 read editorials
 
 3/7/2019 14:15-14:50 got AC
 
 https://youtu.be/WhDtakdCPg4?t=2159
  https://img.atcoder.jp/yahoo-procon2019-qual/editorial.pdf
 https://betrue12.hateblo.jp/entry/2019/02/10/014031
 http://drken1215.hatenablog.com/entry/2019/02/10/014800
 https://misteer.hatenablog.com/entry/minpro2019-qual
 
 https://twitter.com/noisy_noimin/status/1094235173871267841
 https://twitter.com/nebukuro09/status/1094235107852902402
 https://twitter.com/torus711/status/1094235148143386624
 https://twitter.com/hamko_intel/status/1094234963552067585
 https://twitter.com/rickytheta/status/1094234926788927489
 https://twitter.com/beet_aizu/status/1094234574425444352
 
 Walking pattern in an array can be generalized as below:
 
 -------2------->
 <-1-       <-3--
 
 Problem can be reduced to more a more accessible problem (more general problem)
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

const LL Inf=1e16;
LL dp[MAX_N][5];
void solve() {
  REP(i,MAX_N)REP(s,5)dp[i][s]=Inf;
  
  dp[0][0]=0;
  REP(i,N)REP(s,5) {
    SMIN(dp[i+1][0],dp[i][0]+A[i]);
    if(s<=1) {
      int d=A[i]%2!=0;
      if(A[i]==0) d=2;
      SMIN(dp[i+1][1],dp[i][s]+d);
    }
    if(s<=2) SMIN(dp[i+1][2],dp[i][s]+(A[i]%2==0));
    if(s<=3) {
      int d=A[i]%2!=0;
      if(A[i]==0) d=2;
      SMIN(dp[i+1][3],dp[i][s]+d);
    }
    if(s<=4)SMIN(dp[i+1][4],dp[i][s]+A[i]);
  }
  cout<<*min_element(dp[N],dp[N]+5)<<endl;
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
