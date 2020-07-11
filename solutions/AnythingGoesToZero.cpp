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

// $ cp-batch AnythingGoesToZero | diff AnythingGoesToZero.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AnythingGoesToZero.cpp && ./a.out

/*

 7/11/2020

 5:16-5:45 RE (0-division)
 6:03 AC

 https://img.atcoder.jp/aising2020/editorial.pdf

 */

int N;
string X;

int f(int n) {
  int res=0;
  while(n>0) n%=__builtin_popcount(n),++res;
  return res;
}


void solve() {
  string S=X;
  reverse(ALL(S));
  int pc=count(ALL(S),'1');
  map<int,int> fx;
  map<int,vector<int>> pw2;
  for(int d=-1; d<=1; ++d) {
    int pcpc=pc+d;
    if(pcpc==0) continue;
    pw2[pcpc]=VI(N+1,0);
    int cur=1;
    REP(i,N) {
      if(S[i]=='1') {
        fx[pcpc]+=cur;
        fx[pcpc]%=pcpc;
      }
      pw2[pcpc][i]=cur;
      cur=cur*2%pcpc;
    }
  }

  VI res(N);
  REP(i,N) {
    int pcpc=pc;
    int n;
    if(S[i]=='1') {
      pcpc-=1;
      if(pcpc==0) {
        res[i]=0;
        continue;
      }
      n=fx[pcpc];
      n=(n-pw2[pcpc][i]+pcpc)%pcpc;
    } else {
      pcpc+=1;
      n=fx[pcpc];
      n=(n+pw2[pcpc][i])%pcpc;
    }
    //dump(i,pcpc,fx[pcpc],pw2[pcpc][i],n);
    res[i]=f(n)+1;
  }

  reverse(ALL(res));
  REP(i,N) cout<<res[i]<<endl;
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
  N=genRandNum(1,10);
  VI as=genRandSeq(N,0,2);
  string s(N,'0');
  REP(i,N) if(as[i]) s[i]='1';
  X=s;
  dump(N,X);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

//  while(true) test();

  cin>>N>>X;
  solve();

  return 0;
}
