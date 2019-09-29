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

// $ cp-batch PowerfulDiscountTickets | diff PowerfulDiscountTickets.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PowerfulDiscountTickets.cpp && ./a.out

/*
 
 9/15/2019
 
 5:11-5:33, 5:49-6:09 give up
 
 9/29/2019
 
 21:25-22:15 read editorials and got AC
 
 https://img.atcoder.jp/abc141/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/09/16/032000
 https://twitter.com/satanic0258/status/1173230218191896576
 https://twitter.com/ngtkana/status/1173230639283224576?s=20
 https://twitter.com/drken1215/status/1173230175649071104?s=20
 https://twitter.com/tempura_cpp/status/1173230007402975232?s=20
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,M;

void solve() {
  priority_queue<LL> Q;
  REP(i,N) Q.emplace(A[i]);
  while(M--) {
    LL a=Q.top(); Q.pop();
    Q.emplace(a/2);
  }
  LL res=0;
  while (SZ(Q)) res+=Q.top(),Q.pop();
  cout<<res<<endl;
}

/*
bool ok(LL cap) {
  int m=0;
  REP(i,N) {
    LL a=A[i];
    while(a)
  }
}

void solve() {
  sort(A,A+N),reverse(A,A+N);
  LL good=1e16,bad=0;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool res=ok(mid);
    (res?good:bad)=mid;
  }
  cout<<good<<endl;
}*/

LL res=1e16;
void dfs(int i, int m, int cnt, LL cur) {
  if(i==N) {
    SMIN(res,cur);
    return;
  }
  if(M-cnt<m) return;
  FOR(n,cnt,32) if(m+n<=M) {
    LL cost=A[i]/(1LL<<n);
    dfs(i+1,m+n,n,cur+cost);
  }
}
void solve_wrong() {
  sort(A,A+N);
  dfs(0,0,0,0);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
