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

// $ cp-batch MultipleTestcases | diff MultipleTestcases.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MultipleTestcases.cpp && ./a.out

/*
 
 8/5/2018
 
 24:30-24:56 analysis
 24:57-25:06 AC
 
 Editorials:
  - https://img.atcoder.jp/abc099/editorial.pdf
  - https://youtu.be/I-8BnRkq6Ow?t=1845
 
 Summary:
  - It takes too much time in analysis
  - C is small. State can be reduced to few buckets
 
 4/26/2020
 
 solve again
 
 */

const int MAX_N=500+1;
int A[MAX_N][MAX_N],D[31][31];
int N,C;

void solve() {
  VV<int> X(3);
  REP(i,N)REP(j,N) {
    X[(i+j)%3].push_back(--A[i][j]);
  }
  VV<int> cost(3,VI(C));
  REP(c,C)REP(i,3) {
    int sum=0;
    FORR(x,X[i]) sum+=D[x][c];
    cost[i][c]=sum;
  }
  
  int res=1e9;
  REP(c1,C)REP(c2,C)if(c1!=c2)REP(c3,C)if(c2!=c3&&c3!=c1) {
    int sum=cost[0][c1]+cost[1][c2]+cost[2][c3];
    SMIN(res,sum);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>C;
  REP(i,C)REP(j,C) cin>>D[i][j];
  REP(i,N)REP(j,N) cin>>A[i][j];
  solve();
  
  return 0;
}
