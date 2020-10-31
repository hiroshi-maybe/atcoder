#include <bits/stdc++.h>
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
#define ALL(c) (c).begin(),(c).end()
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*

 7/30/2018

 26:30-27:20 RE in sample 1 :(
 27:21-27:30 fixed a bug and got ACC

 Editorials:
  - https://atcoder.jp/img/arc076/editorial.pdf
  - https://youtu.be/xUUPBXY2EZk?t=2167

 Key:
  - build minimum spanning tree
  - Put two edges (∆x and ∆y) between vertices
  - it's possible to pick up optimal edge in O(1) by sorting

 Summary:
  - It took a lot of time to find sorting to accelerate MST process
  - I didn't have graph with doubled edges in my mind
   - I should reduce problem more explicitly
   - Or I should figure out new problem formally
  - 1RE due to taking N edges 👎

 10/31/2020

 10:54-11:11 solve again

 */

// $ cp-batch Built | diff Built.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Built.cpp && ./a.out

struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int size(int x) { return sz[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    int p=x,c=y;
    if(sz[p]<sz[c]) swap(p,c);
    G--,sz[p]=sz[c]=sz[p]+sz[c];
    par[c]=p;
    return p;
  }
private:
  vector<int> par,sz;
};

const int MAX_N=1e6+1;
int XX[MAX_N],YY[MAX_N];
int N;

void solve() {
  vector<II> xs(N),ys(N);
  REP(i,N) xs[i]={XX[i],i},ys[i]={YY[i],i};
  sort(ALL(xs)),sort(ALL(ys));
  vector<III> as,bs;
  REP(i,N-1) {
    auto a=xs[i],b=xs[i+1];
    int dx=abs(a.first-b.first),u=a.second,v=b.second;
    as.emplace_back(dx,u,v);
  }
  REP(i,N-1) {
    auto a=ys[i],b=ys[i+1];
    int dy=abs(a.first-b.first),u=a.second,v=b.second;
    bs.emplace_back(dy,u,v);
  }
  sort(ALL(as)),sort(ALL(bs)),reverse(ALL(as)),reverse(ALL(bs));

  LL res=0;
  UF uf(N);
  const LL Inf=1e18;
  while(uf.G>1) {
    LL acost=Inf,bcost=Inf;
    if(SZ(as)) acost=get<0>(as.back());
    if(SZ(bs)) bcost=get<0>(bs.back());
    if(acost<bcost) {
      LL c; int u,v; tie(c,u,v)=as.back(); as.pop_back();
      if(!uf.sameset(u,v)) res+=c,uf.unite(u,v);
    } else {
      LL c; int u,v; tie(c,u,v)=bs.back(); bs.pop_back();
      if(!uf.sameset(u,v)) res+=c,uf.unite(u,v);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>XX[i]>>YY[i];
  solve();

  return 0;
}

//////////////////

pair<LL,int> X[MAX_N],Y[MAX_N];

LL solve_org() {
  sort(X,X+N),sort(Y,Y+N);
//  dump(N);
  vector<tuple<LL,int,int>> XX,YY;
  REP(i,N-1) {
    XX.emplace_back(X[i+1].first-X[i].first,X[i+1].second,X[i].second);
    YY.emplace_back(Y[i+1].first-Y[i].first,Y[i+1].second,Y[i].second);
//    dump4(i,get<0>(XX[i]),get<1>(XX[i]),get<2>(XX[i]));
//    dump4(i,get<0>(YY[i]),get<1>(YY[i]),get<2>(YY[i]));
  }
  sort(XX.begin(),XX.end()),sort(YY.begin(),YY.end());
//  dump(SZ(XX));

  LL res=0;
  UF uf(N+1);
  int i=0,j=0;
  while(i<N-1||j<N-1) {
    tuple<LL,int,int> a={-1,-1,-1};
    if(i>=N-1) a=YY[j++];
    else if(j>=N-1) a=XX[i++];
    else {
      if(XX[i]<YY[j]) a=XX[i++];
      else a=YY[j++];
    }
    LL d; int u,v; tie(d,u,v)=a;
    assert(d!=-1);
//    dump2(i,j);
//    dump3(d,u,v);
    if(uf.sameset(u,v)) continue;
    res+=d;
    uf.unite(u,v);
  }
  return res;
}

int main_org() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N;
  REP(i,N) {
    int x,y;
    cin>>x>>y;
    X[i]={x,i},Y[i]={y,i};
  }
  cout<<solve_org()<<endl;

  return 0;
}
