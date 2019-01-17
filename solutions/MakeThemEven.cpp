#include <iostream>
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
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch MakeThemEven | diff MakeThemEven.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MakeThemEven.cpp && ./a.out

/*
 
 1/16/2019
 
 20:33-21:08 AC
 
 https://img.atcoder.jp/abc109/editorial.pdf
 https://youtu.be/zu0-rIh4ZXM?t=2855
 
 Key:
  - Only (odd,odd) reduces # of odd parity
  - We cannot intersect path. Zig-zag is typical way to traverse.
 
 */

const int MAX_N=5e2+1;
int A[MAX_N][MAX_N];
int H,W;

vector<II> path(II st, II dest) {
  vector<II> res={st};
  II cur=st;
  while(cur!=dest) {
    int i=cur.first,j=cur.second;
    if(i%2==0) j+=1;
    else j-=1;
    if(j==W) i+=1,j=W-1;
    else if(j==-1) i+=1,j=0;
    res.emplace_back(i,j);
    cur={i,j};
  }
  return res;
}
void solve() {
  int st=0;
  II from;
  vector<vector<II>> res;
  REP(i,H) {
    int dj=i%2==0?+1:-1;
    for(int j=dj>0?0:W-1; j!=(dj>0?W:-1); j+=dj) {
      if(st==0) {
        if(A[i][j]%2==1) {
          from={i,j};
          st=1;
        }
      } else {
        if(A[i][j]%2==1) {
//          dump4(from.first,from.second,i,j);
          res.push_back(path(from,{i,j}));
          st=0;
        }
      }
    }
  }
  
  int cnt=0;
  REP(i,SZ(res)) cnt+=SZ(res[i])-1;
  println("%d",cnt);
  FORR(p,res) {
    REP(i,SZ(p)-1) {
      II p1=p[i],p2=p[i+1];
      println("%d %d %d %d",p1.first+1,p1.second+1,p2.first+1,p2.second+1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>H>>W;
  REP(i,H)REP(j,W) cin>>A[i][j];
  solve();
  
  return 0;
}
