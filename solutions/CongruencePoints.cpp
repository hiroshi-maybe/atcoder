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
const double PI = acos(-1);

typedef long long num;

const double EPS=1e-6;
bool eq(double x, double y) { return abs(x-y)<EPS; }

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
template<typename num>
num det(Point<num> u, Point<num> v) { return u.x*v.y - u.y*v.x; }
template<typename num>
num det(Point<num> origin, Point<num> p1, Point<num> p2) { return det(p1-origin, p2-origin); }
template<typename num>
num dot(Point<num> u, Point<num> v) { return u.x*v.x + u.y*v.y; }

template<typename num>
void sortByPolarAngle(vector<Point<num>>& ps, Point<num> origin) {
  sort(ps.begin(), ps.end(), [&](const Point<num> &a, const Point<num> &b) {
    /*int oa=(a-origin).orthant(),ob=(b-origin).orthant();
    if(oa!=ob) return oa<ob;*/
    num d = det(origin,a,b);
    if(d!=0) return d > 0;
    return Point<num>(a,origin).distance() < Point<num>(b,origin).distance();
  });
}
// $ cp-batch CongruencePoints | diff CongruencePoints.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CongruencePoints.cpp && ./a.out

/*

 6/26/2021

 14:31-16:00 WA

 6/27/2021

 14:20-15:00 AC

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.sen3dbwlbkcn
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.o64jrgdlwy0c

 https://youtu.be/EWx0w7gfQRU?t=2435
 https://atcoder.jp/contests/abc207/editorial/2153
 https://atcoder.jp/contests/abc207/editorial/2167

 */

const int MAX_N=100+1;
II S[MAX_N],T[MAX_N];
int N;

bool solve() {
  REP(i,N)REP(j,N) {
    Point<int> o1=S[i],o2=T[j];
    vector<Point<int>> ss(S,S+N),tt(T,T+N);
    REP(k,N) ss[k]-=o1;
    REP(k,N) tt[k]-=o2;
    sortByPolarAngle(ss,ss[i]);
    sortByPolarAngle(tt,tt[j]);

    bool distok=true;
    REP(i,N-1) {
      distok&=((ss[i]-ss[i+1]).distance())==((tt[i]-tt[i+1]).distance());
    }
    if(!distok) continue;

    bool angok=true;
    FOR(i,1,N-1) {
      auto a=dot(ss[i+1]-ss[i],ss[i-1]-ss[i]);
      auto b=dot(tt[i+1]-tt[i],tt[i-1]-tt[i]);
      angok&=a==b;
    }
    if(!angok) continue;
    return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  FOR(c,1,20)FORE(b,1,c)FOR(a,1,b) {
    if(a*a+b*b==c*c) {
      dump(a,b,c);
    }
  }*/

  cin>>N;
  REP(i,N) cin>>S[i].first>>S[i].second;
  REP(i,N) cin>>T[i].first>>T[i].second;
  cout<<(solve()?"Yes":"No")<<endl;

  return 0;
}
