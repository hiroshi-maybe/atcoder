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

// $ cp-batch SequenceSum | diff SequenceSum.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SequenceSum.cpp && ./a.out

/*

 9/19/2020

 5:25-5:59 AC

 https://atcoder.jp/contests/abc179/editorial/115
 https://drken1215.hatenablog.com/entry/2020/09/20/091500

 */

LL N;
int X,M;

int f(int a) {
  LL b=(LL)a*a%M;
  return (int)b;
}

void solve() {
  VI viz(M,-1);
  vector<LL> A;
  int i=0,cur=X; viz[X]=0;
  A.push_back(X);
  while(true) {
    ++i,cur=f(cur),A.push_back(cur);
    if(viz[cur]>=0) {
      break;
    } else {
      viz[cur]=i;
    }
  }

  int s=viz[cur],t=i;
  int first=s,cycle=t-s;

  //dump(s,t,first,cycle);
  //dumpc(A);

  vector<LL> cum(SZ(A)+1);
  REP(i,SZ(A)) cum[i+1]=cum[i]+A[i];
  LL res=0;
  int x=(int)min((LL)first,N);
  N-=x,res+=cum[x];
  LL times=N/cycle,rem=N%cycle;

  res+=(cum[t]-cum[s])*times;
  res+=cum[s+rem]-cum[s];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>X>>M;
  solve();

  return 0;
}
