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

// $ cp-batch SnukeTheWizard | diff SnukeTheWizard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SnukeTheWizard.cpp && ./a.out

/*
 
 5/9/2019
 
 19:45-20:27, 21:07-21:23 give up
 
 O(1) for each robot
 => 🙅‍♂️
 Group by alphabet bucket
 => 🙅‍♂️
 Query backward
 => 🙅‍♂️
 
 🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️🙅‍♂️
 
 https://twitter.com/beet_aizu/status/1111995127331864577
 => Reduction to interval can be expected
 
 5/10/2019
 
 14:36-15:50 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/03/30/0900
 https://img.atcoder.jp/exawizards2019/editorial.pdf
 https://youtu.be/dUCnyA3Rj_0?t=1806
 Look at left-end. If robot at `2` falls, robot at `1` falls too.
 That is because robot in right position never passes left robots.
 
 Summary:
  - I'm born without ability to figure out monotonic property. Very stupid.
  - Solving by interval was completely out of mind. shit.
 
 */

const int MAX_N=1e6+1;
int N,Q;
string S;
char T[MAX_N],D[MAX_N];

bool okl(int i) {
  REP(j,Q) if(S[i]==T[j]) {
    int d=D[j]=='R'?1:-1;
    i+=d;
    if(i==-1) return true;
  }
  return false;
}
bool okr(int i) {
  REP(j,Q) if(S[i]==T[j]) {
    int d=D[j]=='R'?1:-1;
    i+=d;
    if(i==N) return true;
  }
  return false;
}
void solve() {
  int L=0,R=0;
  int good=-1,bad=N;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (okl(m)?good:bad)=m;
  }
  L=good;
  good=N,bad=-1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (okr(m)?good:bad)=m;
  }
  R=good;
//  dump(L,R);
  cout<<max(0,R-L-1)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q>>S;
  REP(i,Q) {
    cin>>T[i]>>D[i];
  }
  solve();
  
  return 0;
}
