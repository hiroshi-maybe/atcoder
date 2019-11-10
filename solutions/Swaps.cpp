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

// $ cp-batch Swaps | diff Swaps.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Swaps.cpp && ./a.out

/*
 
 11/9/2019
 
 4:40-4:56 give up
 12:40-15:11 read editorials
 
 11/10/2019
 
 8:40-10:10 read editorials
 
 https://youtu.be/qG1nQxAeaVA?t=637
 https://img.atcoder.jp/nikkei2019-2-qual/editorial.pdf
 https://www.hamayanhamayan.com/entry/2019/11/10/005140
 https://twitter.com/hanseilimak/status/1193280625291120640
 https://atcoder.jp/contests/nikkei2019-2-qual/submissions/8354327
 
 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N];
int N;

bool solve() {
  vector<II> BA(N);
  REP(i,N) BA[i]={B[i],A[i]};
  sort(ALL(BA));
  VI AA(N);
  REP(i,N)AA[i]=A[i];
  sort(ALL(AA));
  REP(i,N)if(AA[i]>BA[i].first) return false;
  REP(i,N-1) if(AA[i+1]<=BA[i].first) return true;

  vector<II> X;
  REP(i,N) X.emplace_back(BA[i].second,i);
  sort(ALL(X));
  VI viz(N,0);
  function<void(int)> dfs=[&](int u)->void {
    if(viz[u]) return;
    viz[u]=1;
    dfs(X[u].second);
  };
  int cnt=0;
  REP(i,N)if(!viz[i]) ++cnt,dfs(i);
  return cnt>1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  cout<<(solve()?"Yes":"No")<<endl;
  
  return 0;
}
