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

// $ cp-batch FlipDigits | diff FlipDigits.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FlipDigits.cpp && ./a.out

/*

 11/15/2020

 7:17-7:30, 8:40-8:55 WA
 10:00 WA
 11:00 AC after fixing overflow bug

 https://atcoder.jp/contests/agc049/editorial/330
 https://twitter.com/hanseilimak/status/1327887553379274752
 https://drken1215.hatenablog.com/entry/2020/11/15/051800

 */

string S,T;
int N;

void nope() {
  cout<<-1<<endl;
  exit(0);
}
void solve() {
  VI ss,ts;
  REP(i,N) {
    if(S[i]=='1') ss.push_back(i);
    if(T[i]=='1') ts.push_back(i);
  }

  //dumpc(ss);
  //dumpc(ts);

  if(SZ(ts)>SZ(ss)) nope();

  LL res=0;

  int i=0;
  FORR(ti,ts) {
    if(i==SZ(ss)) nope();
    //dump(i,ss[i],ti,res);
    while(ss[i]<ti) {
      if(i+1>=SZ(ss)) nope();
      res+=ss[i+1]-ss[i],i+=2;
    }
    if(i==SZ(ss)) nope();
    assert(ss[i]>=ti);
    res+=ss[i]-ti,i+=1;
  }
  if((SZ(ss)-i)%2) nope();
  while(i<SZ(ss)) {
    res+=ss[i+1]-ss[i],i+=2;
  }

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>S>>T;
  solve();

  return 0;
}
