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

// $ cp-batch ShortestPathOnALine | diff ShortestPathOnALine.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ShortestPathOnALine.cpp && ./a.out

/*
 
 11/9/2019
 
 4:57-5:35 WA
 6:11 AC
 
 https://img.atcoder.jp/nikkei2019-2-qual/editorial.pdf
 https://youtu.be/qG1nQxAeaVA?t=1521
 https://www.hamayanhamayan.com/entry/2019/11/10/005039_2
 https://twitter.com/hanseilimak/status/1193605201577406464
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N], L[MAX_N], R[MAX_N], W[MAX_N];
int N,M;

using T=tuple<int,int,LL>;
const LL Inf=1e17;
LL solve() {
  vector<T> X;
  REP(i,M) X.emplace_back(R[i],L[i],W[i]);
  sort(ALL(X));
  map<int,LL> D;
  D[1]=0;
  REP(i,M) {
    int l,r; LL w; tie(r,l,w)=X[i];
    auto it=D.lower_bound(l);
    if(it!=D.end()) {
      if(D.count(r)==0) D[r]=Inf;
      SMIN(D[r],it->second+w);
//      dump(l,r,it->first,D[r]);
      VI Y;
      for(auto it2=prev(D.find(r)); it2!=D.begin()&&it2->second>=D[r]; --it2) {
        Y.push_back(it2->first);
      }
      FORR(i,Y) D.erase(i);
    }
  }
  LL res=D.count(N)?D[N]:-1;
  if(res>=Inf) res=-1;
  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  N=10;
  M=3;
  REP(i,M) L[i]=genRandNum(1,N),R[i]=genRandNum(L[i]+1,N+1),W[i]=genRandNum(1,10);
  vector<T> X;
  REP(i,M) X.emplace_back(R[i],L[i],W[i]);
  sort(ALL(X));
  
  vector<LL> dp(N+1,Inf);
  dp[1]=0;
  REP(i,M) {
    int l,r; LL w; tie(r,l,w)=X[i];
    FORE(j,l+1,r) SMIN(dp[j],dp[l]+w);
  }
  LL ans=dp[N];
  if(ans>=Inf) ans=-1;
  LL res=solve();
  if(res!=ans) {
    dump(res,ans);
    dumpc(dp);
    REP(i,M) dump(get<1>(X[i]),get<0>(X[i]),get<2>(X[i]));
  }
  assert(res==ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>M;
  REP(i,M) {
    cin>>L[i]>>R[i]>>W[i];
//    --L[i],--R[i];
  }
  cout<<solve()<<endl;
  
  return 0;
}
