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

// $ cp-batch 106 | diff 106.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address 106.cpp && ./a.out

/*

 10/24/2020

 5:00-5:06 WA
 5:20 pause
 6:36 AC

 https://atcoder.jp/contests/arc106/editorial/256

 */

LL N;

__uint128_t p(LL a, int b) {
  __uint128_t res=1;
  while(b--) res*=a;
  return res;
}

__uint128_t e18=1000000000000000000;

void solve() {
  int A=0,B=0;
  while(p(3,A)<e18) ++A;
  while(p(5,B)<e18) ++B;

  FOR(a,1,A)FOR(b,1,B) {
    if((__uint128_t)p(3,a)+(__uint128_t)p(5,b)==(__uint128_t)N) {
      cout<<a<<" "<<b<<endl;
      return;
    }
  }
  cout<<-1<<endl;
}

void solve_wrong() {
  int b=0;
  LL x=1;
  while(true) {
    LL y=N-x; int a=0;
    if(y==0) break;
    while(y!=0&&(y%3)==0) y/=3,++a;
    //dump(x,y,a);
    if(y==1) {
      LL x=p(5,b),y=p(3,a);
      assert(x+y==N);
      cout<<a<<" "<<b<<endl;
      return;
    }
    if((__uint128_t)x*5>(__uint128_t)N) break;
    b+=1,x*=5;
  }
  cout<<-1<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}

void test() {
  N=genRandNum(1LL,(LL)1e8);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N;
  solve();

  return 0;
}
