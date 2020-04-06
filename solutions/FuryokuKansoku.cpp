#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <tuple>
#include <unordered_set>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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

// $ cp-batch FuryokuKansoku | diff FuryokuKansoku.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FuryokuKansoku.cpp && ./a.out

/*
 
 4/5/2020
 
 17:47-18:25 AC
 
 https://www.slideshare.net/chokudai/abc001
 
 */

int A,B;
int BB;

vector<tuple<string,int,int>> X=
{{"N",0,40000},{"S",16875,19125},{"NNE",1125,3375},{"SSW",19125,21375},{"NE",3375,5625},{"SW",21375,23625},{"ENE",5625,7875},{"WSW",23625,25875},{"E",7875,10125},{"W",25875,28125},{"ESE",10125,12375},{"WNW",28125,30375},{"SE",12375,14625},{"NW",30375,32625},{"SSE",14625,16875},{"NNW",32625,34875}};
vector<pair<int,int>> Y={{0,2},{3,15},{16,33},{34,54},{55,79},{80,107},{108,138},{139,171},{172,207},{208,244},{245,284},{285,326},{327,10000}};

void solve() {
  reverse(ALL(X));
  dumpc(Y);
  string dir="?"; int s=-1;
  REP(i,SZ(X)) {
    string a; int l,r; tie(a,l,r)=X[i];
    if(l<=A&&A<r) {
      dir=a;
      break;
    }
  }
  assert(dir!="?");
  dump(BB);
  REP(i,SZ(Y)) if(Y[i].first<=BB&&BB<=Y[i].second) {
    s=i;
    break;
  }
  dump(dir,s);
  assert(s>=0);
  if(s==0) dir="C";
  cout<<dir<<" "<<s<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
//  cout<<setprecision(12)<<fixed;
  
  cin>>A>>B;
  A*=10;
  BB=(int)(1.0*B/6+0.5);
  solve();
  
  return 0;
}
