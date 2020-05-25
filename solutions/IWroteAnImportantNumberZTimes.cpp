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
// $ cp-batch IWroteAnImportantNumberZTimes | diff IWroteAnImportantNumberZTimes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address IWroteAnImportantNumberZTimes.cpp && ./a.out

/*

 5/25/2020

 10:53-11:33 WA
 11:55 AC

 https://www.slideshare.net/chokudai/arc027

 */

//const int MAX_N=1e6+1;
string S[2];
int N;

//const int Inf=100;
LL solve() {
  map<char,int> cis;
  int ci=0;
  REP(k,2)REP(i,N) if(!isdigit(S[k][i])&&cis.count(S[k][i])==0) {
    cis[S[k][i]]=ci++;
  }

  UF uf(ci);
  REP(i,N) if(!isdigit(S[0][i])&&!isdigit(S[1][i])) {
    uf.unite(cis[S[0][i]],cis[S[1][i]]);
  }
  VI ks(ci,-100);
  // -2:0..9,-1:1..9,d
  FORR(kvp,cis) {
    char c=kvp.first;
    int gid=uf.find(cis[c]);
    REP(k,2)REP(i,N) if(S[k][i]==c) {
      if(isdigit(S[1-k][i])) SMAX(ks[gid],S[1-k][i]-'0');
      else if(i==0) SMAX(ks[gid],-1);
      else SMAX(ks[gid],-2);
    }
    //dump(c,gid);
  }
  LL res=1;
  REP(k,ci) if(ks[k]>=-2) {
    if(ks[k]==-2) res*=10;
    else if(ks[k]==-1) res*=9;
  }
  return res;
/*
  auto mrange=[&](char c, int l, int r) {
    int l1=rs[cis[c]].first,r1=rs[cis[c]].second;
    SMAX(l,l1),SMIN(r,r1);
    assert(l<=r);
    rs[cis[c]]={l,r};
  };
  REP(k,2) if(!isdigit(S[k][0])) rs[cis[S[k][0]]].first=1;

  REP(i,N) {
    if(!isdigit(S[0][i])&&!isdigit(S[1][i])) {
      if(S[0][i]!=S[1][i]) {
        int c0=S[0][i]-'A',c1=S[1][i]-'A';
        int cc0=uf.find(c0),cc1=uf.find(c1);
        int x=uf.unite(c0,c1);
        int y=cc0==x?cc1:cc0;
        mrange('A'+x, rs[y].first, rs[y].second);
      }
    } else if(!isdigit(S[0][i])) {
      int d=S[1][i]-'0';
      mrange(S[0][i],d,d);
    } else if(!isdigit(S[1][i])) {
      int d=S[0][i]-'0';
      mrange(S[1][i],d,d);
    }
    REP(k,2) if(!isdigit(S[k][i])) mrange(S[k][i],i==0?1:0,9);
  }
  LL res=1;
  REP(c,26) if(uf.find(c)==c&&rs[c].first!=-Inf) {
    res*=rs[c].second-rs[c].first+1;
  }
  return res;*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(k,2) cin>>S[k];
  cout<<solve()<<endl;

  return 0;
}
