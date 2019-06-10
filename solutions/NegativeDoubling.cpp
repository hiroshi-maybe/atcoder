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

// $ cp-batch NegativeDoubling | diff NegativeDoubling.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NegativeDoubling.cpp && ./a.out

/*
 
 6/8/2019
 
 16:43-18:00 give up
 16:05-18:40 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2018/12/23/1000
 http://noimin.hatenablog.com/entry/2018/12/26/002011
 https://betrue12.hateblo.jp/entry/2018/12/24/030307
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

__int128 p4[40];
LL dpl[MAX_N][20],dpr[MAX_N][20];
const LL Inf=1e18;
LL solve() {
  p4[0]=1; FOR(i,1,40) p4[i]=p4[i-1]*4;
  REP(i,N)REP(j,20)dpl[i][j]=dpr[i][j]=Inf;
  REP(j,20) dpr[N-1][j]=dpl[0][j]=j;

  for(int i=N-2; i>=0; --i) {
    REP(x,16) {
      int j=0;
      while(p4[x]*A[i]>p4[j]*A[i+1]) ++j;
      if(j<=15) dpr[i][x]=dpr[i+1][j]+x;
      else dpr[i][x]=dpr[i+1][15]+(LL)(N-1-i)*(j-15)+x;
    }
  }
  FOR(i,1,N) {
    REP(x,16) {
      int j=0;
      while(p4[j]*A[i-1]<p4[x]*A[i]) ++j;
      if(j<=15) dpl[i][x]=dpl[i-1][j]+x;
      else dpl[i][x]=dpl[i-1][15]+(LL)i*(j-15)+x;
    }
  }
  LL res=dpr[0][0]*2;
  FOR(i,1,N) SMIN(res,i+dpl[i-1][0]*2+dpr[i][0]*2);
  return res;
}


int f(int s, LL a, LL b) {
  int x=s;
  while(a*(1LL<<x)<b*(s==1?2:1)) x+=2;
  return x;
}
/*
LL solve_wrong() {
  int cnt0=0,p0=-1;
  REP(i,N) if(A[i]==0&&(i==N-1||A[i+1]!=0)) ++cnt0,p0=i;
  if(cnt0>1) return -1;
  if(p0!=-1) {
    int p1=p0;
    while(p1<N&&A[p1]==0) ++p1;
//    LL res=left(p0-1)+right(p1);
    return -1;
  }
  dpl[0]=1;
  FOR(i,1,N) {
    LL a=A[i-1],b=A[i];
    int x=f(1,a,b);
    dpl[i]=dpl[i-1]+(LL)i*(x-1)+1;
    dump(i,x,dpl[i]);
  }
  dpr[N-1]=0;
  for(int i=N-2; i>=0; --i) {
    LL a=A[i+1],b=A[i];
    int x=f(0,a,b);
    dpr[i]=dpr[i+1]+(LL)(N-i-1)*(x-1)+1;
    dump(i,x,dpr[i]);
  }
  LL res=min(dpl[N-1],dpr[0]);
  REP(i,N-1) SMIN(res,dpl[i]+dpr[i+1]);
  return res;
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
