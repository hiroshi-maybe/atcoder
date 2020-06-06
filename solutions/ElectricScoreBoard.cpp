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

// $ cp-batch ElectricScoreBoard | diff ElectricScoreBoard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ElectricScoreBoard.cpp && ./a.out

/*

 6/5/2020

 21:19-21:50 AC

 */

vector<string> S;
int N;

vector<string> dsds={
  ".###..#..###.###.#.#.###.###.###.###.###.",
  ".#.#.##....#...#.#.#.#...#.....#.#.#.#.#.",
  ".#.#..#..###.###.###.###.###...#.###.###.",
  ".#.#..#..#.....#...#...#.#.#...#.#.#...#.",
  ".###.###.###.###...#.###.###...#.###.###."
};

void show(vector<string> ss) {
  FORR(s,ss) dump(s);
}

vector<string> take(int i, vector<string> &s) {
  vector<string> x(5,string(4,'?'));
  REP(r,5)FOR(j,4*i,4*(i+1)) x[r][j-4*i]=s[r][j];
  //dumpc(x);
  return x;
}

void solve() {
  vector<vector<string>> ds(10);
  REP(i,10) {
    ds[i]=take(i,dsds);
    //dump(i);
    //show(ds[i]);
  }
  //dumpc(ds[0]);
  VI res(N,-1);
  REP(i,N) {
    vector<string> a=take(i,S);
    REP(d,10) if(a==ds[d]) {
      res[i]=d;
      break;
    }
    assert(res[i]!=-1);
  }
  string ans(N,'?');
  REP(i,N) ans[i]='0'+res[i];
  cout<<ans<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  S=vector<string>(5);
  REP(i,5) cin>>S[i];
  solve();

  return 0;
}
