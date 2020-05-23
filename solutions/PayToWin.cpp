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
std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}
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

// $ cp-batch PayToWin | diff PayToWin.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PayToWin.cpp && ./a.out

/*

 5/23/2020

 5:00-5:40,6:45-7:00,7:20-7:30 give up

 13:30-16:00 read tweets, prove by myself and got AC

 https://twitter.com/hanseilimak/status/1264296651235065856
 https://img.atcoder.jp/agc044/editorial.pdf

 https://betrue12.hateblo.jp/entry/2020/05/24/021818
 https://twitter.com/tempura_cpp/status/1264201997563002881
 https://twitter.com/maspy_stars/status/1264202814332387330
 https://twitter.com/kenkoooo/status/1264202984826605570
 https://twitter.com/sotasingularity/status/1264202802139557888
 https://twitter.com/satanic0258/status/1264203708222455810
 https://twitter.com/chokudai/status/1264204048720265218
 https://twitter.com/small_onions/status/1264204132610539520
 https://twitter.com/ngtkana/status/1264204467945091076
 https://twitter.com/maspy_stars/status/1264204712229744640
 https://twitter.com/nico_shindannin/status/1264207521264197632
 https://twitter.com/wkbme/status/1264240782967312384

 */

LL N,A,B,C,D;

const LL Inf=(LL)1e18+1;
LL res=Inf;
LL X[3],Y[3];

map<LL,LL> memo;
LL f(LL n) {
  if(memo.count(n)) return memo[n];
  LL &res=memo[n];
  res=Inf;
  if(n<Inf/D) res=D*n;
  REP(i,3) {
    LL y=Y[i],c=X[i];
    vector<LL> ts={(n+y-1)/y, n/y};
    //dump(n,y,ts[0],ts[1]);
    FORR(t,ts) {
      SMIN(res,abs(n-t*y)*D+c+f(t));
    }
  }
  //dump(n,res);
  return res;
}

LL solve() {
  X[0]=C,X[1]=B,X[2]=A;
  Y[0]=5,Y[1]=3,Y[2]=2;
  memo.clear();
  LL res=f(N);
  //dump(N,SZ(memo),res);
  return res;
}

void dfs(__int128_t cur, __int128_t coin, int i) {
  dump(cur,coin,i);
  if(cur>=N||i>=3) {
    __int128_t a=coin+D*max(N-cur,cur-N);
    if(a>=Inf) return;
    SMIN(res,(LL)a);
    return;
  }
  dfs(cur,coin,i+1);
  while(cur<N) {
    cur*=Y[i],coin+=X[i];
    dfs(cur,coin,i+1);
  }
}

LL solve_wrong() {
  X[0]=C,X[1]=B,X[2]=A;
  Y[0]=5,Y[1]=3,Y[2]=2;
  dfs(1,D,0);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    res=Inf;
    cin>>N>>A>>B>>C>>D;
    cout<<solve()<<endl;
  }

  return 0;
}
