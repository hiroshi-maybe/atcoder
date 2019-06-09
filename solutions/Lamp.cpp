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

// $ cp-batch Lamp | diff Lamp.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Lamp.cpp && ./a.out

/*
 
 6/9/2019
 
 5:12-5:39 AC
 
 */

const int MAX_N=2010+1;
string A[MAX_N];
int N,M;

int pos[4][MAX_N][MAX_N];
void solve() {
//  REPE(i,N+1) dump(A[i]);
  
  // l
  FORE(i,1,N)FORE(j,1,M) pos[0][i][j]=A[i][j]=='#'?j:pos[0][i][j-1];
  // r
  FORE(i,1,N) {
    pos[1][i][M+1]=M+1;
    for(int j=M; j>=1; --j) pos[1][i][j]=A[i][j]=='#'?j:pos[1][i][j+1];
  }
  // t
  FORE(j,1,M)FORE(i,1,N)pos[2][i][j]=A[i][j]=='#'?i:pos[2][i-1][j];
  // b
  FORE(j,1,M) {
    pos[3][N+1][j]=N+1;
    for(int i=N; i>=1; --i)pos[3][i][j]=A[i][j]=='#'?i:pos[3][i+1][j];
  }
  int res=0;
  FORE(i,1,N)FORE(j,1,M) if(A[i][j]!='#') {
    int x=pos[1][i][j]-pos[0][i][j]-1;
    int y=pos[3][i][j]-pos[2][i][j]-1;
    SMAX(res,x+y-1);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REPE(i,N+1) A[i]=string(M+2,'#');
  REP(i,N) {
    string s; cin>>s;
    FORE(j,1,M) A[i+1][j]=s[j-1];
  }
  solve();
  
  return 0;
}
