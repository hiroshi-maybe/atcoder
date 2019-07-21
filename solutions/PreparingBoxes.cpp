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

// $ cp-batch PreparingBoxes | diff PreparingBoxes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PreparingBoxes.cpp && ./a.out

/*
 
 7/20/2019
 
 5:12-5:28 WA
 8:35 AC
 
 https://img.atcoder.jp/abc134/editorial.pdf
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

int X[MAX_N];
void solve() {
  ZERO(X);
  for(int i=N; i>=1; --i) {
    int sum=0;
    for(int j=2*i; j<=N; j+=i) sum^=X[j];
    X[i]=sum^A[i];
  }

  VI res;
  FORE(i,1,N) if(X[i]) res.push_back(i);
  println("%d",SZ(res));
  REP(i,SZ(res)) println("%d",res[i]);
}

void solve_org() {
  ZERO(X);
  int sufn=(N+1)/2;
  int i=N;
  while(sufn--) {
    X[i]=A[i];
    --i;
  }
  while(i>=1) {
    int sum=0;
    for(int j=2*i; j<=N; j+=i) sum^=X[j];
    X[i]=sum^A[i];
    --i;
  }
  
//  dumpC(X+1,X+N+1);
  FORE(i,1,N) {
    int sum=0;
    for(int j=i; j<=N; j+=i) sum^=X[j];
//    dump(i,A[i],sum);
    assert(A[i]==(sum&1));
  }
  
  VI res;
  FORE(i,1,N) if(X[i]) res.push_back(i);
  println("%d",SZ(res));
  REP(i,SZ(res)) println("%d",res[i]);
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
  N=genRandNum(1,(int)2e5);
  VI AA=genRandSeq(N,0,2);
  REP(i,N) A[i+1]=AA[i];
  dumpc(AA);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) cin>>A[i+1];
  solve();
  
  return 0;
}
