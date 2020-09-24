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

// $ cp-batch WizardInMaze | diff WizardInMaze.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WizardInMaze.cpp && ./a.out

/*

 9/23/2020

 21:47-22:05 AC

 https://atcoder.jp/contests/abc176/editorial/65

 */

const int MAX_N=1e3+1;
int si,sj,di,dj;
int N,M;
string S[MAX_N];

void solve() {
  VV<int> viz(N,VI(M,-1));
  int g=0;

  vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
  auto dfs=[&](auto &&self, int i, int j) {
    if(viz[i][j]!=-1) return;
    viz[i][j]=g;
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(S[ii][jj]=='#') continue;
      self(self,ii,jj);
    }
  };
  REP(i,N)REP(j,M) if(viz[i][j]==-1&&S[i][j]!='#') {
    dfs(dfs, i, j);
    g++;
  }

  vector<set<int>> G(g);
  REP(i,N)REP(j,M) if(S[i][j]!='#') {
    FORE(di,-2,2) FORE(dj,-2,2) {
      int ii=i+di,jj=j+dj;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(S[ii][jj]=='#') continue;
      if(viz[ii][jj]!=viz[i][j]) {
        int u=viz[i][j],v=viz[ii][jj];
        if(G[u].count(v)==0) {
          G[u].emplace(v),G[v].emplace(u);
        }
      }
    }
  }

  int s=viz[si][sj],d=viz[di][dj];
  const int Inf=1e8;
  VI D(g,Inf);
  queue<int> Q;
  Q.emplace(s),D[s]=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    FORR(v,G[u]) {
      if(D[v]>D[u]+1) {
        D[v]=D[u]+1;
        Q.emplace(v);
      }
    }
  }

  int res=D[d];
  if(res==Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>si>>sj>>di>>dj;
  --si,--sj,--di,--dj;
  REP(i,N) cin>>S[i];
  solve();

  return 0;
}
