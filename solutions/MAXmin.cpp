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

// $ cp-batch MAXmin | diff MAXmin.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MAXmin.cpp && ./a.out

/*

 10/11/2020

 6:52-6:58, 8:12-8:27 WA
 8:35 WA
 9:05 AC

 https://twitter.com/hanseilimak/status/1315365366877437952
 https://atcoder.jp/contests/arc105/editorial/169
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.a6usn1s0j58h

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

int solve_wrong() {
  VI as(A,A+N);
  sort(ALL(as));
  as.erase(unique(ALL(as)),as.end());
  //dumpc(as);
  int res=as[0];
  REP(i,SZ(as)) if(as[i]%as[0]!=0) {
    dump(i,as[i],as[i]%as[0]);
    SMIN(res,as[i]%as[0]);
  }

  return res;
}

int solve() {
  LL g=A[0];
  REP(i,N) g=gcd(g,A[i]);
  return g;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(1,5);
  VI as=genRandSeq(N,1,20);
  REP(i,N) A[i]=as[i];
  int act=solve();

  dumpc(as);

  int exp=-1;
  while(true) {
    set<int> S(ALL(as));
    if(SZ(S)==1) {
      exp=*S.begin();
      break;
    }
    int mina=*min_element(ALL(as)),maxa=*max_element(ALL(as));
    assert(mina!=maxa);
    REP(i,N) if(as[i]==maxa) as[i]-=mina;
  }

  dump(exp,act);
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;

  return 0;
}
