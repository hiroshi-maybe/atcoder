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

// $ cp-batch XXOR | diff XXOR.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XXOR.cpp && ./a.out

/*
 
 2/10/2019
 
 18:27-18:49 WA
 
 2/11/2019
 
 10:45-11:30 AC
 
 It took 45 mins to fix overflow bug 🖕
 1e12*2^50 can be added in invalid transition.
 I misunderstood that this case is ignored by -Inf.
 However x*c[k^1] exceeds LL max.
 
 https://img.atcoder.jp/abc117/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/02/03/224200
 https://betrue12.hateblo.jp/entry/2019/02/03/234159
 http://hamko.hatenadiary.jp/entry/2019/02/03/224024
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
LL K;
int N;

const LL Inf=1e18;
int cnt[50];
LL dp[51][2];
LL solve_dp() {
  REP(i,N)REP(j,50) cnt[j]+=(A[i]>>j)&1;
  reverse(cnt,cnt+50);
  REPE(i,50)REP(j,2)dp[i][j]=-Inf;

  dp[0][0]=0;
  REP(i,50)REP(less,2) if(dp[i][less]>=0) {
    int kbit=(K>>(49-i))&1;
    int a=0,b=1;
    if(!less&&kbit==0) b=0;
    LL x=1LL<<(49-i);
    LL c[2]={N-cnt[i],cnt[i]};
    FORE(k,a,b) {
      SMAX(dp[i+1][less|(k<kbit)],dp[i][less]+x*c[k^1]);
    }
  }
  return max(dp[50][0],dp[50][1]);
}

LL solve() {
  REP(i,N)REP(j,50) cnt[j]+=(A[i]>>j)&1;
  reverse(cnt,cnt+50);
  
  vector<LL> B(51,0);
  for(int i=49; i>=0; --i) {
    LL b=1LL<<(49-i);
    B[i]=B[i+1]+max(b*cnt[i],b*(N-cnt[i]));
  }
  LL res=0,cur=0;
  REP(i,50) {
    int ub=(K>>(49-i))&1;
    LL b=1LL<<(49-i);
    LL c[2]={b*cnt[i],b*(N-cnt[i])};
    if(ub==1) SMAX(res,cur+c[0]+B[i+1]);
    cur+=c[ub];
  }
  SMAX(res,cur);
  return res;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
LL genRandNum(LL lb, LL ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  LL x = rnd() % (LL)(ub - lb);
  return x + lb;
}
vector<LL> genRandSeq(int size, LL lb, LL ub) {
  if (size==0) return {};
  vector<LL> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

LL f(int k) {
  LL res=0;
  REP(i,N) res+=k^A[i];
  return res;
}
void test() {
  N=(int)genRandNum(0,(LL)1e3);
  vector<LL> S=genRandSeq(N,0,(LL)1e3);
  REP(i,N)A[i]=S[i];
  K=genRandNum(0,(LL)1e3);
  LL res=-Inf;
  REPE(k,K) SMAX(res,f(k));
  
  LL act=solve();
  if(res!=act) {
    dump(res,act,K);
    dumpc(S);
  }
  assert(res==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
