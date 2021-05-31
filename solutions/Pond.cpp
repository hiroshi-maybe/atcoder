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
template <typename Val>
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<Val>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<Val>>(R+1,vector<Val>(C+1,0));

    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  Val query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<Val>> cum;
};
// $ cp-batch Pond | diff Pond.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Pond.cpp && ./a.out

/*

 5/30/2021

 5:19-6:23 TLE
 6:33 give up

 22:45-23:32 read tweets and got AC
 23:45 read editorials

 https://atcoder.jp/contests/abc203/editorial/1955
 https://youtu.be/FA9Z9DowNlQ?t=1853

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.6ezzckpuakz8
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.x8lzngp93dey

 https://twitter.com/laycrs/status/1398997675001843714
 https://twitter.com/kyopro_friends/status/1398998312578023424
 https://twitter.com/tsutaj/status/1398998892092432388
 https://twitter.com/kiri8128/status/1398998650794086403
 https://twitter.com/tanakh/status/1399000304541061124

 */

const int MAX_N=1e3+1;
int A[MAX_N][MAX_N];
int N,K;

bool ok(int m) {
  VV<int> as(N,VI(N,0));
  REP(i,N)REP(j,N) as[i][j]=A[i][j]>=m;
  TwoDimCumSum<int> cum(as);
  REPE(i,N-K)REPE(j,N-K) {
    int cnt=cum.query(i,j,i+K,j+K);
    if(cnt<K*K/2+1) return false;
  }
  return true;
}
void solve() {
  int good=0,bad=1e9+1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool res=ok(m);
    //dump(m,res);
    (res?good:bad)=m;
  }
  cout<<good<<endl;
}

void solve_tle() {
  int res=1e9;
  set<II> S0,S1;
  auto add=[&](II a) {
    if(SZ(S1)==0) {
      S1.emplace(a);
      return;
    }

    if(S1.begin()->first>a.first) S0.emplace(a);
    else S1.emplace(a);
    while(SZ(S1)-SZ(S0)>1) {
      auto x=*S1.begin();
      S1.erase(x);
      S0.emplace(x);
    }
    while(SZ(S0)-SZ(S1)>1) {
      auto x=*S0.rbegin();
      S0.erase(x);
      S1.emplace(x);
    }
  };

  auto rem=[&](II a) {
    if(S0.count(a)) S0.erase(a);
    else S1.erase(a);
  };

  auto med=[&]() -> II {
    if(SZ(S0)>=SZ(S1)) return *S0.rbegin();
    else return *S1.begin();
  };

  REP(i,K)REP(j,K) add({A[i][j],i*N+j});
  REP(step,(N-K+1)*(N-K+1)-1) {
    SMIN(res,med().first);
    int r=step/(N-K+1),c=step%(N-K+1);
    /*
    dump(r,c,med().first);
    dumpc(S0);
    dumpc(S1);*/
    if(c==N-K) {
      // to down
      bool isr=(r%2)==0;
      int jst=isr?N-K:0;
      REP(o,K) {
        int i=r,j=jst+o;
        rem({A[i][j],i*N+j});
        add({A[i+K][j],(i+K)*N+j});
      }
    } else {
      // to left or right
      bool tor=(r%2)==0;
      int j0=tor?c:(N-c-1);
      int j1=tor?(c+K):(N-c-1-K);
      FOR(i,r,r+K) {
        rem({A[i][j0],i*N+j0});
        add({A[i][j1],i*N+j1});
      }
    }
  }
  SMIN(res,med().first);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  REP(i,N)REP(j,N) cin>>A[i][j];
  solve();

  return 0;
}
