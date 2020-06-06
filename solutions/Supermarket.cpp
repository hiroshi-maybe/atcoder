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

// $ cp-batch Supermarket | diff Supermarket.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Supermarket.cpp && ./a.out

/*

 6/6/2020

 0:43-1:19 AC

 */

VV<int> T;
int N,M;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  T=VV<int>(N);
  REP(i,N) {
    int K; cin>>K;
    REP(j,K) {
      int t; cin>>t;
      T[i].push_back(t);
    }
    reverse(ALL(T[i]));
  }

  VI nxt(N,0);
  set<pair<int,int>> Q1,Q2;
  REP(i,N) if(SZ(T[i])) Q1.emplace(-T[i].back(),i),T[i].pop_back();
  REP(i,N) if(SZ(T[i])) nxt[i]=-T[i].back(),Q2.emplace(-T[i].back(),i),T[i].pop_back();

  int Q; cin>>Q;
  while(Q--) {
    int a; cin>>a;
    auto it1=Q1.begin();
    II x1=*it1,x2={0,1e8};
    if(a==2&&SZ(Q2)) x2=*(Q2.begin());
    int res=-1,i=-1;
    if(x2.first>x1.first) {
      res=-x1.first;
      Q1.erase(it1);
      II topush={nxt[x1.second],x1.second};
      if(Q2.count(topush)) Q2.erase(topush);
      Q1.emplace(topush);
      i=x1.second;
    } else {
      res=-x2.first;
      if(Q2.count(x2)) Q2.erase(x2);
      i=x2.second;
    }

    assert(i!=-1);
    if(SZ(T[i])) nxt[i]=-T[i].back(),Q2.emplace(-T[i].back(),i),T[i].pop_back();
    else nxt[i]=0;

    cout<<res<<endl;
  }

  return 0;
}
