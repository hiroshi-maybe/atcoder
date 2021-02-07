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

// $ cp-batch CircleLatticePoints | diff CircleLatticePoints.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CircleLatticePoints.cpp && ./a.out

/*

 2/6/2021

 4:19-4:54, 5:24 WA on only one test case with long double
 21:25-21:49 AC with long long integer. Needed to fix overflow bug though.

 https://atcoder.jp/contests/abc191/editorial/611

 */
#define round(x) ((x)>=0?(LL)((x)+0.5):(LL)((x)-0.5))
long double X,Y,R;
int yc;
const int Inf=2e5+10;
bool ok(LL x, LL y) {
  LL XX=round(X*10000),YY=round(Y*10000),r=round(R*10000);
  LL xx=x*10000,yy=y*10000;
  LL dx=xx-XX,dy=yy-YY;
  //assert(dx*dx<=2e18&&r*r<=2e18);
  LL a=dx*dx+dy*dy,b=r*r;
  //long double dx2=x-X,dy2=y-Y;
  //long double a2=dx2*dx2+dy2*dy2,b2=R*R;
  //assert((a<=b)==(a2<=b2));
  return a<=b;
}
int ub(int x, int yc) {
  int bad=Inf,good=yc;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool res=ok(x,m);
    //dump(good,bad,m,res);
    (res?good:bad)=m;
  }
  return good;
}
int lb(int x, int yc) {
  int bad=-Inf,good=yc;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool res=ok(x,m);
    (res?good:bad)=m;
  }
  return good;
}
void solve() {
  LL res=0;
  int xl=(int)(X-R-10),xr=(int)(X+R+10);
  yc=(int)Y;
  FORE(x,xl,xr) {
    int y=Inf;
    FOR(yy,yc-10,yc+10) if(ok(x,yy)) {
      y=yy; break;
    }
    if(y==Inf) continue;
    LL r=ub(x,y),l=lb(x,y);
    //dump(x,y,l,r);
    res+=r-l+1;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>X>>Y>>R;
  solve();

  return 0;
}
