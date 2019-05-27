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

// $ cp-batch FrogJump | diff FrogJump.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FrogJump.cpp && ./a.out

/*
 
 5/26/2019
 
 17:00-18:00 give up
 20:50-23:10 read editorial and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/05/26/1330
 https://img.atcoder.jp/abc128/editorial.pdf
 http://kazune-lab.net/contest/2019/05/26/abc128/
 
 I thought there are two cases
 1. k*A-k*B=N-1
 2. (k+1)*A-k*B=N-1
 
 However case #1 cannot happen. If happened, step is beyond N-1 😡
 
 # Transform a formula so that
 
     (k+1)*A-k*B=N-1
 <=> A+k*(A-B)=N-1
 
 Define C=A-B, then..
 
 A+k*C=N-1 <=> A=N-1-k*C
 
   S
 = {0,A,A-B,2A-B,2A-2B,...,N-1}
 = {0,A,C,A+C,2C,A+2C,3C,...,k*C,N-1}
 = {0,N-1-k*C,C,N-1-(k-1)*C,2C,...,k*C,N-1}
 = { i*C : i=1..k} ∪ { N-1-i*C : i=1..k } where k*C<(N-1)
 
 Suppose `C` is fixed. Then we can find compute res(k+1,C) from res(k,C) in O(1).
 From condition k*C<N-1, time complexity is upper-bounded by harmoney series O(N*log N) time
 
 Summary:
  - if state increases based on # of steps, dp works
 
 */

const int MAX_N=1e6+1;
LL S[MAX_N];
int N;

void solve() {
  LL res=0;
  FOR(c,1,N-1) {
    LL cur=0;
    SETI viz;
    FOR(k,1,(N-1)/c) {
      LL a=k*c,b=N-1-k*c;
      if(b<=0||a>=N-1) break;
      if(viz.count(a)) break;
      viz.emplace(a);
      if(viz.count(b)) break;
      viz.emplace(b);
      cur+=S[a]+S[b];
//      dump(c,k,a,b,S[a],S[b],cur);
      SMAX(res,cur);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>S[i];
  solve();
  
  return 0;
}
