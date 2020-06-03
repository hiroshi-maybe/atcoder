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

// $ cp-batch Cake123 | diff Cake123.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Cake123.cpp && ./a.out

/*

 4/7/2019

 20:19-21:05 give up

 4/8/2019

 14:45-16:40 read editorials and got AC

 There are three major solutions
  1. Make `K` largest from A and B as A'. make K largest from A' and C
  2. If f(A[i],B[j],C[k]) is taken, keep adding next candidate to priority queue
   - f(A[i+1],B[j],C[k]), f(A[i],B[j+1],C[k]) and f(A[i],B[j].C[k+1]) are next candidate
  3. Brute-force + edge pruning

 # 1. Semi brute-force.

 We can get A'={a+b:a∈A,b∈B} and sort in descendent order where |A'| = |A|*|B|.
 A'[0..K-1] can be a candidate of K largest. However A[K] cannot.
 The best partner for A[K] is C[0]. However A[K]+C[0]<A[i]+C[0], i=0..K-1.
 Thus Choosing K largest from A' is optimal.

 #2. Priority queue

 Obviously maximal value is A[0]+B[0]+C[0]. Candidate of next largest value is oen of {A[1]+B[0]+C[0],A[0]+B[1]+C[0],A[0]+B[0]+C[1]}.
 We want to always query largest from candidates online. Priority queue works for it.

 http://drken1215.hatenablog.com/entry/2019/04/07/001000
 https://img.atcoder.jp/abc123/editorial.pdf
 https://twitter.com/torus711/status/1114523526952710144
 https://twitter.com/kakira9618/status/1114523600470532097
 https://twitter.com/mistter_gp/status/1114523617033838593
 https://twitter.com/CuriousFairy315/status/1114524060451389440
 https://twitter.com/tempura_cpp/status/1114524179447959555
 https://twitter.com/kyopro_friends/status/1114524642796953600
 https://twitter.com/satanic0258/status/1114533340260917248
 https://twitter.com/nabesan_go/status/1114535121107832833

 6/3/2020

 9:00-9:33 solve again

 */

const int MAX_N=1e3+1;
LL A[3][MAX_N];
int K,N[3];

void solve_again() {
  REP(i,3)REP(j,N[i]) sort(A[i],A[i]+N[i]),reverse(A[i],A[i]+N[i]);
  vector<LL> xs;
  REP(i,N[0])REP(j,N[1]) xs.push_back(A[0][i]+A[1][j]);
  sort(xs.rbegin(),xs.rend());
  vector<LL> res;
  REP(i,min(SZ(xs),K))REP(j,N[2]) res.push_back(xs[i]+A[2][j]);
  sort(res.rbegin(),res.rend());
  REP(i,K) cout<<res[i]<<endl;
}

void solve_semibruteforce() {
  REP(c,3) sort(A[c],A[c]+N[c]),reverse(A[c],A[c]+N[c]);
  vector<LL> X;
  REP(i,N[0])REP(j,N[1]) {
    X.emplace_back(A[0][i]+A[1][j]);
  }
  sort(ALL(X)),reverse(ALL(X));
  vector<LL> Y;
  REP(i,min(N[0]*N[1],K))REP(j,N[2]) {
    Y.push_back(X[i]+A[2][j]);
  }
  sort(ALL(Y)),reverse(ALL(Y));
  REP(i,K) cout<<Y[i]<<endl;
}

void solve() {
  REP(c,3) sort(A[c],A[c]+N[c]),reverse(A[c],A[c]+N[c]);
  priority_queue<tuple<LL,int,int,int>> Q; Q.emplace(A[0][0]+A[1][0]+A[2][0],0,0,0);
  set<III> viz;
  vector<LL> res;
  while(SZ(res)<K) {
    assert(SZ(Q));
    LL v; int i,j,k; tie(v,i,j,k)=Q.top(),Q.pop();
    res.push_back(v);
    if(i+1<N[0]&&viz.count(make_tuple(i+1,j,k))==0) Q.emplace(A[0][i+1]+A[1][  j]+A[2][  k],i+1,j,k),viz.emplace(i+1,j,k);
    if(j+1<N[1]&&viz.count(make_tuple(i,j+1,k))==0) Q.emplace(A[0][  i]+A[1][j+1]+A[2][  k],i,j+1,k),viz.emplace(i,j+1,k);
    if(k+1<N[0]&&viz.count(make_tuple(i,j,k+1))==0) Q.emplace(A[0][  i]+A[1][  j]+A[2][k+1],i,j,k+1),viz.emplace(i,j,k+1);
  }
  REP(i,K) cout<<res[i]<<endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  REP(i,3) cin>>N[i];
  cin>>K;
  REP(i,3)REP(j,N[i]) cin>>A[i][j];
  solve();

  return 0;
}
