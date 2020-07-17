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

// $ cp-batch Finalists | diff Finalists.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Finalists.cpp && ./a.out

/*

 7/17/2020

 9:24-10:20 AC

 https://kmjp.hatenablog.jp/entry/2014/08/21/0930
 https://www.slideshare.net/chokudai/code-formula2014-quala

 */

const int MAX_N=50+1,MAX_K=1e3+1;
int A[MAX_N][MAX_K];
int N,K;

void solve() {
  VI viz((int)1e6+1,0);
  priority_queue<III,vector<III>,greater<III>> Q;
  int k=K;
  REP(i,N) {
    int remr=N-i-1;
    VI res;
    REP(j,K) Q.emplace(j,i,A[i][j]);
    //dump(i,SZ(Q));
    while(SZ(Q)&&k>0) {
      int rank,ii,id; tie(rank,ii,id)=Q.top();
      if(viz[id]) {
        Q.pop();
        continue;
      }
      //dump(i,rank,ii,id,k-rank*remr);
      if(k-rank*remr>0) {
        res.push_back(id),Q.pop(),viz[id]=1,--k;
      } else break;
    }
    sort(ALL(res));
    REP(i,SZ(res)) cout<<res[i]<<" ";
    cout<<endl;
  }
  assert(k==0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  REP(i,N)REP(j,K) cin>>A[i][j];
  solve();

  return 0;
}
