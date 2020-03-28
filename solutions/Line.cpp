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

// $ cp-batch Line | diff Line.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Line.cpp && ./a.out

/*
 
 3/28/2020
 
 5:12-5:57 give up
 8:24-8:30 AC
 
 https://img.atcoder.jp/abc160/editorial.pdf
 
 https://atcoder.jp/contests/abc160/submissions/11291903
  - O(N) solution
 
 */

const int MAX_N=1e4+1;
int N,X,Y;

VI G[MAX_N];
const int Inf=1e7;
int mx[MAX_N][MAX_N];
void solve() {
  REP(i,N)REP(j,N) mx[i][j]=i==j?0:Inf;
  queue<II> Q;
  REP(i,N) Q.emplace(i,i);
  while(SZ(Q)) {
    int s,u; tie(s,u)=Q.front(),Q.pop();
    FORR(v,G[u]) {
      if(mx[s][v]>mx[s][u]+1) {
        mx[s][v]=mx[s][u]+1;
        Q.emplace(s,v);
      }
    }
  }
  VI res(N);
  REP(j,N)REP(i,j) res[mx[i][j]]++;
  FORE(k,1,N-1) cout<<res[k]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>X>>Y;
  --X,--Y;
  REP(i,N-1) G[i].push_back(i+1),G[i+1].push_back(i);
  G[X].push_back(Y),G[Y].push_back(X);
  
  solve();
  
  return 0;
}
