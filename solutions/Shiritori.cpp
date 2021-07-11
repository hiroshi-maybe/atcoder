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
struct GraphCycle {
public:
  // input
  int V;
  vector<vector<int>> G;
  GraphCycle(int V): V(V), G(V), done(V, -1), viz(V, 0) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
  }

  vector<int> findCycleFreeNodes() {
    vector<int> res;
    for(int u=0; u<V; ++u) {
      if(!viz[u]) dfs(u);
      if(!done[u]) res.push_back(u);
    }
    return res;
  }
private:
  vector<int> done; // -1: not done, 0: descendent has NO cycle, 1: descendent has cycle
  vector<int> viz;

  int dfs(int u) {
    if(done[u]!=-1) return done[u];
    viz[u]=true;

    int res=false;
    for(int v : G[u]) {
      if(!viz[v]) dfs(v);
      res|=done[v]==-1?true:done[v];
    }
    return done[u]=res;
  }
};

// $ cp-batch Shiritori | diff Shiritori.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Shiritori.cpp && ./a.out

/*

 7/10/2021

 21:25-21:40 give up

 7/11/2021

 9:45-12:00, 13:30-17:45 read editorials and got AC

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.zfu0pbcxzmdr
 https://twitter.com/hanseilimak/status/1414139550843097091
 https://qiita.com/drken/items/4e1bcf8413af16cb62da

 https://youtu.be/FEDp2Kzc7jk?t=4232
 https://atcoder.jp/contests/abc209/editorial/2230

 */

const int MAX_N=1e6+1;
string S[MAX_N];
int N;
char aa[2]={'a','A'};
const int Inf=1e8;
int ctoi(char c) {
  int res=Inf;
  REP(i,2) {
    int x=c-aa[i]+26*i;
    if(x<0) x=Inf;
    SMIN(res,x);
  }
  return res;
}
int id(string s) {
  int res=0;
  REP(i,3) {
    res*=52;
    res+=ctoi(s[i]);
  }
  return res;
}
II pspair(string s) {
  string p=s.substr(0, 3),su=s.substr(SZ(s)-3, 3);
  return {id(p),id(su)};
}

VI revG[MAX_N];
int outd[MAX_N];

void solve() {
  REP(i,N) {
    auto p=pspair(S[i]);
    revG[p.second].push_back(p.first),outd[p.first]++;
  }
  queue<int> Q;
  VI res(MAX_N,-1);
  REP(i,MAX_N) if(outd[i]==0) Q.emplace(i),res[i]=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    assert(outd[u]==0);
    FORR(v,revG[u]) if(res[v]==-1) {
      outd[v]--;
      if(res[u]==0) res[v]=1,outd[v]=0,Q.emplace(v);
      else if(outd[v]==0) res[v]=0,Q.emplace(v);
    }
  }

  REP(i,N) {
    auto p=pspair(S[i]);
    string ans="Draw";
    if(res[p.second]==0) ans="Takahashi";
    else if(res[p.second]==1) ans="Aoki";
    cout<<ans<<endl;
  }
}

VI IN[MAX_N],OUT[MAX_N];
VI G[MAX_N], xG[MAX_N];
int ind[MAX_N];

VI solve_org(int t=0) {
  REP(i,MAX_N) G[i].clear(),xG[i].clear(),revG[i].clear(),IN[i].clear(),OUT[i].clear();
  ZERO(ind),ZERO(outd);

  if(t==0||t==1) {
    VI res(MAX_N,-1);
    REP(i,N) {
      auto p=pspair(S[i]);
      dump(p.first,p.second);
      revG[p.second].push_back(p.first),xG[p.first].push_back(p.second);
      ind[p.first]++;
    }
    queue<int> Q;

    if(t==0) {
      REP(i,MAX_N) if(ind[i]==0) {
        res[i]=0;
        Q.emplace(i);
      }
      while(SZ(Q)) {
        int u=Q.front(); Q.pop();
        FORR(v, revG[u]) if(res[v]==-1) {
          ind[v]--;
          if(res[u]==0) res[v]=1,Q.emplace(v);
          else if(ind[v]==0) res[v]=0,Q.emplace(v);
        }
      }
    } else {
      // wrong
      REP(i,MAX_N) if(ind[i]==0) {
        Q.emplace(i);
      }
      while(SZ(Q)) {
        int u=Q.front(); Q.pop();
        res[u]=0;
        FORR(v,xG[u]) {
          if(res[v]==0) res[u]=1;
        }
        FORR(v,revG[u]) {
          ind[v]--;
          if(ind[v]==0) Q.emplace(v);
        }
      }
    }

    VI ans2(N,-1);
    REP(i,N) {
      auto p=pspair(S[i]);
      string ans="Draw";
      if(res[p.second]==0) ans="Takahashi",ans2[i]=0;
      else if(res[p.second]==1) ans="Aoki",ans2[i]=1;
      cout<<ans<<endl;
    }
    return ans2;
  }

  {
    // wrong
    REP(i,N) {
      auto p=pspair(S[i]);
      IN[p.first].push_back(i),OUT[p.second].push_back(i);
    }

    GraphCycle gc(N);
    REP(i,N) {
      auto p=pspair(S[i]);
      FORR(v,IN[p.second]) gc.edge(i, v);
    }

    VI xs=gc.findCycleFreeNodes();
    VI res(N,-1);
    auto dfs=[&](auto &&self, int u) {
      if(res[u]>=0) return res[u];
      res[u]=0;
      FORR(v,gc.G[u]) {
        int a=self(self, v);
        if(a==0) res[u]=1;
      }
      return res[u];
    };

    FORR(u, xs) dfs(dfs,u);
    REP(u,N) if(res[u]==-1) {
      FORR(v,gc.G[u]) if(res[v]==0) res[u]=1;
    }
    //dumpc(res);
    REP(u,N) {
      string ans="Draw";
      if(res[u]==0) ans="Takahashi";
      else if(res[u]==1) ans="Aoki";
      cout<<ans<<endl;
    }
    return res;
  }
  return {};
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=10;
  REP(i,N) {
    VI x=genRandSeq(6,0,3);
    string s(6,'a');
    REP(j,SZ(s)) s[j]='a'+x[j];
    S[i]=s;
  }
  VV<int> ans(3);
  REP(i,3) ans[i]=solve_org(i);
  if(ans[0]!=ans[2]) {
    dumpC(S,S+N);
    dumpc(ans[0])
    dumpc(ans[2])
  }
  assert(ans[0]==ans[2]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N;
  REP(i,N) cin>>S[i];
  /*
  VI res=solve_org(1);
  dumpc(res);*/
  solve();

  return 0;
}
