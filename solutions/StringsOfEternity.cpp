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

// $ cp-batch StringsOfEternity | diff StringsOfEternity.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StringsOfEternity.cpp && ./a.out

/*
 
 7/27/2019
 
 5:39-6:40 give up
 10:00-10:46 read editorials and got AC
 
 My code was assumuing only the case such that T cycle starts from initial character of S.
 
 https://img.atcoder.jp/abc135/editorial.pdf
 https://twitter.com/uwitenpen/status/1155133476380667905?s=20
 
 */
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
vector<int> zalgo(string &S) {
  int N=S.size();
  vector<int> Z(N,0);
  int l=0;
  for(int i=1; i<N; ++i) {
    // S[l..r] is current right most prefix-substring
    int r=l+Z[l],pre=Z[i-l];
    if (i+pre<r) {
      Z[i]=pre;
    } else {
      int j=max(0, r-i);
      while(i+j<N&&S[j]==S[i+j]) ++j;
      Z[i]=j;
      l=i;
    }
  }
  Z[0]=N;
  return Z;
}
const int MAX_N=1e7+1;
string S,T;

void solve() {
  string SS=S+S;
  while(SZ(SS)<SZ(T)) SS+=S;
  int M=SZ(T);
  string TS=T+"$"+SS+SS;
  VI Z=zalgo(TS);
  //  dump(TS);
  //  dumpc(Z);
  assert(SZ(TS)<MAX_N);
  int N=SZ(SS);
  VI G(N,-1);
  FOR(i,M+1,SZ(Z)) if(Z[i]==M) {
    int u=i-(M+1),v=(u+M)%N;
    if(u<N)G[u]=v;
  }
//  dumpc(G);
  UF uf(N);
  REP(i,N) if(G[i]!=-1) {
    int u=i,v=G[i];
    if(uf.find(u)==uf.find(v)) {
      cout<<-1<<endl;
      return;
    }
    uf.unite(u,v);
  }
  int res=0;
  REP(i,N) SMAX(res,uf.size(i));
  assert(res>0);
  cout<<res-1<<endl;
}

int dp[MAX_N];
void solve_wrong() {
  ZERO(dp);
  int M=SZ(T);
  string SS=S;
  while(SZ(SS)<MAX_N/2) SS+=S;

  string X=S;
  while(SZ(X)<2*M) X+=S;
  string pref=X.substr(0,M),suf=X.substr(M);
//  dump(X,pref,suf);
  if(pref==T) {
    if(SZ(suf)>0&&M%SZ(suf)==0) {
      bool ok=true;
      REP(i,M) if(T[i]!=suf[i%SZ(suf)]) ok=false;
      if(ok) {
        cout<<-1<<endl;
        return;
      }
    } else if(SZ(suf)==0) {
      cout<<-1<<endl;
      return;
    }
  }
  string TS=T+"$"+SS;
  VI Z=zalgo(TS);
//  dump(TS);
//  dumpc(Z);
  assert(SZ(TS)<MAX_N);
  int N=SZ(Z),res=0;
  FOR(i,M+1,N) if(Z[i]==M) {
    if(i+M<=N){
      SMAX(dp[i+M],dp[i]+1);
      SMAX(res,dp[i+M]);
    }
  }
  cout<<res<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  int N=genRandNum(1,5e5),M=genRandNum(1,5e5);
  VI A=genRandSeq(N,0,26),B=genRandSeq(M,0,26);
  S=string(N,'a'),T=string(M,'a');
  REP(i,N)S[i]='a'+A[i];
  REP(i,M)T[i]='a'+B[i];
  dump(S);
  dump(T);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>S>>T;
  solve();
  
  return 0;
}
