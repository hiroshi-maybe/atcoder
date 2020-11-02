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
bool isColinear(Point<num> origin, Point<num> p1, Point<num> p2) { return det(origin, p1, p2)==0; }
// $ cp-batch Collinearity | diff Collinearity.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Collinearity.cpp && ./a.out

/*

 11/1/2020

 4:03-4:10 AC

 https://atcoder.jp/contests/abc181/editorial/258

 */

const int MAX_N=1e6+1;
II A[MAX_N];
int N;

bool solve() {
  vector<Point<int>> ps(A,A+N);
  REP(i,N)REP(j,N)if(i!=j)REP(k,N)if(k!=i&&k!=j) {
    if(isColinear(ps[i],ps[j],ps[k])) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i].first>>A[i].second;
  cout<<(solve()?"Yes":"No")<<endl;

  return 0;
}
