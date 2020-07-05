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

// $ cp-batch League | diff League.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address League.cpp && ./a.out

/*

 9/1/2019

 5:26-5:57 AC

 https://img.atcoder.jp/abc139/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/09/01/1000

 7/4/2020

 17:58-18:20 solve again

 */

const int MAX_N=1e3+1;
int A[MAX_N][MAX_N];
int N;

void solve() {
  VI ps(N,0);
  int res=0;
  while(count(ALL(ps),N-1)<N) {
    VI X(N,-1);
    REP(i,N) if(ps[i]<N-1) X[i]=A[i][ps[i]];
    VI is;
    REP(i,N) if(X[i]!=-1&&i==X[X[i]]) {
      is.push_back(i);
    }
    assert(SZ(is)%2==0);
    if(is.empty()) {
      cout<<-1<<endl;
      return;
    }
    FORR(i,is) ps[i]++;
    ++res;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N)REP(j,N-1) cin>>A[i][j],A[i][j]--;
  solve();

  return 0;
}

map<II,int> ids;
VI G[MAX_N*MAX_N];
void solve_org() {
  REP(i,N) REP(j,N-2) {
    int a=A[i][j],b=A[i][j+1];
    G[a].push_back(b);
  }
  int M=SZ(ids);
  vector<int> D(M,0);
  for(int u=0; u<M; ++u) for(auto v : G[u]) D[v]++;
//  dumpc(D);
  vector<int> seq;
  queue<II> Q;
  for(int u=0; u<M; ++u) if(D[u]==0) Q.emplace(u,1);
  int res=0;
  while(Q.size()) {
    int u,len; tie(u,len)=Q.front(); Q.pop();
    seq.push_back(u);
    SMAX(res,len);
    for(auto v : G[u]) {
      D[v]--;
      if(D[v]==0) Q.emplace(v,len+1);
    }
  }
//  dumpc(seq);
//  dump(SZ(seq));
  if(SZ(seq)<M) res=-1;
  cout<<res<<endl;
}

int main_org() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;

  int id=0;
  REP(i,N)FOR(j,i+1,N) ids[{i,j}]=id++;
  REP(i,N)REP(j,N-1) {
    int x=i;
    int y; cin>>y;
    --y;
    if(x>y) swap(x,y);
    A[i][j]=ids[{x,y}];
  }
  solve();

  return 0;
}
