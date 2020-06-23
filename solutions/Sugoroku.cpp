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
template <class T> struct RMQ {
public:
  T Inf;
  vector<T> A;
  int SIZE; // normalized size of original array
  T merge(T a, T b) { return min(a,b); }
  RMQ(int N, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(N);
    this->A=vector<T>(2*SIZE,Inf);
  }
  // O(N) initialization
  RMQ(vector<T> &X, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(X.size());
    this->A=vector<T>(2*SIZE,Inf);
    for(int i=0; i<X.size(); ++i) A[i+SIZE-1]=X[i];
    for(int i=SIZE-2; i>=0; --i) {
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  void update(int i, T v) {
    i+=SIZE-1;
    A[i]=v;
    while(i>0) {
      i=(i-1)/2;
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  // half-open range [ql,qr)
  T query(int ql, int qr) {
    return qu(ql,qr,0,0,SIZE);
  }
private:
  // i: node index (<SIZE if not leaf)
  T qu(int ql, int qr, int i, int l, int r) {
    if(qr<=l||r<=ql) return Inf;
    if(ql<=l&&r<=qr) return A[i];
    int m=(l+r)/2;

    return merge(qu(ql,qr,2*i+1,l,m),qu(ql,qr,2*i+2,m,r));
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};
// $ cp-batch Sugoroku | diff Sugoroku.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Sugoroku.cpp && ./a.out

/*

 11/24/2019

 4:54-5:17 AC

 https://twitter.com/hanseilimak/status/1198735200571686912
 https://img.atcoder.jp/abc146/editorial.pdf
 https://youtu.be/7IlBVSglZqc?t=8293
 https://twitter.com/_TTJR_/status/1198597383124221952?s=20
 https://twitter.com/satanic0258/status/1198597232888406016?s=20
 https://twitter.com/maspy_stars/status/1198598488344317952?s=20
 https://twitter.com/ei1333/status/1198598090204172288?s=20
 https://twitter.com/kyopro_friends/status/1198599795184586752
 https://twitter.com/armeria_betrue/status/1198604099396128769?s=20
 https://twitter.com/maspy_stars/status/1198626710599528454

 6/22/2020

 22:09-22:48 solve again by greedy simulation

 */

//const int MAX_N=1e6+1;
int N,M;
string S;

void nope() {
  cout<<-1<<endl;
  exit(0);
}
void solve() {
  VI rl;
  REP(i,N+1) if(S[i]=='1') {
    if(i==0||S[i-1]=='0') rl.push_back(0);
    rl.back()+=1;
  }
  FORR(l,rl) if(l>=M) nope();

  VI ps={N};
  while(ps.back()!=0) {
    int cur=ps.back();
    int j=-1;
    REP(i,M) if(cur-i-1>=0&&S[cur-i-1]=='0') j=cur-i-1;
    ps.push_back(j);
  }
  //dumpc(ps);
  reverse(ALL(ps));
  REP(i,SZ(ps)-1) cout<<ps[i+1]-ps[i]<<" ";
  cout<<endl;
}

const int Inf=1e8;
void solve_org() {
  VI A(N+1,Inf);
  REPE(i,N) A[i]=S[i]=='1'?Inf:i;
  RMQ<int> rmq(A,Inf);
  VI res;
  int i=N;
  while(i>0) {
    int ii=rmq.query(max(0,i-M), i);
    if(ii==Inf) {
      cout<<-1<<endl;
      return;
    }
//    dump(ii,A[ii],i-ii);
    res.push_back(i-ii);
    i=ii;
  }
  assert(i==0);
  reverse(ALL(res));
  REP(i,SZ(res)) printf("%d%c",res[i]," \n"[i==SZ(res)-1]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>S;
  solve();

  return 0;
}
