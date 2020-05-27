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

// $ cp-batch KabeNuke | diff KabeNuke.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KabeNuke.cpp && ./a.out

/*

 5/27/2020

 8:39-9:10 AC

 https://www.slideshare.net/chokudai/abc020

 */

const int MAX_N=10+1;
string S[MAX_N];
int H,W,T;

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int D[MAX_N][MAX_N][MAX_N*MAX_N];
void solve() {
  queue<III> Q;
  II s,e;
  REP(i,H)REP(j,W) {
    if(S[i][j]=='S') s={i,j};
    if(S[i][j]=='G') e={i,j};
  }
  const int Inf=1e5;
  REP(i,H)REP(j,W)REP(k,H*W)D[i][j][k]=Inf;
  Q.emplace(s.first,s.second,0),D[s.first][s.second][0]=0;
  while(SZ(Q)) {
    int i,j,b; tie(i,j,b)=Q.front(),Q.pop();
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=H||jj<0||jj>=W) continue;
      int bb=b+(S[ii][jj]=='#');
      if(D[ii][jj][bb]>D[i][j][b]+1) {
        D[ii][jj][bb]=D[i][j][b]+1;
        Q.emplace(ii,jj,bb);
      }
    }
  }
  LL res=0;
  REP(b,H*W) if(D[e.first][e.second][b]<Inf) {
    LL w=D[e.first][e.second][b]-b;
    LL good=0,bad=2e9;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      ((w+mid*b<=T)?good:bad)=mid;
    }
    SMAX(res,good);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>H>>W>>T;
  REP(i,H) cin>>S[i];
  solve();

  return 0;
}
