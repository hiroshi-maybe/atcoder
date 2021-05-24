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
template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};

// compute inversions
vector<int> inversions(vector<int> ns) {
  int maxv=*max_element(ns.begin(),ns.end());
  BIT<int> bit(maxv+1);
  int N=ns.size();
  vector<int> res(N);
  for(int i=N-1; i>=0; --i) {
    // Count elements which stays in right side and smaller
    res[i]=bit.query(0,ns[i]);
    bit.add(ns[i],1);
  }
  return res;
}
// $ cp-batch Swaps2 | diff Swaps2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Swaps2.cpp && ./a.out

/*

 5/23/2021

 10:19-11:49 give up

 12:00-12:10, 18:40-19:20 read editorial and got AC

 https://atcoder.jp/contests/arc120/editorial/1921
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.a6usn1s0j58h

 https://twitter.com/prd_xxx/status/1396453312162004998
 https://twitter.com/ngtkana/status/1396451730997448705
 https://twitter.com/0214sh7/status/1396451042611499010
 https://twitter.com/SSRS_cp/status/1396451108462030848

 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N];
int N;

void solve() {
  VI as(A,A+N),bs(B,B+N);
  REP(i,N) as[i]+=i,bs[i]+=i;

  //dumpc(as);
  //dumpc(bs);

  map<int,VI> ps;
  REP(i,N) ps[as[i]].push_back(i);
  FORR(kvp, ps) reverse(ALL(kvp.second));

  VI xs(N,-1);
  REP(i,N) {
    int b=bs[i];
    if(SZ(ps[b])==0) {
      cout<<-1<<endl;
      return;
    }

    xs[ps[b].back()]=i;
    ps[b].pop_back();
  }

  auto invs=inversions(xs);
  LL res=accumulate(ALL(invs),0LL);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  solve();

  return 0;
}
