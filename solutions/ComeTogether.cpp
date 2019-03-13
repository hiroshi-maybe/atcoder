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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch ComeTogether | diff ComeTogether.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ComeTogether.cpp && ./a.out

/*
 
 3/12/2019
 
 16:16-16:50 AC
 
 https://img.atcoder.jp/nikkei2019-final/editorial.pdf
 https://betrue12.hateblo.jp/entry/2019/02/18/235125
 http://tutuz.hateblo.jp/entry/2019/02/22/154515
 
 */

const int MAX_N=1e6+1;
LL A[2][MAX_N];
int N[2],K;

LL X[2][MAX_N];
LL cum[2][MAX_N];
void solve() {
  REP(c,2)FORE(i,1,N[c]) X[c][i]=N[1-c];
  REP(c,2)REP(i,K) X[c][A[c][i]]--;
  REP(c,2)REPE(i,N[c]) cum[c][i+1]=cum[c][i]+X[c][i];
  LL tot[2];
  REP(c,2) tot[c]=cum[c][N[c]+1];
  dump(tot[0],tot[1]);
  LL mid[2];
  REP(c,2) {
    int x=upper_bound(cum[c],cum[c]+N[c]+1,tot[c]/2)-cum[c];
    mid[c]=x-1;
  }
  dump(mid[0],mid[1]);
  LL res=0;
  REP(c,2) {
    LL m=mid[c];
    REPE(i,N[c]) res+=abs(i-m)*X[c][i];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(c,2)cin>>N[c];
  cin>>K;
  REP(i,K)REP(c,2) cin>>A[c][i];
  solve();
  
  return 0;
}
