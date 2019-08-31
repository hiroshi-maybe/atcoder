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

// $ cp-batch Classified | diff Classified.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Classified.cpp && ./a.out

/*
 
 8/26/2019
 
 17:34-18:15 give up
 
 8/27/2019
 
 20:15-20:35 read editorials
 
 8/30/2019
 
 22:00-23:10 read editorials
 
 8/31/2019
 
 11:40-13:10 read editorials and got AC
 
 https://img.atcoder.jp/jsc2019-qual/editorial.pdf
 https://youtu.be/JTH27weC38k?t=2986
 http://kazune-lab.net/contest/2019/08/24/jsc2019-qual/#d---classified
  - detailed proof
 http://kmjp.hatenablog.jp/entry/2019/08/27/0930
 https://www.hamayanhamayan.com/entry/2019/08/25/090413
 http://merom686.hatenablog.com/entry/2019/08/24/233828
 https://twitter.com/torus711/status/1165258408817131521
 https://twitter.com/a3VtYQo/status/1165258718302240768
 https://twitter.com/kyopro_friends/status/1165259137241907200
 https://twitter.com/shr_pc/status/1165259186877292544
 https://twitter.com/LatteMalta/status/1165259723651739648
 https://twitter.com/kyort0n/status/1165257465685897216
 https://twitter.com/beet_aizu/status/1165257519737868291
 https://twitter.com/tempura_cpp/status/1165257615321915394
 https://twitter.com/tempura_cpp/status/1165260294815248384
 https://twitter.com/Hoi_koroo/status/1165257619197419520
 https://twitter.com/323O65281/status/1165257809308422145
 https://twitter.com/ei1333/status/1165258172837195777
 
 */

int N;

int ith(int i, int mask) {
  return (mask>>i)&1;
}
void solve() {
  REP(i,N)FOR(j,i+1,N) {
    //      dump(i,j);
    for(int k=0; k<31; ++k) if(ith(k,i)!=ith(k,j)) {
      cout<<k+1<<" \n"[j==N-1];
      break;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
