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

// $ cp-batch Handstand | diff Handstand.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Handstand.cpp && ./a.out

/*
 
 4/17/2019
 
 15:46-16:25 WA
 16:28 bug fix and got AC
 16:34 add solution by sliding window
 
 https://img.atcoder.jp/abc124/editorial.pdf
 
 Run Length Encoding seems to be simplest
  - https://twitter.com/beet_aizu/status/1117064163761647616
  - https://atcoder.jp/contests/abc124/submissions/4945876
 
 */

//const int MAX_N=1e6+1;
int N,K;
string S;

// run length encoding + cumulative sum
void solve() {
  vector<II> X;
  X.emplace_back(1,0);
  REP(i,N) {
    int a=S[i]-'0';
    if(X.back().first!=a) X.emplace_back(a,0);
    X.back().second++;
  }
  int M=SZ(X);
  vector<int> cum(M+1,0);
  REP(i,M) cum[i+1]=cum[i]+X[i].second;
//  dumpc(cum);
  int res=0;
  if(M<2*K+1) res=cum[M];
  for(int i=0; i<M; i+=2) SMAX(res,cum[min(M,i+2*K+1)]-cum[i]);
  cout<<res<<endl;
}

void solve_slidingwindow() {
  deque<II> Q;
  if(S[0]=='0') Q.emplace_back(0,0);
  int l=-1,res=0;
  REP(i,N) {
    if(S[i]=='1'&&(i==0||S[i-1]=='0')) l=i;
    if(S[i]=='1'&&(i==N-1||S[i+1]=='0')) {
      assert(l!=-1);
      int r=i+1;
      //      dump(l,r);
      Q.emplace_back(l,r);
      l=-1;
      if(SZ(Q)==K+1) SMAX(res,r-Q.front().first),Q.pop_front();
    }
  }
  SMAX(res,N-Q.front().first);
  cout<<res<<endl;
}

void solve_twopointers() {
  vector<II> X;
  if(S[0]=='0') X.emplace_back(0,0);
  int l=-1;
  REP(i,N) {
    if(S[i]=='1'&&(i==0||S[i-1]=='0')) l=i;
    if(S[i]=='1'&&(i==N-1||S[i+1]=='0')) {
      assert(l!=-1);
      int r=i+1;
//      dump(l,r);
      X.emplace_back(l,r);
      l=-1;
    }
  }
  if(X.empty()||X.back().second!=N-1) X.emplace_back(N,N);
  int res=0;
  int M=SZ(X);
  REP(i,M) {
    int j=min(i+K,M-1);
    SMAX(res,X[j].second-X[i].first);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>S;
  solve();
  
  return 0;
}
