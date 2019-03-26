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

// $ cp-batch LimitedInsertion | diff LimitedInsertion.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LimitedInsertion.cpp && ./a.out

/*
 
 3/23/2019
 
 22:00-22:57 give up
 
 3/26/2019
 
 12:25-12:58 read editorials and got AC
 
 https://img.atcoder.jp/agc032/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/03/24/091900
 
 Research all the cases in small data set.
 It's possible to figure out that B[i]>=i is the condition to build B.
 Let's move backward. If we can build `B`, there should exist `i` s.t. B[i]==i.
 We can remove max { i s.t. B[i]==i} because it doesn't break j<i s.t. B[j]==j.
 Thus maximum such `i` is the only choice because B[j] s.t. B[j]==j cannot move front of the array.
 We can greedily keep removing such elements until getting empty.
 
 Summary:
  - Move backward is always a key to build something by some operation 😡
 
 */

const int MAX_N=1e2+1;
int B[MAX_N];
int N;

VI res;
void f(VI &X) {
  int N=SZ(X);
  for(int i=N-1; i>=0; --i) if(i+1==X[i]) {
    res.push_back(X[i]);
    VI Y;
    REP(j,N) if(i!=j) Y.push_back(X[j]);
    f(Y);
    return;
  }
}
void solve() {
  VI X(B,B+N);
  f(X);
  if(SZ(res)!=N) {
    println("-1");
  } else {
    reverse(ALL(res));
    FORR(x,res) println("%d",x);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>B[i];
  solve();
  
  return 0;
}
