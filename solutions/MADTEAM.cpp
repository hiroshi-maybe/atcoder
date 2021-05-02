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

// $ cp-batch MADTEAM | diff MADTEAM.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MADTEAM.cpp && ./a.out

/*

 5/1/2021

 5:43-6:09 WA
 6:40 give up

 5/2/2021

 11:20-12:30 read editorial and got AC

 https://youtu.be/3ymJpfD1sPE?t=2402
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.12kgidm2iod7

 https://twitter.com/kyopro_friends/status/1388488669145624576
 https://twitter.com/kzyKT_M/status/1388488471522594818
 https://twitter.com/laycrs/status/1388488460068028417
 https://twitter.com/tomerun/status/1388488549389930498
 https://twitter.com/camypaper/status/1388489616596951041
 https://twitter.com/tanakh/status/1388489827805323273
 https://twitter.com/kiri8128/status/1388489133429903365
 https://twitter.com/ngtkana/status/1388490711754952708
 https://twitter.com/kuuso1/status/1388490521534889987

 */

const int MAX_N=3000+1;
LL A[MAX_N][5];
int N;

const LL Inf=1e9+100;

bool ok(LL mid) {
  set<int> S;
  REP(i,N) {
    int mask=0;
    REP(j,5) if(A[i][j]>=mid) mask|=(1<<j);
    S.emplace(mask);
  }
  VI ss(ALL(S));
  REP(_,2) ss.push_back(0);
  int fmask=(1<<5)-1;
  REP(k,SZ(ss))REP(j,k)REP(i,j) {
    int mask=(ss[k]|ss[j]|ss[i]);
    if(mask==fmask) return true;
  }
  return false;
}
void solve() {
  LL good=0,bad=Inf;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool res=ok(mid);
    //dump(mid,res);
    (res?good:bad)=mid;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(j,N)REP(i,5) cin>>A[j][i];
  solve();

  return 0;
}
