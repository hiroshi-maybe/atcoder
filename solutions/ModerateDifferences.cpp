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

/*

 4/27/2018

 12:50-13:30 give up

 Editorials:
  - https://atcoder.jp/img/agc017/editorial.pdf
  - https://youtu.be/5usHNxVUzqk?t=920
  - http://hamayanhamayan.hatenablog.jp/entry/2017/07/10/020557
  - http://phwinx.hatenablog.com/entry/2017/07/14/014057
  - https://kimiyuki.net/blog/2017/07/09/agc-017-b/
   - clearly mentioning to commutativity
  - http://www.learning-algorithms.com/entry/2017/08/19/222158
  - https://ei1333.hateblo.jp/entry/2017/07/10/235514
  - https://twitter.com/tanakh/status/884051844955111425
  - https://twitter.com/satanic0258/status/884057667529879553
  - https://twitter.com/sigma425/status/884101055193112576

 Making formula? Simulation? I have no idea how to come up with this solution 😞

 14:00-14:30 read editorials and AC

 Key:
  - Two options: up (x[i]<x[i+1]) and down (x[i]>x[i+1])
  - Lower bound and upper bound are determined based on the two sufficient conditions (up or down)
  - Order of decision doesn't matter in terms of aggregated bounds
   - "Commutative"

 Summary:
  - Accumulating lower bound and upper bound may be popular as seen in GCJ 2018 R1A
  - Figuring out that two options are sufficient and order doesn't matter is the key though, it was hard for me 😞

 2/2/2021

 8:16-9:12 solve again by myself

 */

// $ cp-batch ModerateDifferences | diff ModerateDifferences.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ModerateDifferences.cpp && ./a.out

LL A,B,C,D;
int N;

bool solve() {
  LL T=abs(A-B);
  int M=N-1;
  REPE(x,M) {
    int y=M-x;
    LL l=C*x-D*y,r=D*x-C*y;
    if(l<=T&&T<=r) return true;
  }
  return false;
}

bool solve_v1() {
  REP(x,N-1) {
    LL l=C*x-D*(N-1-x),r=D*x-C*(N-1-x);
    if(l<=B-A&&B-A<=r) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N>>A>>B>>C>>D;
  string yes="YES",no="NO";
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
