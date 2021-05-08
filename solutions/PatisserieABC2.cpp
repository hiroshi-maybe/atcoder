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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch PatisserieABC2 | diff PatisserieABC2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PatisserieABC2.cpp && ./a.out

/*

 5/8/2021

 5:43-6:40 give up

 9:40-10:10 AC

 https://atcoder.jp/contests/abc200/editorial/1247

 https://twitter.com/kiri8128/status/1391027430492569602
 https://twitter.com/ei1333/status/1391025354693767169
 https://twitter.com/tanakh/status/1391028020886925319
 https://twitter.com/kzyKT_M/status/1391025189618479104
 https://twitter.com/laycrs/status/1391025209222651905

 */

const int MAX_N=1e6+1;
int N;
LL K;

LL dp[MAX_N*3];
void solve() {
  FORE(i,1,N) dp[i]=1;
  REP(_,2) {
    vector<LL> cum(N*3+10);
    REPE(i,N*3) cum[i+1]=cum[i]+dp[i];
    ZERO(dp);
    REPE(i,N*3) dp[i]=cum[i]-cum[max(0,i-N)];
  }
  //dumpC(dp,dp+N*3+1);

  LL k=K;
  FORE(X,3,3*N) {
    LL x=X;
    LL cnt=dp[X];
    if(cnt>=k) {
      dump(x,k);
      FORE(I,1,N) {
        LL i=I;
        LL minj=max(1LL,x-i-N),maxj=min((LL)N,x-i-1);
        if(maxj<minj) continue;
        LL cnt=maxj-minj+1;
        dump(x,i,k,cnt);
        assert(cnt>=1);
        if(cnt>=k) {
          LL j=minj+k-1;
          assert(j<=maxj);
          LL kk=x-i-j;
          //dump(x,k,i,minj,maxj,j,kk);
          assert(1<=kk&&kk<=N);
          cout<<i<<" "<<j<<" "<<kk<<endl;
          return;
        }
        k-=cnt;
        assert(k>=0);
      }
    }
    k-=cnt;
    assert(k>=0);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  solve();

  return 0;
}
