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

// $ cp-batch SequenceDecomposing | diff SequenceDecomposing.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SequenceDecomposing.cpp && ./a.out

/*
 
 7/20/2019
 
 5:37-5:54 AC
 
 Our algorithm puts numbers from left to right.
 If we put A[i] to existing stacks. We put A[i] after `x` which is largest value strictly less than A[i].
 
 Suppose we have (one of) optimal sequence of color assignment `S`.
 Our algorithm and `S` both have stacks with largest values `a`, `b` and `c` (a<b<A[i]<c).
 `S` is assigning A[i] after `a`. Now we may have `b`<A[i]<`c`.
 On the other hand our algorithm chooses `b` and gets `a`<A[i]<`c`.
 This is better than optimal `S` because a<A[i+1]<b fits after `a`. 
 
 https://img.atcoder.jp/abc134/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/07/20/0900
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  multiset<int> S;
  REP(i,N) {
    if(S.empty()) S.emplace(A[i]);
    else {
      auto it=S.lower_bound(A[i]);
      if(it==S.begin()) {
        S.emplace(A[i]);
      } else {
        --it;
        assert(*it<A[i]);
        S.erase(it),S.emplace(A[i]);
      }
    }
  }
  cout<<SZ(S)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
