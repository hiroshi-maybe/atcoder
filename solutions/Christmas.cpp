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

// $ cp-batch Christmas | diff Christmas.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Christmas.cpp && ./a.out

/*
 
 2/3/2019
 
 10:40-11:12 WA
 11:17 AC
 
 https://img.atcoder.jp/abc115/editorial.pdf
 
 */

int N;
LL X;

const int MAX_N=52;
pair<LL,LL> dp[MAX_N];
pair<LL,LL> f(int x) {
  if(x==0) return dp[x]={1,1};
  auto p=f(x-1);
  LL a=2LL*p.first+1,b=2LL*p.second+3;
//  dump(x,a,b);
  return dp[x]={a,b};
}
LL g(LL x, int lv) {
  SMAX(x,0LL);
  SMIN(x,dp[lv].second);
  if(x==0) return 0;
  if(x==dp[lv].second) return dp[lv].first;
  --x;
//  LL l=g(min(max(0LL,x),dp[lv-1].second),lv-1);
  LL l=g(x,lv-1);
  x-=dp[lv-1].second;
  LL c=0;
  if(x>0) ++c;
  x--;
//  LL r=g(min(max(0LL,x),dp[lv-1].second),lv-1);
  LL r=g(x,lv-1);
//  dump(x,lv,dp[lv].second,l,c,r);
  return l+c+r;
}
void solve() {
  f(50);
  cout<<g(X,N)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>X;
  solve();
  
  return 0;
}
