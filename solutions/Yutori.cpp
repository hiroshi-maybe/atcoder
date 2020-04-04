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

// $ cp-batch Yutori | diff Yutori.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Yutori.cpp && ./a.out

/*
 
 4/4/2020
 
 6:05-6:30 give up
 
 11:35-12:35 read editorials and got AC
 
 https://twitter.com/hanseilimak/status/1246507944008486913
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.7fnug5h0hkpd
 http://kmjp.hatenablog.jp/entry/2020/04/05/0900
 https://youtu.be/q-mrqE2Q7JQ?t=4025
 https://twitter.com/drken1215/status/1246433125510418435
 https://twitter.com/kyopro_friends/status/1246434408237690880
 https://twitter.com/laycrs/status/1246432536244277253
 https://twitter.com/prd_xxx/status/1246432457823379457
 https://twitter.com/satanic0258/status/1246432446502957056
 https://twitter.com/tsutaj/status/1246432739252776960
 
 */

//const int MAX_N=1e6+1;
string S;
int N,K,C;

void solve() {
  VI A(N); REP(i,N) A[i]=S[i]=='o';
  
  auto f=[&](VI &A)->VI {
    VI res(N);
    int pre=-1e7,cnt=0;
    REP(i,N) if(A[i]) {
      if(i-pre>=C+1) ++cnt,res[i]=1,pre=i;
    }
    return res;
  };
  
  VI L=f(A);
  reverse(ALL(A));
  VI R=f(A);
  reverse(ALL(R));
  int cntl=count(ALL(L),1),cntr=count(ALL(R),1);
//  dump(cntl,cntr);
  if(cntl>K||cntr>K) return;
  VI res;
  REP(i,N)if(L[i]&&R[i]) res.push_back(i);
  FORR(a,res) cout<<a+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>C>>S;
  solve();
  
  return 0;
}
