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

// $ cp-batch 123Triangle | diff 123Triangle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address 123Triangle.cpp && ./a.out

/*
 
 3/21/2020
 
 5:53-7:30 give up
 
 12:30-13:54 read editorials and got AC
 
 https://img.atcoder.jp/agc043/editorial.pdf
 https://youtu.be/zbjSIZ16x_I?t=742
 
 https://twitter.com/kenkoooo/status/1241372209945272321
 https://twitter.com/armeria_betrue/status/1241372111391698946
 https://twitter.com/_primenumber/status/1241372359132467204
 https://twitter.com/drken1215/status/1241374689391300609
 https://twitter.com/tempura_cpp/status/1241375077481869313
 https://twitter.com/prd_xxx/status/1241375079700676608
 
 https://mathtrain.jp/lucastheorem
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.i9kv94z1r4g3
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.8zg86t78uyfb
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.sa5l6s69zifh
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.l3mg1nsz0kqr
 
 */

//const int MAX_N=1e6+1;
string S;
int N;

int solve() {
  VI A(N);
  REP(i,N) A[i]=S[i]-'1';
  VI cnt2(N);
  REP(i,N) {
    int n=i;
    while(n>0&&n%2==0) cnt2[i]++,n/=2;
  }
  VI cum2(N+1);
  REP(i,N) cum2[i+1]=cum2[i]+cnt2[i];
  VI B(N);
  REP(i,N) B[i]=A[i]%2;
//  dumpc(B);
  
  auto f=[&](VI &B) -> int {
    int p=0;
    REP(i,N) if(B[i]>0) {
      int x=cum2[N]-cum2[i+1]-cum2[N-i];
      assert(x>=0);
      p^=(x==0);
    }
    return p;
  };
  
  int p=f(B);
  if(p==1) return 1;
  if(count(ALL(A),1)>0) return 0;
  VI C(N);
  REP(i,N) C[i]=A[i]/2;
  return f(C)*2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  cout<<solve()<<endl;
  
  return 0;
}
