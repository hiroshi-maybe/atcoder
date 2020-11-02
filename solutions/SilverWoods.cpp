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
template<typename num>
struct Point {
public:
  num x, y;
  Point(): x(0), y(0) {}
  Point(num x, num y): x(x), y(y) {}
  Point(pair<num,num> p): x(p.first), y(p.second) {}
  Point(pair<num,num> p, pair<num,num> org): Point(p.first-org.first, p.second-org.second) {}
  Point(Point p, Point org): Point(p.x-org.x, p.y-org.y) {}

  explicit operator bool() const { return x!=0||y!=0; }
  Point operator-() const { return Point(0,0)-*this; }
  Point &operator+=(Point that) { x+=that.x,y+=that.y; return *this; }
  Point &operator-=(Point that) { x-=that.x,y-=that.y; return *this; }
  Point &operator*=(double a) { x*=a,y*=a; return *this; }
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  Point operator*(double a) const { return Point(*this)*=a; }
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<num,num>(x,y)<pair<num,num>(that.x,that.y); }
  bool operator>(Point that) const { return pair<num,num>(x,y)>pair<num,num>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  num distance() { return x*x + y*y; }
  Point rotate90() { return Point{-y, x}; }
  int orthant() const {
    if(x==0&&y==0) return 1;
    if(y>0) return x>0?1:2;
    else return x>0?4:3;
  }
};
// $ cp-batch SilverWoods | diff SilverWoods.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SilverWoods.cpp && ./a.out

/*

 11/1/2020

 5:26-5:35, 8:07-9:12 give up

 9:45-10:17 AC

 https://twitter.com/hanseilimak/status/1323134025599389696
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.cw0pz5h8w1p5

 https://atcoder.jp/contests/abc181/editorial/267
 https://drken1215.hatenablog.com/entry/2020/11/02/013900
 https://kmjp.hatenablog.jp/entry/2020/11/01/0930

 https://twitter.com/kyopro_friends/status/1322897594981363712

 */

const int MAX_N=1e6+1;
II P[MAX_N];
int N;

bool ok(double r) {
  set<int> xs;
  REP(i,N) xs.emplace(P[i].first);
  vector<Point<int>> ps;
  REP(i,N) ps.emplace_back(P[i]);
  FORR(x,xs) ps.emplace_back(x,100),ps.emplace_back(x,-100);
  UF uf(SZ(ps));
  FOR(i,N,SZ(ps)) if(i+2<SZ(ps)) {
    uf.unite(i,i+2);
  }
  REP(j,SZ(ps))REP(i,j) if(sqrt((ps[i]-ps[j]).distance())<2*r) {
    //dump(i,j,sqrt((ps[i]-ps[j]).distance()));
    uf.unite(i,j);
  }
  //dumpc(ps);
  //REP(i,SZ(ps)) dump(i,uf.find(i));

  return !uf.sameset(SZ(ps)-1,SZ(ps)-2);
}

void solve() {
  double good=0,bad=101;
  REP(_, 100) {
    double m=(good+bad)/2;
    bool res=ok(m);
    //dump(m,res);
    (res?good:bad)=m;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>P[i].first>>P[i].second;
  solve();

  return 0;
}
