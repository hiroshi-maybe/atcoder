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

// $ cp-batch Poker | diff Poker.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Poker.cpp && ./a.out

/*

 2/27/2021

 4:37-5:18 AC

 https://atcoder.jp/contests/abc193/editorial/810

 */

string S,T;
int K;

LL p10[18];
LL f(VI x) {
  VI cnt(10,0);
  REP(i,5) cnt[x[i]]++;
  LL res=0;
  FORE(i,1,9) res+=p10[cnt[i]]*i;
  return res;
}

VI cnt(VI xs, VI ys) {
  VI cnt(10,0);
  REP(i,5) cnt[xs[i]]++,cnt[ys[i]]++;
  return cnt;
}

VI cards(string s, int a) {
  VI res(5,a);
  REP(i,4) res[i]=s[i]-'0';
  return res;
}
void solve() {
  p10[0]=1;
  REP(i,10) p10[i+1]=p10[i]*10;
  LL res=0;
  FORE(a,1,9) FORE(b,1,9) {
    VI xs=cards(S,a),ys=cards(T,b);
    VI ns=cnt(xs,ys);
    //dumpc(ns);
    //dump(a,b,K);
    bool ok=true;
    FORE(i,1,9) if(ns[i]>K) ok=false;
    if(!ok) continue;
    ns[a]--,ns[b]--;
    //dump(a,ns[a]);
    LL x=((LL)K-ns[a]);
    ns[a]++;
    //dump(b,ns[b]);
    LL y=(LL)K-ns[b];
    assert(x>=0);
    assert(y>=0);
    if(f(xs)>f(ys)) res+=x*y;
  }
  double ans=(double)res/(9.0*K-8)/(9.0*K-9);
  cout<<ans<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>K>>S>>T;
  solve();

  return 0;
}
