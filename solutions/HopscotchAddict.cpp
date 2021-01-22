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

// $ cp-batch HopscotchAddict | diff HopscotchAddict.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address HopscotchAddict.cpp && ./a.out

/*

 6/29/2019

 5:45-6:02 AC

 https://img.atcoder.jp/abc132/editorial.pdf
 https://kenkoooo.hatenablog.com/entry/2019/06/29/224711
 http://kmjp.hatenablog.jp/entry/2019/06/29/1030

 7/10/2020

 9:38-9:52 solve again

 1/11/2021

 10:50-11:01 solve again

 */

const int MAX_N=1e5+1;
VI G[MAX_N];
int N,M,S,T;

void solve() {
  const int Inf=1e8;
  VV<int> D(N,VI(3,Inf));
  REP(i,N)REP(j,3)D[i][j]=Inf;
  queue<II> Q;
  Q.emplace(S,0),D[S][0]=0;
  while(SZ(Q)) {
    auto [u,p]=Q.front(); Q.pop();
    int d=D[u][p];
    FORR(v,G[u]) {
      int pp=(p+1)%3;
      if(D[v][pp]>d+1) {
        D[v][pp]=d+1,Q.emplace(v,pp);
        //dump(v,pp,D[v][pp]);
      }
    }
  }

  int res=D[T][0];
  if(res==Inf) res=-1;
  else res/=3;
  cout<<res<<endl;
}

void solve_v2() {
  const int Inf=1e7;
  VV<int> D(N,VI(3,Inf));
  queue<II> Q;
  Q.emplace(S,0),D[S][0]=0;
  while(SZ(Q)) {
    int u,step; tie(u,step)=Q.front(),Q.pop();
    int ss=(step+1)%3;
    FORR(v,G[u]) {
      int dd=D[u][step]+1;
      if(dd<D[v][ss]) {
        Q.emplace(v,ss);
        D[v][ss]=dd;
      }
    }
  }

  if(D[T][0]!=Inf) assert(D[T][0]%3==0);
  int res=D[T][0]/3;
  if(res==Inf/3) res=-1;
  cout<<res<<endl;
}

const LL Inf=1e10;
LL D[MAX_N][3];
void solve_org() {
  REP(i,N)REP(j,3)D[i][j]=Inf;
  queue<tuple<long long,int,int>> Q; Q.emplace(0,S,0); D[S][0]=0;
  while(Q.size()>0) {
    auto tu=Q.front(); Q.pop();
    int u,step; long long d;
    tie(d,u,step)=tu;
    for(auto v : G[u]) {
      int step2=(step+1)%3;
      if(d+1<D[v][step2]) {
        D[v][step2]=d+1;
//        dump(v,step2,d+1);
        Q.emplace(d+1,v,step2);
      }
    }
  }
  LL res;
//  dump(D[T][0]);
  if(D[T][0]>=Inf) res=-1;
  else if(D[T][0]%3==0) res=D[T][0]/3;
  else res=Inf;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
  }
  cin>>S>>T;
  --S,--T;
  solve();

  return 0;
}
