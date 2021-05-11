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

// $ cp-batch VillageOfMPeople | diff VillageOfMPeople.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VillageOfMPeople.cpp && ./a.out

/*

 5/9/2021

 23:18-23:48 pause

 5/10/2021

 22:20-22:33 WA
 22:35 AC (fixed overlow bug)

 https://youtu.be/QYROykOSgG4?t=667
 https://atcoder.jp/contests/arc118/editorial/1226

 */

const int MAX_K=1e6+1;
LL A[MAX_K];
LL K,N,M;

VV<LL> build(LL d) {
  VV<LL> B(2,vector<LL>(K));
  REP(i,K) {
    LL minb=(M*A[i]-d+N-1)/N;
    LL maxb=(M*A[i]+d)/N;
    B[0][i]=minb,B[1][i]=maxb;
  }
  return B;
}
bool ok(LL d) {
  VV<LL> B=build(d);
  LL minm=0,maxm=0;
  REP(i,K) minm+=B[0][i],maxm+=B[1][i];

  return minm<=M&&M<=maxm;
}

void solve() {
  LL good=2e18,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    (ok(m)?good:bad)=m;
  }

  auto B=build(good);
  vector<LL> res=B[0];
  LL sum=accumulate(ALL(B[0]),0LL);
  assert(sum<=M);
  LL rem=M-sum;
  REP(i,K) {
    while(rem>0&&res[i]<B[1][i]) res[i]++,--rem;
  }

  assert(accumulate(ALL(res),0LL)==M);
  REP(i,K) cout<<res[i]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>K>>N>>M;
  REP(i,K) cin>>A[i];
  solve();

  return 0;
}
