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

// $ cp-batch TwoCurrencies | diff TwoCurrencies.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoCurrencies.cpp && ./a.out

/*
 
 4/26/2020
 
 5:25-7:06 AC after looking at twitter
 
 https://twitter.com/hanseilimak/status/1254488842070974464
 https://img.atcoder.jp/abc164/editorial.pdf
 
 */

const int MAX_N=2e5+1;
LL A[MAX_N];
int N,M,S;

const int Infs=2500+10;
// (u,silver),dist
vector<pair<int,LL>> G[MAX_N];
LL D[MAX_N];
const LL Inf=1000000000000000LL;
void solve() {
  REP(u,N)REP(s,Infs) D[u*Infs+s]=Inf;
  int st=S;
  using P=pair<long long,int>;
  priority_queue<P,vector<P>,greater<P>> Q; Q.emplace(0,st); D[st]=0;
   while(Q.size()>0) {
//     auto it=Q.begin();
     int us; long long d;
     tie(d,us)=Q.top(),Q.pop();
     if(d!=D[us]) continue;
//     int u=us/Infs,s=us%Infs;
//     dump(u,s,d);
     for(auto p : G[us]) {
       int vs; long long w; tie(vs,w)=p;
       if(d+w<D[vs]) {
//         auto it2=Q.find({D[vs],vs});
//         if(it2!=Q.end()) Q.erase(it2);
         D[vs]=d+w; Q.emplace(d+w,vs);
       }
     }
   }
  
  vector<LL> res(N,Inf);
  REP(u,N) REP(s,Infs) {
    SMIN(res[u],D[u*Infs+s]);
  }
  FOR(i,1,N) cout<<res[i]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  set<int> x; int y=0;
  
  cin>>N>>M>>S;
  S=min(S,Infs-1);
  REP(i,M) {
    int u,v,a; LL b; cin>>u>>v>>a>>b;
    --u,--v;
    REP(s,Infs) if(s-a>=0) {
      G[Infs*u+s].emplace_back(Infs*v+s-a,b);
      G[Infs*v+s].emplace_back(Infs*u+s-a,b);
//      x.emplace(Infs*u+s),x.emplace(Infs*v+s);
    }
  }
  REP(u,N) {
    int c; LL d; cin>>c>>d;
    REP(s,Infs) {
      int ss=(int)min((LL)Infs-1,(LL)s+c);
      G[Infs*u+s].emplace_back(Infs*u+ss,d);
//      ++y;
    }
  }
//  dump(SZ(x),y);
  solve();
  
  return 0;
}
