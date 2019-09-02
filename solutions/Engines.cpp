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

// $ cp-batch Engines | diff Engines.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Engines.cpp && ./a.out

/*
 
 9/1/2019
 
 5:58-6:40 give up
 17:30-19:05 read editorials
 
 Group by polar angle sort
 https://twitter.com/hanseilimak/status/1168346783363153920
 
 https://img.atcoder.jp/abc139/editorial.pdf
 https://youtu.be/UWbGRhF3Ozw?t=8213
 http://kmjp.hatenablog.jp/entry/2019/09/01/1030
 https://twitter.com/_primenumber/status/1168156580027621377
 https://twitter.com/kyort0n/status/1168175301609676802
 https://twitter.com/kyopro_friends/status/1168182509437214720
 https://twitter.com/tempura_cpp/status/1168156924258336768
 https://twitter.com/satanic0258/status/1168156952687329281?s=20
 https://twitter.com/kzyKT_M/status/1168156629130305537?s=20
 https://twitter.com/kymn_/status/1168156658083647488?s=20
 https://twitter.com/ngtkana/status/1168158312707133440
 
 */

const int MAX_N=100+1;
int X[MAX_N],Y[MAX_N];
int N;

typedef int ValType;
typedef long long ValTypeLL;
struct Point {
public:
  ValType x, y;
  Point(): x(0), y(0) {}
  Point(ValType x, ValType y): x(x), y(y) {}
  Point(pair<ValType,ValType> p): x(p.first), y(p.second) {}
  Point(pair<ValType,ValType> p, pair<ValType,ValType> org): Point(p.first-org.first, p.second-org.second) {}
  Point(Point p, Point org): Point(p.x-org.x, p.y-org.y) {}
  
  explicit operator bool() const { return x!=0||y!=0; }
  Point operator-() const { return Point(0,0)-*this; }
  Point &operator+=(Point that) { x+=that.x,y+=that.y; return *this; }
  Point &operator-=(Point that) { x-=that.x,y-=that.y; return *this; }
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<ValType,ValType>(x,y)<pair<ValType,ValType>(that.x,that.y); }
  bool operator>(Point that) const { return pair<ValType,ValType>(x,y)>pair<ValType,ValType>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  ValTypeLL distance() { return (ValTypeLL)x*x + (ValTypeLL)y*y; }
  Point rotate90() { return Point{-y, x}; }
  int orthant() const {
    if(y>0) return x>0?1:2;
    else return x>0?4:3;
  }
};
ValTypeLL det(Point u, Point v) {
  return (ValTypeLL)u.x*v.y - (ValTypeLL)u.y*v.x;
}
ValTypeLL det(Point origin, Point p1, Point p2) {
  return det(p1-origin, p2-origin);
}
void sortByPolarAngle(vector<Point>& ps, Point origin) {
  sort(ps.begin(), ps.end(), [&](const Point &a, const Point &b) {
    int oa=a.orthant(),ob=b.orthant();
    if(oa!=ob) return oa<ob;
    ValTypeLL d = det(origin,a,b);
    if(d!=0) return d > 0;
    return Point(a,origin).distance() < Point(b,origin).distance();
  });
}

void solve() {
  vector<Point> ps(N);
  REP(i,N) ps[i]={(ValType)X[i],(ValType)Y[i]};
  sortByPolarAngle(ps, {0,0});
  ValTypeLL res=0;
  REP(st,N)FORE(len,1,N) {
    Point x={0,0};
    REP(l,len) x+=ps[(st+l)%N];
    SMAX(res,x.distance());
  }
  cout<<sqrt(res)<<endl;
}

double res=0;
int viz[MAX_N];
void dfs(LL x, LL y, int cnt) {
  double cur=hypot(x,y);
  SMAX(res,cur);
  if(cnt==N) return;
  vector<pair<double,int>> xs;
  REP(i,N) if(!viz[i]) {
    LL xx=x+X[i],yy=y+Y[i];
    xs.emplace_back(hypot(xx,yy),i);
  }
  auto it=max_element(ALL(xs));
  if(it->first<cur) return;
  int k=it->second;
  viz[k]=1;
  dfs(x+X[k],y+Y[k],++cnt);
  viz[k]=0;
}
void f(int mask) {
  ZERO(viz);
  LL x=0,y=0;
  int cnt=0;
  
  int px=(mask>>1)&1,py=mask&1;
  REP(i,N) {
    if(px&&X[i]<0) continue;
    if(!px&&X[i]>0) continue;
    if(py&&Y[i]<0) continue;
    if(!py&&Y[i]>0) continue;
    x+=X[i],y+=Y[i];
    viz[i]=true;
    ++cnt;
  }
  dfs(x,y,cnt);
}
void solve_wrong() {
  REP(i,4) f(i);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i];
  solve();
  
  return 0;
}
