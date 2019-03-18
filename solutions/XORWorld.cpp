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

// $ cp-batch XORWorld | diff XORWorld.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XORWorld.cpp && ./a.out

/*
 
 3/16/2019
 
 11:25-11:54 AC
 
 n^(n+1) = 1 for even `n`
 <=> XOR{x : x=1,..,n} = { n(n%4==0), 1(n%4==1), n^1(n%4==2), 0(n%4==3) }
 
 https://img.atcoder.jp/abc121/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/03/09/224100
 https://betrue12.hateblo.jp/entry/2019/03/09/224330
 http://purple-jwl.hatenablog.com/entry/20121008/1349694710
 https://twitter.com/259_Momone/status/1104376943535771648
 
 */

LL A,B;

// cycle property
LL f(LL X) {
  if(X<0) return 0;
  LL cy=X/4;
//  dump(X,cy,cy*4,X);
  assert(cy*4<=X);
  LL res=0;
  for(LL i=cy*4; i<=X; ++i) res^=i;
  return res;
}

// math property
LL f_math(LL X) {
  if(X<0) return 0;
  LL rem=X%4;
  if(rem==0) return X;
  if(rem==1) return 1;
  if(rem==2) return X^1;
  return 0;
}

LL f_org(LL X) {
  if(X<0) return 0;
  LL res=0;
  REP(i,45) {
    LL cy=1LL<<(i+1);
    LL a=(X+1)/cy,b=(X+1)%cy;
    LL pow=(1LL<<i);
    LL p=pow*a+max(0LL,b-pow);
    p%=2;
//    dump(i,a,b,p);
    if(p==1LL) res|=(1LL<<i);
  }
  return res;
}
void solve() {
  LL res=f(A-1)^f(B);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>A>>B;
  solve();
  
  return 0;
}
