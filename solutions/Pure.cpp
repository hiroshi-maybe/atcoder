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

// $ cp-batch Pure | diff Pure.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Pure.cpp && ./a.out

/*
 
 9/28/2019
 
 5:52-6:40 give up.
 18:15-18:30 Output format was wrong. # of vertices was missing. I got AC after its fix.
 
 If there is a cycle, minimum cycle should be expected solution.
 
 https://youtu.be/l4pTJy13sbM?t=7507
 https://img.atcoder.jp/abc142/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/09/28/1030
 
 https://twitter.com/torus711/status/1177942891378831362?s=20
 https://twitter.com/ngtkana/status/1177943168832065538?s=20
 https://twitter.com/xuzijian629/status/1177945200708091909?s=20
 
 */

const int MAX_N=1e3+10;
int N;
VI G[MAX_N];

const int Inf=1e7;
int D[MAX_N];
void solve() {
  VI res(N+1,-1);
  REP(st,N) {
    
    REP(i,N) D[i]=Inf;
    VI pre(N,-1);
    queue<int> Q;
    Q.emplace(st),D[st]=0;
    while(SZ(Q)) {
      int u=Q.front(); Q.pop();
      int d=D[u];
      FORR(v,G[u]) {
        int dd=D[v];
        if(dd>d+1) {
          D[v]=d+1,Q.push(v);
          pre[v]=u;
        }
      }
    }
    int mind=Inf,end=-1;
    REP(i,N) if(i!=st) {
      FORR(v,G[i]) if(v==st&&D[i]<mind) {
        mind=D[i],end=i;
      }
    }
    if(end!=-1) {
      VI path; int cur=end;
      while(cur!=-1) path.push_back(cur),cur=pre[cur];
      if(SZ(path)<SZ(res)) res=path;
//      dump(st,end);
//      dumpc(path);
    }
    
  }
  if(SZ(res)>N) {
    println("-1");
  } else {
    println("%d",SZ(res));
    FORR(a,res) println("%d",a+1);
  }
}

int viz[MAX_N];
VI ok(VI &cur, int st) {
  VI A;
  for(int i=SZ(cur)-1; i>=0&&cur[i]!=st; --i) A.push_back(cur[i]);
  A.push_back(st);
  SETI S(ALL(A));
//  dumpc(S);
  int cnt=0;
  REP(i,SZ(A)) {
    int u=A[i];
    FORR(v,G[u]) {
//      dump(u,v,S.count(v));
      if(S.count(v))++cnt;
    }
  }
//  dump(cnt);
  if(cnt==SZ(A)) return A;
  return {};
}
void dfs(int u, VI &cur) {
  if(viz[u]==0) {
//    dump(u);
//    dumpc(cur);
    VI res=ok(cur,u);
    if(SZ(res)) {
      println("%d", SZ(res));
      REP(i,SZ(res)) println("%d", res[i]+1);
      exit(0);
    }
    return;
  }
  cur.push_back(u);
  viz[u]=0;
  FORR(v,G[u]) {
    dfs(v,cur);
  }
  viz[u]=1;
  cur.pop_back();
}

void solve_dfs() {
  MINUS(viz);
  REP(i,N) if(viz[i]==-1) {
    VI A;
    dfs(i,A);
  }
  println("-1");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
    
  int M;
  cin>>N>>M;
  
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
  }
  solve();
  
  /*
  int CN=SZ(scc.CC);
  REP(i,CN) {
    VI VV=scc.CC[i];
    dumpc(VV);
    SETI S(ALL(VV));
    int cnt=0;
    REP(i,SZ(VV)) {
      int u=VV[i];
      FORR(v,G[u]) if(S.count(v))++cnt;
    }
    if(cnt==SZ(VV)) {
      REP(i,SZ(VV)) printf("%d ", VV[i]+1);
      println("");
      return 0;
    }
  }
  println("-1");*/
  return 0;
}
