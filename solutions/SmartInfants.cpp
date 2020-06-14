#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <cassert>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SmartInfants | diff SmartInfants.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SmartInfants.cpp && ./a.out

/*

 6/14/2020

 5:22-5:49 TLE
 7:37 AC after fixing multiset assignment bug

 https://img.atcoder.jp/abc170/editorial.pdf
 https://twitter.com/hanseilimak/status/1272267372951334913

 https://ngtkana.growi.cloud/solutions/contest/abc170
 https://twitter.com/satanic0258/status/1272162160668368902

 */

const int MAX_N=2e5+1;
int rates[MAX_N],kind[MAX_N];
multiset<int> P[MAX_N];
multiset<int> maxs;
int N,Q;

const int Inf=2e9;
int maxrate(int kid) {
  auto &s=P[kid];
  if(SZ(s)==0) return Inf;
  //auto it=s.rbegin();
  //return it->first;
  return *s.rbegin();
}
void solve(vector<II> &qs) {
  REP(i,Q) {
    int pid,newk;
    if(SZ(qs)) {
      pid=qs[i].first,newk=qs[i].second;
    } else {
      scanf("%d %d", &pid,&newk);
      --newk,--pid;
    }

    // Get starting timepoint
    auto start = chrono::high_resolution_clock::now();
    auto measure=[&]() -> int {
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
      start = stop;
      return duration.count();
    };

    dump(i,SZ(maxs));
    int oldk=kind[pid],maxr1=maxrate(oldk);
    dump(measure());
    int maxr2=maxrate(newk);
    dump(measure());

    if(maxr1!=Inf)maxs.erase(maxs.find(maxr1));
    if(maxr2!=Inf)maxs.erase(maxs.find(maxr2));

    dump(measure());

    P[oldk].erase(P[oldk].find(rates[pid]));
    P[newk].emplace(rates[pid]);
    maxr1=maxrate(oldk),maxr2=maxrate(newk);
    if(maxr1!=Inf)maxs.emplace(maxr1);
    if(maxr2!=Inf)maxs.emplace(maxr2);
    kind[pid]=newk;

    dump(measure())

    cout<<*maxs.begin()<<endl;

    dump(measure());
  }
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=2e5,Q=N;
  VI xs(2e5+1,-1);
  VI as=genRandSeq(N,1,10);
  VI bs=genRandSeq(N,0,2e5);
  REP(i,N)rates[i]=as[i],kind[i]=bs[i];
  VI cs=genRandSeq(Q,0,N),ds=genRandSeq(Q,0,N);
  vector<II> qs(N);
  REP(i,N) qs[i]={cs[i],ds[i]};
  solve(qs);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //test();

  scanf("%d %d", &N,&Q);
  VI xs(2e5+1,-1);
  VV<int> ys(2e5+1);
  REP(i,N) {
    int a,b; scanf("%d %d", &a,&b);
    --b;
    rates[i]=a;
    ys[b].emplace_back(a);
    kind[i]=b;

    SMAX(xs[b],a);
  }
  REP(i,2e5) if(SZ(ys[i])) {
    multiset<int> s(ALL(ys[i]));
    P[i]=s;
  }

  REP(i,2e5+1) if(xs[i]!=-1) {
    maxs.emplace(xs[i]);
  }
  vector<II> qs;
  solve(qs);

  return 0;
}
