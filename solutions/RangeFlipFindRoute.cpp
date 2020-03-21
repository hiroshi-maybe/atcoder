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

// $ cp-batch RangeFlipFindRoute | diff RangeFlipFindRoute.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RangeFlipFindRoute.cpp && ./a.out

/*
 
 3/21/2020
 
 5:00-5:32 TLE
 5:53 AC
 
 https://img.atcoder.jp/agc043/editorial.pdf
 
 */

const int MAX_N=1e2+1;
string A[MAX_N];
int N,M;

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/};

bool block(II p) {
  return A[p.first][p.second]=='#';
}

int res=1e7;
int cnt=0;
void dfs(int i, int j, vector<II> &path) {
  if(i==N-1&&j==M-1) {
    int ans=0;
    REP(i,SZ(path)) {
      if(block(path[i])) {
        if(i==0||!block(path[i-1])) ++ans;
      }
    }
    dump(++cnt);
//    dumpc(path);
    SMIN(res,ans);
//    dump(res,ans);
    
    return;
  }
  for(auto m : moves) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=M) continue;
    path.emplace_back(ii,jj);
    dfs(ii,jj,path);
    path.pop_back();
  }
}

void solve_tle() {
  vector<II> path={{0,0}};
  
  dfs(0,0,path);
  cout<<res<<endl;
}

bool bl(int i, int j) {
  return A[i][j]=='#';
}

const int Inf=1e7;
int dp[MAX_N][MAX_N];
void solve() {
  REPE(i,N)REPE(j,M) dp[i][j]=Inf;
  dp[0][0]=A[0][0]=='#';
  REP(i,N) REP(j,M) if(i!=0||j!=0) {
    if(i>0) {
      int step=!bl(i-1,j)&&bl(i,j);
      SMIN(dp[i][j],dp[i-1][j]+step);
    }
    if(j>0) {
      int step=!bl(i,j-1)&&bl(i,j);
      SMIN(dp[i][j],dp[i][j-1]+step);
    }
  }
//  REP(i,N)REP(j,M) dump(i,j,dp[i][j]);
  
  cout<<dp[N-1][M-1]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
