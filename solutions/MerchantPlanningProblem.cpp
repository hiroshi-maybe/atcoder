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

// $ cp-batch MerchantPlanningProblem | diff MerchantPlanningProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MerchantPlanningProblem.cpp && ./a.out

/*

 6/6/2020

 25:20-25:45 AC

 */

const int MAX_N=1e6+1;
int N,M,K;

map<int,int> ids;
int T[16];
LL mx[16][16];
VI G[MAX_N];

const LL Inf=1e18;
LL D[MAX_N];
void bfs(int s, int id) {
  REP(i,N) D[i]=Inf;
  queue<int> Q;
  Q.emplace(s),D[s]=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    FORR(v,G[u]) {
      if(D[v]>D[u]+1) D[v]=D[u]+1,Q.emplace(v);
    }
  }
  if(id>=0) REP(i,K) mx[id][i]=D[T[i]];
}

bool ith(int mask, int i) { return (mask>>i)&1; }

LL memo[16][1<<16];
LL f(int cur, int mask) {
  LL &res=memo[cur][mask];
  if(res>=0) return res;
  if(__builtin_popcount(mask)==K) {
    return res=0;
  }
  res=Inf;
  REP(i,K) if(!ith(mask,i)) {
    SMIN(res,mx[cur][i]+f(i,mask|(1<<i)));
  }
  //dump(cur,mask,res);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  int s; cin>>s; --s;
  cin>>K;
  REP(i,K) {
    cin>>T[i];
    T[i]--;
    ids[T[i]]=i;
  }

  REP(i,K) bfs(T[i],i);
  bfs(s,-1);
  LL res=Inf;
  //dump(mx[0][1],mx[1][0]);
  REP(i,K) {
    MINUS(memo);
    //dump(i,T[i],D[T[i]]);
    SMIN(res,D[T[i]]+f(i,1<<i));
  }
  cout<<res<<endl;

  return 0;
}
