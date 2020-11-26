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

// $ cp-batch ThirdAvenue | diff ThirdAvenue.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThirdAvenue.cpp && ./a.out

/*

 11/22/2020

 21:42-21:55 TLE
 21:59 AC

 https://atcoder.jp/contests/abc184/editorial/352
 https://kmjp.hatenablog.jp/entry/2020/11/22/1000

 https://twitter.com/torus711/status/1330508333497810945
 https://twitter.com/ei1333/status/1330507005535117312
 https://twitter.com/ngtkana/status/1330506565900791808
 https://twitter.com/satanic0258/status/1330506496942096384
 https://twitter.com/kzyKT_M/status/1330506434384187399
 https://twitter.com/kyopro_friends/status/1330510019423391744

 */

const int MAX_N=2000+1;
string A[MAX_N];
int N,M;

const int Inf=1e8;
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
void solve() {
  VV<int> D(N,VI(M,Inf));
  VV<II> mv(26);
  VI viz(26);
  II s,g;
  REP(i,N)REP(j,M) {
    if(islower(A[i][j])) {
      int c=A[i][j]-'a';
      mv[c].emplace_back(i,j);
    }
    if(A[i][j]=='S') s={i,j};
    if(A[i][j]=='G') g={i,j};
  }

  queue<II> Q;
  Q.emplace(s),D[s.first][s.second]=0;
  while(SZ(Q)) {
    int i,j; tie(i,j)=Q.front(); Q.pop();
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='#') continue;
      if(D[ii][jj]>D[i][j]+1) {
        D[ii][jj]=D[i][j]+1;
        Q.emplace(ii,jj);
      }
    }
    if(islower(A[i][j])) {
      int c=A[i][j]-'a';
      if(!viz[c]) {
        FORR(p,mv[c]) {
          int ii=p.first,jj=p.second;
          if(D[ii][jj]>D[i][j]+1) {
            D[ii][jj]=D[i][j]+1;
            Q.emplace(ii,jj);
          }
        }
      }
      viz[c]=1;
    }
  }

  int res=D[g.first][g.second];
  if(res==Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
