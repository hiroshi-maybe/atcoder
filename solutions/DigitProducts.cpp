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
template<class T> using VVV=vector<vector<vector<T>>>;
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

// $ cp-batch DigitProducts | diff DigitProducts.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DigitProducts.cpp && ./a.out

/*

 7/4/2021

 21:31-23:40 give up

 7/5/2021

 6:45-6:52 AC

 https://atcoder.jp/contests/abc208/editorial/2189
 https://youtu.be/FhQVDtJyM6o?t=4483

 https://twitter.com/kyopro_friends/status/1411685013091799048
 https://twitter.com/laycrs/status/1411681450747858944
 https://twitter.com/kiri8128/status/1411681961119080458
 https://twitter.com/tomerun/status/1411681836678336516
 https://twitter.com/maspy_stars/status/1411682362996322312
 https://twitter.com/ei1333/status/1411681264285884417

 */

const int MAX_K=1e6;
LL N,K;

LL dp[21][MAX_K][2][2];
void solve() {
  vector<LL> ps={2,3,5,7};
  VV<LL> exps(4);
  REP(i,4) {
    LL cur=1;
    while(cur<=K) {
      exps[i].push_back(cur);
      cur*=ps[i];
    }
  }

  //REP(i,4) dumpc(exps[i]);
  set<LL> kss{0};
  REP(cnt2,SZ(exps[0]))REP(cnt3,SZ(exps[1]))REP(cnt5,SZ(exps[2]))REP(cnt7,SZ(exps[3])) {
    LL k=exps[0][cnt2]*exps[1][cnt3];
    if(k>K) continue;
    k*=exps[2][cnt5];
    if(k>K) continue;
    k*=exps[3][cnt7];
    if(k>K) continue;
    if(0<=k&&k<=K) kss.emplace(k);
  }

  vector<LL> ks(ALL(kss));
  const LL inf = K+1;
  ks.push_back(inf);
  //dumpc(ks);
  //dump(SZ(ks));
  map<LL,int> id;
  REP(i,SZ(ks)) id[ks[i]]=i;
  dp[0][1][0][1]=1;
  string S=to_string(N);
  int L=SZ(S);
  REP(i,L) {
    REP(j,SZ(ks)) REP(less,2) REP(init,2) {
      LL k=ks[j];
      int curd=S[i]-'0';
      int lb=init?1:0,hb=less?9:curd;
      FORE(d,lb,hb) {
        LL kk=min(inf,k*d);
        assert(id.count(kk));
        int jj=id[kk];
        dp[i+1][jj][less|(d<curd)][0]+=dp[i][j][less][init];
        //dump(i,j,less,d,k,k*d,dp[i][j][less],dp[i+1][jj][less|(d<curd)]);
      }
    }
    dp[i+1][1][1][1]=1;
  }

  LL res=0;
  REP(j,SZ(ks)-1) REP(less,2) {
    //dump(j,ks[j],less,dp[L][j][less][0]);
    res+=dp[L][j][less][0];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  solve();

  return 0;
}
