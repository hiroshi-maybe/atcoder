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

// $ cp-batch Doublet | diff Doublet.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Doublet.cpp && ./a.out

/*

 5/25/2020

 16:21-16:50 AC

 https://kmjp.hatenablog.jp/entry/2013/01/19/0930

 */

const int MAX_N=1e3+10;
string S[MAX_N];
int N;
string s,e;

const int Inf=1e8;
VI G[MAX_N];
int D[MAX_N];
int pre[MAX_N];
void solve() {
  S[N]=s,S[N+1]=e;
  if(s==e) {
    cout<<0<<endl;
    cout<<s<<endl;
    cout<<s<<endl;
    return;
  }
  int M=N+2;
  int L=SZ(s);
  REP(j,M)REP(i,j) {
    int cnt=0;
    REP(k,L) cnt+=S[i][k]!=S[j][k];
    if(cnt==1) G[i].push_back(j),G[j].push_back(i);
  }

  REP(i,M) D[i]=Inf,pre[i]=-1;
  queue<int> Q;
  Q.emplace(N),D[N]=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    FORR(v,G[u]) {
      if(D[v]>D[u]+1) {
        Q.emplace(v),D[v]=D[u]+1,pre[v]=u;
      }
    }
  }
  if(D[N+1]==Inf) {
    cout<<-1<<endl;
    return;
  }
  VI res={N+1};
  int i=N+1;
  while(pre[i]!=-1) {
    res.push_back(pre[i]),i=pre[i];
  }
  //dumpC(S,S+M);
  reverse(ALL(res));
  //dumpc(res);
  cout<<SZ(res)-2<<endl;
  REP(i,SZ(res)) cout<<S[res[i]]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>s>>e>>N;
  REP(i,N) cin>>S[i];
  solve();

  return 0;
}
