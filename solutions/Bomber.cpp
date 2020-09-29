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

// $ cp-batch Bomber | diff Bomber.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Bomber.cpp && ./a.out

/*

 9/28/2020

 22:47-23:13 AC

 https://atcoder.jp/contests/abc176/editorial/66
 https://kmjp.hatenablog.jp/entry/2020/08/23/0900

 */

const int MAX_N=1e6+1;
II A[MAX_N];
int H,W,M;

void solve() {
  VI wcnts(W,0);
  set<II> S;
  map<int,VI> hs;
  REP(i,M) {
    hs[A[i].first].push_back(A[i].second);
    wcnts[A[i].second]++;
  }
  REP(i,W)if(wcnts[i]>0) S.emplace(wcnts[i],i);
  //dumpc(S);
  int res=0;
  FORR(kvp,hs) {
    int ans=SZ(kvp.second);
    FORR(w,kvp.second) {
      int cnt=wcnts[w];
      auto it=S.find({cnt,w});
      S.erase(it);
      --wcnts[w],S.emplace(wcnts[w],w);
    }
    //dump(kvp.first,ans,S.begin()->first);
    SMAX(res,ans+S.rbegin()->first);
    FORR(w,kvp.second) {
      int cnt=wcnts[w];
      auto it=S.find({cnt,w});
      S.erase(it);
      ++wcnts[w],S.emplace(wcnts[w],w);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>H>>W>>M;
  REP(i,M) {
    int h,w; cin>>h>>w;
    --h,--w;
    A[i]={h,w};
  }
  solve();

  return 0;
}
