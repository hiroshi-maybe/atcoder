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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch VariousSushi | diff VariousSushi.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VariousSushi.cpp && ./a.out

/*
 
 2/19/2019
 
 21:25-21:59 WA
 22:08 AC (overflow bug)
 
 https://img.atcoder.jp/abc116/editorial.pdf
 https://misteer.hatenablog.com/entry/ABC116
 
 */

const int MAX_N=1e6+1;
LL D[MAX_N];
int T[MAX_N];
int N,K;

void solve() {
  vector<pair<LL,int>> X(N);
  REP(i,N) X[i]={D[i],T[i]};
  sort(X.rbegin(),X.rend());
  
  dumpc(X);
  
  LL cur=0;
  MAPII ts;
  
  REP(i,K) {
    cur+=X[i].first;
    ts[X[i].second]++;
  }
  LL res=cur+1LL*SZ(ts)*SZ(ts);
  int l=K-1,r=K,n=K;
  dump(l,r,cur,SZ(ts),n);
  while(l>=0&&r<N) {
    while(l>=0) {
      int t; LL d; tie(d,t)=X[l--];
      if(ts[t]>1) {
        cur-=d,ts[t]--,--n;
        break;
      }
    }
    while(r<N) {
      int t; LL d; tie(d,t)=X[r++];
      if(ts.count(t)==0) {
        cur+=d,ts[t]++,++n;
        break;
      }
    }
    dump(l,r,n);
    if(n!=K) break;
    SMAX(res,cur+1LL*SZ(ts)*SZ(ts));
    dump(l,r,cur,SZ(ts));
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) cin>>T[i]>>D[i];
  solve();
  
  return 0;
}
