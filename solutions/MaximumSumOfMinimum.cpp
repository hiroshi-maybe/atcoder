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

// $ cp-batch MaximumSumOfMinimum | diff MaximumSumOfMinimum.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumSumOfMinimum.cpp && ./a.out

/*
 
 6/1/2019
 
 5:28-5:40 WA
 6:07 RE
 6:31 WA
 6:54 AC
 
 https://img.atcoder.jp/m-solutions2019/editorial.pdf
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
VI G[MAX_N];
int N;
II D[MAX_N];
vector<LL> res;

LL dfs(int u, int pre) {
  LL ans=0;
  FORR(v,G[u])if(v!=pre) {
    ans+=min(res[u],res[v])+dfs(v,u);
  }
  return ans;
}

LL solve() {
  res.clear();
  sort(A,A+N),reverse(A,A+N);
  int j=0;
  queue<int> Q; Q.push(0);
  vector<LL> res(N,-1);
  LL ans=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    res[u]=A[j++];
    if(u!=0) ans+=res[u];
    FORR(v,G[u]) if(res[v]==-1) Q.push(v);
  }
  cout<<ans<<endl;
  REP(i,N)cout<<res[i]<<" \n"[i==N-1];
  
  return ans;
}


LL solve_org() {
//  REP(i,N)G[i].clear();
  res.clear();
  ZERO(D);
  priority_queue<LL> Q;
  REP(i,N)Q.emplace(A[i]);
  
  REP(i,N)D[i]={SZ(G[i]),i};
  sort(D,D+N),reverse(D,D+N);
  int u=D[0].second;
  queue<int> QQ; QQ.push(u);
  res=vector<LL>(N,-1);
  while(SZ(QQ)) {
    int u=QQ.front(); QQ.pop();
//    dump(u);
    res[u]=Q.top(),Q.pop();
    FORR(v,G[u]) if(res[v]==-1)QQ.push(v);
  }
  LL ans=dfs(0,-1);
//  dump(ans);
  cout<<ans<<endl;
  REP(i,N)cout<<res[i]<<" \n"[i==N-1];
  
  /*
  LL b=0;
  do {
    REP(i,N)res[i]=A[i];
    SMAX(b,dfs(0,-1));
    if(b==40) {
      dumpC(A,A+N);
    }
  }while(next_permutation(A,A+N));
  */
  
  return ans;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> gen_tree(int N) {
  vector<int> P(N-1,0);
  printf("%d\n",N);
  for(int u=1; u<=N-1; ++u) {
    P[u-1]=genRandNum(0,u);
    printf("%d %d\n",u+1,P[u-1]+1);
  }
  // parent of u+1 = P[u] (P[u]<u+1)
  return P;
}

void test() {
  N=8;
  REP(i,N)G[i].clear();
  VI xs=gen_tree(N);
  REP(u,N-1) {
    int v=xs[u];
    G[u+1].push_back(v),G[v].push_back(u+1);
//    cerr<<(u+1)<<" "<<v<<endl;
  }
  REP(i,N) {
    A[i]=genRandNum(1,10);
    cerr<<A[i]<<" ";
  }
  LL a=solve();
  sort(A,A+N);
  LL b=0;
  do {
    REP(i,N)res[i]=A[i];
    SMAX(b,dfs(0,-1));
  }while(next_permutation(A,A+N));
  dump(a,b);
  assert(a==b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true)test();
  
  cin>>N;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
//    dump(u,v);
    G[u].push_back(v),G[v].push_back(u);
  }
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
