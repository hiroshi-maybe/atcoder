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

// $ cp-batch PickingUp | diff PickingUp.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PickingUp.cpp && ./a.out

/*
 
 6/15/2019
 
 5:03-5:15 AC
 
 https://img.atcoder.jp/diverta2019-2/editorial.pdf
 
 Editorial is showing more efficient way.
     (p,q) is determined
 <=> optimal sequence of points of 0 cost is uniquely determined. res=N-cnt(diff {p,q} for all pairs)
 
 */

const int MAX_N=100+1;
LL X[MAX_N],Y[MAX_N];
int N;

void solve() {
  map<II,int> cnt;
  REP(i,N)REP(j,N)if(i!=j) cnt[{X[j]-X[i],Y[j]-Y[i]}]++;
  int maxp=0;
  FORR(kvp, cnt) SMAX(maxp, kvp.second);
  cout<<N-maxp<<endl;
}

void solve_org() {
  vector<pair<LL,LL>> A;
  REP(i,N)A.emplace_back(X[i],Y[i]);
  //sort(ALL(A));
  set<pair<LL,LL>> S(ALL(A));
  LL res=N;
  REP(i,N)REP(j,N)if(i!=j) {
    LL dx=A[i].first-A[j].first,dy=A[i].second-A[j].second;
    LL sum=N;
    REP(k,N) {
      pair<LL,LL> cur={A[k].first,A[k].second};
      if(S.count({cur.first+dx,cur.second+dy}))--sum;
    }
     SMIN(res,sum);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i];
  solve();
  
  return 0;
}
