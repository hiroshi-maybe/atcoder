#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*

 8/16/2018

 10:55-11:15 analysis
 11:16-11:33 implement, submit and got AC

 Editorials:
  - https://img.atcoder.jp/soundhound2018-summer-qual/editorial.pdf
  - http://betrue12.hateblo.jp/entry/2018/07/08/122013
  - https://www.hamayanhamayan.com/entry/2018/07/09/190130
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2018/0707_soundhound2018_summer_qual
  - https://qiita.com/arcslab123/items/d71c27ba30f2cce10eba
  - https://kimiyuki.net/writeup/algo/atcoder/soundhound2018-summer-qual-d/
  - http://d.hatena.ne.jp/merom686/20180708/1531024153
  - http://tancahn2380.hatenablog.com/entry/2018/07/13/160133

 10/31/2020

 solve again

 */

// $ cp-batch SavingSnuuk | diff SavingSnuuk.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SavingSnuuk.cpp && ./a.out

const int MAX_N=1e6+1;
int N,M,S,T;

vector<II> G[MAX_N];
using Edge=pair<long long, int>;
const LL Inf=1e18;

vector<LL> dijkstra(int V, int st) {
  vector<LL> D(V,Inf);
  priority_queue<Edge,vector<Edge>,greater<Edge>> Q; Q.emplace(0,st); D[st]=0;
  while(Q.size()>0) {
    long long d; int u;
    tie(d,u)=Q.top(),Q.pop();
    if(d!=D[u]) continue;
    for(auto p : G[u]) {
      long long w; int v; tie(w,v)=p;
      if(d+w<D[v]) D[v]=d+w,Q.emplace(d+w,v);
    }
  }
  return D;
}

void solve() {
  vector<LL> d1=dijkstra(2*N, S),d2=dijkstra(2*N, T+N);
  vector<LL> res(N+1,Inf);
  for(int i=N-1; i>=0; --i) {
    SMIN(res[i],res[i+1]);
    LL ans=d1[i]+d2[i+N];
    SMIN(res[i],ans);
  }
  REP(i,N) cout<<(LL)1e15-res[i]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>S>>T; --S,--T;
  REP(i,M) {
    int u,v; LL a,b; cin>>u>>v>>a>>b;
    --u,--v;
    G[u].emplace_back(a,v),G[v].emplace_back(a,u);
    G[u+N].emplace_back(b,v+N),G[v+N].emplace_back(b,u+N);
  }
  solve();

  return 0;
}

vector<LL> W[2][MAX_N];
vector<int> E[MAX_N];

//const long long Inf=1e17;
const int MAX_V=MAX_N;
long long D[2][MAX_V];
void dijkstra_org(int V, int st, int cur) {
  for(int i=0; i<V; ++i) D[cur][i]=Inf;
  set<pair<long long,int>> Q; Q.emplace(0,st); D[cur][st]=0;
  while(Q.size()>0) {
    auto it=Q.begin(); Q.erase(it);
    int u; long long d;
    tie(d,u)=*it;
    REP(i,SZ(E[u])) {
      int v=E[u][i];
      LL w=W[cur][u][i];
      if(d+w<D[cur][v]) {
        auto it2=Q.find({D[cur][v],v});
        if(it2!=Q.end()) Q.erase(it2);
        D[cur][v]=d+w; Q.emplace(d+w,v);
      }
    }
  }
//  REP(i,V) dump2(i,D[cur][i]);
}

void solve_org() {
  dijkstra_org(N,S,0),dijkstra_org(N,T,1);
  priority_queue<pair<LL,int>, vector<pair<LL,int>>, greater<pair<LL,int>>> Q;
  REP(u,N) {
    LL x=D[0][u]+D[1][u];
    Q.emplace(x,u);
  }
  REP(u,N) {
    while(SZ(Q)&&Q.top().second<u) Q.pop();
    assert(SZ(Q));
//    dump3(u,Q.top().first,Q.top().second);
    LL res=1e15-Q.top().first;
    cout<<res<<endl;
  }
}

int main_org() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N>>M>>S>>T;
  --S,--T;
  REP(i,M) {
    int u,v; LL a,b; cin>>u>>v>>a>>b;
    --u,--v;
    E[u].push_back(v),E[v].push_back(u);
    W[0][u].push_back(a),W[0][v].push_back(a);
    W[1][u].push_back(b),W[1][v].push_back(b);
  }
  solve_org();
  return 0;
}
