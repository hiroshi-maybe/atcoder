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

// $ cp-batch YakinikuOptimizationProblem | diff YakinikuOptimizationProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address YakinikuOptimizationProblem.cpp && ./a.out

/*
 
 3/1/2020
 
 9:23-9:42 give up
 
 10:00-12:10 read editorial and got AC
 
 https://youtu.be/TdR816rqc3s?t=10210
 https://twitter.com/kyopro_friends/status/1234116163413495808?s=20
 https://img.atcoder.jp/abc157/editorial.pdf
 https://twitter.com/hanseilimak/status/1234186202481168385
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.xn61xzur0w28
 
 */

const double PI = acos(-1);

typedef double num;
typedef double numLL;

const double EPS=1e-9;
bool eq(double x, double y) { return abs(x-y)<EPS; }

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
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  Point operator*(double a) const { return Point(x*a, y*a);}
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<num,num>(x,y)<pair<num,num>(that.x,that.y); }
  bool operator>(Point that) const { return pair<num,num>(x,y)>pair<num,num>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  numLL distance() { return (numLL)x*x + (numLL)y*y; }
  Point rotate90() { return Point{-y, x}; }
  int orthant() const {
    if(x==0&&y==0) return 1;
    if(y>0) return x>0?1:2;
    else return x>0?4:3;
  }
};

struct Circle {
  Point org; numLL rad;
  Circle(Point org=Point(), numLL rad=0) : org(org), rad(rad) {}
  vector<Point> cross(const Circle& c) {
    Point p=c.org-org;
    double l=sqrt(p.distance());
    if(eq(l,0)) return {};
    double maxSide=max({l,(double)rad,(double)c.rad});
    if(eq(l+rad+c.rad, maxSide*2)) { return {org + p*(rad/l)}; }
    if(l+rad+c.rad<maxSide*2) return {};
    double x=-(c.rad*c.rad-l*l-rad*rad)/(2*l);
    double y=sqrt(rad*rad-x*x);
    Point mid=org+p*(x/l);
    p=p.rotate90();
    return {mid+p*(y/l), mid-p*(y/l)};
  }
  bool contains(const Point& p) {
    return sqrt((p-org).distance())<rad+EPS;
  }
};

const int MAX_N=60+1;
Circle A[MAX_N];
int N,K;

void solve() {
  double good=1e8,bad=0;
  REP(_,100) {
    double t=(good+bad)/2;
    vector<Circle> B;
    REP(i,N) {
      Circle c=Circle(A[i].org, t/A[i].rad);
      B.push_back(c);
    }
    vector<Point> ps;
    REP(i,N) ps.push_back(B[i].org);
    REP(i,N)REP(j,N) {
      Circle a=B[i],b=B[j];
      auto xs=a.cross(b);
      FORR(x,xs) ps.push_back(x);
    }
    bool ok=false;
    FORR(p,ps) {
      int cnt=0;
      REP(i,N) cnt+=B[i].contains(p);
      if(cnt>=K) ok=true;
    }
    (ok?good:bad)=t;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) {
    double x,y,c; cin>>x>>y>>c;
    A[i]=Circle({x,y},c);
  }
  solve();
  
  return 0;
}
