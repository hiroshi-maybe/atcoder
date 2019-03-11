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

// $ cp-batch LazyFaith | diff LazyFaith.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LazyFaith.cpp && ./a.out

/*
 
 3/11/2019
 
 14:54-15:14 AC
 
 https://img.atcoder.jp/abc119/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/02/24/230900
 
 */

const int MAX_N=1e6+1;
LL P[2][MAX_N];
int N[2];

void solve(LL x) {
  vector<LL> ps[2];
  REP(c,2) {
    int i=lower_bound(P[c],P[c]+N[c],x)-P[c];
    ps[c].push_back(P[c][i]);
    if(i>0) ps[c].push_back(P[c][i-1]);
  }
  LL res=1e17;
  REP(o,2) {
    REP(mask,4) {
      LL cost=0;
      LL p=x;
      REP(i,2) {
        int j=(mask>>i)&1;
        LL pp=ps[i][min(j,SZ(ps[i])-1)];
        cost+=abs(pp-p),p=pp;
      }
      SMIN(res,cost);
    }
    swap(ps[0],ps[1]);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int Q;
  cin>>N[0]>>N[1]>>Q;
  REP(c,2)REP(i,N[c]) cin>>P[c][i];
  REP(c,2)P[c][N[c]++]=1e16;
  REP(_,Q) {
    LL x; cin>>x;
    solve(x);
  }
  
  return 0;
}
