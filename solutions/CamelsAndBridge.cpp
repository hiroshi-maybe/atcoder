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

// $ cp-batch CamelsAndBridge | diff CamelsAndBridge.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CamelsAndBridge.cpp && ./a.out

/*

 10/11/2020

 6:59-7:33 give up
 16:45-18:00 read editorials

 10/12/2020

 21:25-24:35 confused why max distance works

 10/13/2020

 8:05-10:25 got AC

 https://twitter.com/hanseilimak/status/1316035092117032960
 https://atcoder.jp/contests/arc105/editorial/170
 https://youtu.be/dhhldocM--0?t=687
 https://kmjp.hatenablog.jp/entry/2020/10/12/0900
 https://jupiro.hatenablog.com/entry/2020/10/12/002352

 https://en.wikipedia.org/wiki/Longest_path_problem
 https://qiita.com/tanabe13f/items/6c723c29a121de760790

 https://twitter.com/kyopro_friends/status/1315312900672684032
 https://twitter.com/laycrs/status/1315312633805905920
 https://twitter.com/ngtkana/status/1315312295736561665
 https://twitter.com/camypaper/status/1315315168230866944
 https://twitter.com/ajis_ka/status/1315310047799373827

 */

const int MAX_N=1e6+1;
int W[MAX_N], L[MAX_N], V[MAX_N];
int N,M;

const int Inf=1e9;
void solve() {
  int minv=*min_element(V,V+M), maxw=*max_element(W,W+N);
  if(maxw>minv) {
    cout<<-1<<endl;
    return;
  }

  map<int,int> A; REP(i,M) SMAX(A[V[i]],L[i]);
  vector<II> B;
  int maxv=0;
  FORR(kvp,A) {
    B.emplace_back(kvp.first,maxv);
    SMAX(maxv, kvp.second);
  }
  B.emplace_back(Inf,maxv);
  //dumpC(W,W+N);
  //dumpc(B);

  auto f=[&](int w) -> LL {
    auto it=lower_bound(ALL(B),make_pair(w,0));
    return it->second;
  };

  LL res=Inf;
  VI P(N); iota(ALL(P),0);
  do {
    vector<LL> dp(N,0);
    vector<LL> ws(N); REP(i,N) ws[i]=W[P[i]];
    REP(i,N) {
      int w=ws[i];
      for(int j=i-1; j>=0; --j) {
        w+=ws[j];
        int x=f(w);
        SMAX(dp[i],dp[j]+x);
      }
    }
    SMIN(res,dp[N-1]);
  } while(next_permutation(ALL(P)));

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>W[i];
  REP(i,M) cin>>L[i]>>V[i];
  solve();

  return 0;
}
