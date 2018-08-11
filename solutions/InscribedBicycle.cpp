#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/10/2018
 
 15:20-16:25 sample #2 doesn't pass
 24:10-25:13 read editorials and add math O(1) solution
 
 My approach was to check if two circles of radius `x` can be filled in the triangle.
 I wanted to compute coordinate of center of such circle.
 I spent A LOT OF TIME to find coordinate of center of a circle. However it was way too complex. I gave up.
 By polar coordinate, I thought below condition is the one. However it passed sample #1 though, did not pass #2.
 
 I couldn't find that set of possible positions of center of the circle forms similar triangle in geometry.
 
 Editorials:
  - https://cf16-final.contest.atcoder.jp//data/other/cf16-exhibition-final/editorial.pdf
  - http://kurkur.hatenablog.com/entry/2018/01/24/193840
   - O(1) math with incenter
   - https://en.wikipedia.org/wiki/Incenter
   - https://juken-mikata.net/how-to/mathematics/inscribed-circle-radius.html
    - r = 2*S/(a+b+c)
    - http://examist.jp/mathematics/math-b/planar-vector/triangle-vector/
     - S = 1/2(a1*b2-a2*b1)
  - http://wk1080id.hatenablog.com/entry/2018/02/21/000505
   - binary search is performed though, it's not necessary
   - this solution is also using incircle. Thus O(1) solution is possible with same approach.
  - https://kimiyuki.net/writeup/algo/atcoder/codefestival-2016-grand-final-b/
   - O(1) math solution
   - close to my original wrong solution
 
 Summary:
  - If formula was toooooo complex, look for another approach 😡
  - poor math 🎉. I completely forgot incenter of triangle.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int X[3],Y[3];

double slope(double x1,double y1,double x2,double y2) {
  return atan((y2-y1)/(x2-x1));
}

bool ok(double r) {
  bool good=false;
  REP(i,3)REP(j,3)if(i<j) {
    int k=3-i-j;
    double x1=X[i],y1=Y[i],x2=X[j],y2=Y[j];
    double D=hypot(x1-x2,y1-y2);
    double x3=X[k],y3=Y[k];
    double rad1=slope(x1,y1,x3,y3)-slope(x1,y1,x2,y2),rad2=slope(x2,y2,x1,y1)-slope(x2,y2,x3,y3);
    rad1*=0.5,rad2*=0.5;
    double d1=r/abs(tan(rad1))+r,d2=r/abs(tan(rad2))+r;
    if(d1+d2<=D) dump4(i,j,d1,d2);
    good|=d1+d2<=D;
  }
  return good;
}

void solve_wrong() {
  /*
  if(X[1]>X[2]) swap(X[1],X[2]),swap(Y[1],Y[2]);
  if(X[0]>X[1]) swap(X[0],X[1]),swap(Y[0],Y[1]);
  if(X[1]>X[2]) swap(X[1],X[2]),swap(Y[1],Y[2]);*/

  double good=0,bad=1001;
  REP(_,50) {
    double mid=(good+bad)*0.5;
    bool okok=ok(mid);
    dump2(mid,okok);
    (okok?good:bad)=mid;
  }
  cout<<setprecision(12)<<good<<endl;
}

void solve() {
  double x1=X[0],y1=Y[0],x2=X[1],y2=Y[1],x3=X[2],y3=Y[2];
  double a=hypot(x2-x3,y2-y3),b=hypot(x1-x3,y1-y3),c=hypot(x1-x2,y1-y2);
  double px=x2-x1,py=y2-y1,qx=x3-x1,qy=y3-y1;
  double S=0.5*abs(px*qy-py*qx);
  double r=2*S/(a+b+c);
  double d=max({a,b,c});
  double res= d*r/(d+2*r);
  cout<<setprecision(15)<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  REP(i,3) cin>>X[i]>>Y[i];
  solve();
  return 0;
}
