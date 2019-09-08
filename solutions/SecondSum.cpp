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

// $ cp-batch SecondSum | diff SecondSum.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SecondSum.cpp && ./a.out

/*
 
 9/7/2019
 
 6:03-6:40 give up

 I iterated right boundary from left to right.
 Sounds like there is monotonic property though, I couldn't figure out how to compute in O(1) for each right boundary.
 
 9/8/2019
 
 14:50-16:20 read editorials and got AC
 
 My approach was completely wrong. 
 
 https://youtu.be/VSeggcnxwrc?t=5634
 https://img.atcoder.jp/abc140/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/09/08/0900
 https://twitter.com/tempura_cpp/status/1170330911491018753?s=20
 https://twitter.com/satanic0258/status/1170331002545139712
 
 */

const int MAX_N=1e6+1;
int P[MAX_N];
int N;

int pos[MAX_N];
void solve() {
  REP(i,N) pos[P[i]]=i;
  multiset<int> S; S.emplace(-1),S.emplace(-1),S.emplace(N),S.emplace(N);
  LL res=0;
  for(int a=N; a>=1; --a) {
    int i=pos[a];
    auto r=S.upper_bound(i),l=r; --l;
    int l2=*l; --l; int l1=*l;
    int r1=*r; ++r; int r2=*r;
    LL x=(r1-i)*(l2-l1),y=(r2-r1)*(i-l2);
    res+=+(x+y)*a;
    S.emplace(i);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>P[i];
  solve();
  
  return 0;
}
