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

// $ cp-batch Hanjo | diff Hanjo.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Hanjo.cpp && ./a.out

/*

 3/20/2021

 5:12-6:05 AC

 https://atcoder.jp/contests/abc196/editorial/930

 */

int H,W,A,B;

LL res=0;
void dfs(int a, int b, VV<int> &cur) {
  if(a==0&&b==0) {
    REP(i,H)REP(j,W) assert(cur[i][j]!=0);
    //dump(a,b);
    //REP(i,H) dumpc(cur[i]);
    ++res;
    return;
  }

  REP(i,H)REP(j,W) if(cur[i][j]==0) {
    if(a>0) {
      if(j<W-1&&cur[i][j+1]==0) {
        cur[i][j]=cur[i][j+1]=a+100;
        dfs(a-1,b,cur);
        cur[i][j]=cur[i][j+1]=0;
      }
      if(i<H-1&&cur[i+1][j]==0) {
        cur[i][j]=cur[i+1][j]=a+100;
        dfs(a-1,b,cur);
        cur[i][j]=cur[i+1][j]=0;
      }
    }
    if(b>0&&cur[i][j]==0) {
      //dump(a,b);
      //REP(i,H) dumpc(cur[i]);
      cur[i][j]=b;
      dfs(a,b-1,cur);
      cur[i][j]=0;
    }

    return;
  }
}

void solve() {
  VV<int> cur(H, VI(W,0));
  dfs(A,B,cur);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>H>>W>>A>>B;
  solve();

  return 0;
}
