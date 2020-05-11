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

// $ cp-batch IceRinkGame | diff IceRinkGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address IceRinkGame.cpp && ./a.out

/*
 
 4/23/2018
 
 9:10-9:23 analysis
 9:24-9:38 1WA by binary search 🤔
 9:48 2WA
 9:49-10:27 Figured out behavior of the range by simulation and got AC
 
 Editorials:
  - https://img.atcoder.jp/agc020/editorial.pdf
  - http://hamayanhamayan.hatenablog.jp/entry/2018/01/15/003942
  - https://kimiyuki.net/blog/2018/02/22/agc-020-b/
  - http://skbtkey.hatenablog.com/entry/AGC020_B
 
 Summary:
  - It turned out that binary search solution had overflow bug 😞

 5/10/2020
 
 22:16-23:02 solve again
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int K;

void fail() {
  cout<<-1<<endl;
  exit(0);
}

bool ok1(LL N) {
  LL n=N;
  REP(i,K) {
    LL g=n/A[i];
    n=g*A[i];
  }
  return n>=2;
}
bool ok2(LL N) {
  LL n=N;
  REP(i,K) {
    LL g=n/A[i];
    n=g*A[i];
  }
  return n<=2;
}

void solve_bs() {
  LL good=2e18,bad=0;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool res=ok1(mid);
    (res?good:bad)=mid;
  }
  LL lb=good;
  
  good=1,bad=2e18;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool res=ok2(mid);
    (res?good:bad)=mid;
  }
  LL hb=good;
  if(hb<lb) fail();
  cout<<lb<<" "<<hb<<endl;
}

void solve() {
  LL l=2,r=2;
  for(int i=K-1; i>=0; --i) {
    LL g1=(l+A[i]-1)/A[i],g2=r/A[i];
    SMAX(g1,1LL);
    if(g2<=0) fail();
    if(g2<g1) fail();
    l=A[i]*g1,r=A[i]*g2+A[i]-1;
//    dump(i,g1,g2,B1[i],B2[i]);
  }
  cout<<l<<" "<<r<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>K;
  REP(i,K) cin>>A[i];
  solve();
  
  return 0;
}
