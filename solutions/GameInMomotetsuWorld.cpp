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

// $ cp-batch GameInMomotetsuWorld | diff GameInMomotetsuWorld.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GameInMomotetsuWorld.cpp && ./a.out

/*

 5/16/2021

 11:16-12:31 AC

 https://atcoder.jp/contests/abc201/editorial/480
 https://www.youtube.com/watch?v=Wx6020jI4NM

 */

const int MAX_N=2000+10;
string A[MAX_N];
int N,M;

const int Inf=1e8;
II memo[MAX_N][MAX_N];

II f(int i, int j) {
  //if(i>=N) return (j<M-1?make_pair(-Inf,-Inf):make_pair(0,0));
  //if(j>=M) return (i<N-1?make_pair(-Inf,-Inf):make_pair(0,0));
  //if(i>=N||j>=M) return {-Inf,-Inf};
  //if(i==N-1&&j==M-1) return {0,0};
  if(memo[i][j].first!=-Inf) return memo[i][j];
  II &res=memo[i][j];

  vector<II> xs;

  REP(di,2)REP(dj,2)if(di+dj==1) {
    int ii=i+di,jj=j+dj;
    if(ii>=N||jj>=M) continue;
    auto x=f(ii,jj);
    swap(x.first,x.second);
    int d=(A[ii][jj]=='+')?1:-1;
    x.first+=d;
    xs.push_back(x);
  }

  if(SZ(xs)==0) {
    assert(i==N-1&&j==M-1);
    return {0,0};
  }
  if(SZ(xs)==1) return res=xs[0];

  if(xs[0].first-xs[0].second>xs[1].first-xs[1].second) {
    res=xs[0];
  } else {
    res=xs[1];
  }

/*
  if(xs[0].first!=xs[1].first) {
    res=xs[0].first>xs[1].first?xs[0]:xs[1];
  } else {
    res=xs[0].second<xs[1].second?xs[0]:xs[1];
  }*/
  dump(i,j,res.first,res.second);
  return res;
}

void solve() {
  REP(i,N)REP(j,M) memo[i][j]={-Inf,-Inf};
  II res=f(0,0);
  dump(res.first, res.second);
  string ans="Draw";
  if(res.first>res.second) ans="Takahashi";
  else if(res.first<res.second) ans="Aoki";
  cout<<ans<<endl;
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
