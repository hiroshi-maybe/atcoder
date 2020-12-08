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

// $ cp-batch WeirdDictionary | diff WeirdDictionary.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WeirdDictionary.cpp && ./a.out

/*

 12/8/2020

 16:36-17:10 AC

 https://www.slideshare.net/chokudai/abc030

 */

const int MAX_N=1e6+1;
int B[MAX_N];
string K;
int N,a;

bool dec() {
  bool bor=1;
  for(int i=SZ(K)-1; i>=0; --i) {
    int d=K[i]-'0'-bor;
    //dump(i,d);
    bor=0;
    if(d<0) {
      bor=1;
      K[i]='0'+d+10;
    } else K[i]='0'+d;
    if(bor==0) return false;
  }
  if(bor==1) return true;
  return false;
}
int viz[MAX_N];
void solve() {
  MINUS(viz);
  int u=a,i=0;
  while(true) {
    if(viz[u]!=-1) break;
    if(dec()) {
      cout<<u+1<<endl;
      return;
    }
    viz[u]=i++;
    u=B[u];
  }
  int L=i-viz[u];
  //dump(L,K,u,i);
  LL p10=1;
  int j=0;
  for(int i=SZ(K)-1; i>=0; --i) {
    j=(j+(K[i]-'0')*p10)%L;
    p10*=10,p10%=L;
  }
  while(j--) u=B[u];
  cout<<u+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>a>>K;
  --a;
  REP(i,N) {
    cin>>B[i];
    B[i]--;
  }
  solve();

  return 0;
}
