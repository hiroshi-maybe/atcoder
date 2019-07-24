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

// $ cp-batch DoNotDuplicate | diff DoNotDuplicate.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DoNotDuplicate.cpp && ./a.out

/*
 
 7/21/2019
 
 6:07-6:48 give up
 
 7/23/2019
 
 15:00-16:30, 17:20-17:40, 20:00-21:20 read editorials
 
 https://youtu.be/eFQGwwdAVWg?t=1788
 https://img.atcoder.jp/agc036/editorial.pdf
 
 Simple code with doubling by @pekempey
 https://atcoder.jp/contests/agc036/submissions/6492744
 
 Deriving stack behavior is the first step.
 suppose f(i) = min { j s.t. X[i]=X[j] }
 Then 0..f(0) is gone. We can keep erasing prefixes.
 
 The second step is figuring out max length of `res`.
 That is less than `N` because X[N*(K-2)]=X[N*(K-1)]
 res with maximum length is X[N*(K-1)+1..X*N-1]
 Thus we want to keep erasing prefixes until remaining length is less than N.
 
 That's possible by doubling. Remember # of index to jump and next position.
 Take 2^k jump from `0` in order of 61,..,1,0 so that we can take as many jumps as possible.
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;
LL K;

const LL Inf=3e18;
LL sum[62][MAX_N];
int suc[62][MAX_N];
void solve() {
  REP(i,N) A[i+N]=A[i];
  VI pos(MAX_N,-1);
  for(int i=2*N-1; i>=0; --i) {
    int a=A[i];
    suc[0][i]=(pos[a]+1)%N;
    sum[0][i]=pos[a]-i+1;
    pos[a]=i;
  }
  REP(i,61)REP(j,N) {
    suc[i+1][j]=suc[i][suc[i][j]];
    sum[i+1][j]=min(Inf,sum[i][j]+sum[i][suc[i][j]]);
  }
  LL p=0;
  for(int i=61; i>=0; --i)if(p+sum[i][p%N]<N*K) {
    p+=sum[i][p%N];
  }
  VI res;
  VI viz(MAX_N,0);
  FOR(i,p%N,N) {
    int a=A[i];
    if(!viz[a]) {
      res.push_back(A[i]),viz[a]=1;
    } else {
      while(true) {
        bool last=res.back()==a;
        viz[res.back()]=0,res.pop_back();
        if(last) break;
      }
    }
  }
  REP(i,SZ(res)) printf("%d%c", res[i]," \n"[i==SZ(res)-1]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
