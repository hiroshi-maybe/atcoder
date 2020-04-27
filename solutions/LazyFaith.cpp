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

// $ cp-batch LazyFaith | diff LazyFaith.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LazyFaith.cpp && ./a.out

/*
 
 3/11/2019
 
 14:54-15:14 AC
 
 https://img.atcoder.jp/abc119/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/02/24/230900
 
 4/25/2020
 
 solve again
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N,M;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int Q;
  cin>>N>>M>>Q;
  const LL Inf=1e12;
  A[0]=B[0]=-Inf;
  REP(i,N) cin>>A[i+1];
  REP(i,M) cin>>B[i+1];
  A[N+1]=B[M+1]=Inf;

  //sort(A,A+N),sort(B,B+M);
  while(Q--) {
    LL x; cin>>x;
    int i=lower_bound(A,A+N+2,x)-A,j=lower_bound(B,B+M+2,x)-B;
    vector<LL> dx1={x-A[i-1],A[i]-x},dx2={x-B[j-1],B[j]-x};
//    dumpc(dx1);
//    dumpc(dx2);
    vector<LL> ds={
      max(dx1[0],dx2[0]),
      max(dx1[1],dx2[1]),
      dx1[0]*2+dx2[1],
      dx2[0]*2+dx1[1],
      dx1[1]*2+dx2[0],
      dx2[1]*2+dx1[0]};
    LL res=*min_element(ALL(ds));
    cout<<res<<endl;
  }
  
  return 0;
}
