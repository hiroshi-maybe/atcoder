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

// $ cp-batch Folia | diff Folia.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Folia.cpp && ./a.out

/*

 5/30/2020

 5:07-6:23 WA
 7:00 give up
 7:10 AC by looking at tweets mentioning to N=0 case

 https://img.atcoder.jp/nomura2020/editorial.pdf
 https://twitter.com/hanseilimak/status/1266842684095737856
 
 https://twitter.com/kyopro_friends/status/1266739316341932032
 https://twitter.com/laycrs/status/1266745573463388161
 https://twitter.com/tanakh/status/1266734865711431683
 https://twitter.com/satanic0258/status/1266828274866388992
 https://twitter.com/satanic0258/status/1266746980870438912

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void nope() {
  cout<<-1<<endl;
  exit(0);
}
void solve() {
  vector<LL> L(N+1,1),R(N+1);
  REPE(i,N) R[i]=i<60?1LL<<i:1e18;
  SMIN(R[N],A[N]),SMAX(L[N],A[N]);
  for(int i=N; i>=0; --i) {
    if(i<N)L[i]=max({L[i],A[i]+(L[i+1]+1)/2});
    if(i<N)R[i]=min({R[i],R[i+1]+A[i]});
    if(L[i]>R[i]) nope();
  }
  LL cur=1;
  vector<LL> res={1};
  FORE(i,1,N) {
    cur=min(2LL*cur,R[i]);
    res.push_back(cur);
    cur-=A[i];
  }

  LL ans=accumulate(ALL(res),0LL);
  cout<<ans<<endl;
}

void solve_org() {
  if(N==0) {
    if(A[0]==1) cout<<1<<endl;
    else nope();
    return;
  }
  vector<LL> B(N+1),PLB(N+1),RB(N+1);
  B[N]=A[N];
  for(int i=N-1; i>=0; --i) {
    B[i]=A[i]+(B[i+1]+1)/2;
    PLB[i]=(B[i+1]+1)/2;
    RB[i]=A[i]+i<N?RB[i+1]:0;
    if(i<60&&B[i]>(1LL<<i)) nope();
  }
  vector<LL> res(N+1);
  res[N]=A[N];
  for(int i=N-1; i>=0; --i) {
    res[i]=A[i]+res[i+1];
    if(i<60) {
      res[i]=min({res[i],1LL<<i});
    }
  }
  FORE(i,1,N) {
    res[i]=min({res[i],2LL*(res[i-1]-A[i-1])});
    //dump(i,res[i],PLB[i],2LL*(res[i-1]-A[i-1]));
    assert(res[i]-A[i]>=PLB[i]);
  }

  //dumpc(res);
  REP(i,N) {
    //dump(i,res[i+1],(res[i]-A[i])*2);
    assert(res[i]-A[i]<=res[i+1]&&res[i+1]<=(res[i]-A[i])*2);
  }
  LL ans=accumulate(ALL(res),0LL);
  cout<<ans<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N+1) cin>>A[i];
  solve();

  return 0;
}
