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

// $ cp-batch MandarinOrange | diff MandarinOrange.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MandarinOrange.cpp && ./a.out

/*

 1/23/2021

 4:05-4:11 AC

 8:40-9:00 Add O(N) solution for "largest rectangle in histogram"

 https://atcoder.jp/contests/abc189/editorial/533
 https://youtu.be/u2woAs3M1c0?t=1733

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void solve() {
  vector<II> st;
  vector<II> left(N);
  st.emplace_back(0,-1);
  REP(i,N) {
    int a=A[i];
    while(st.back().first>=a) st.pop_back();
    left[i]=st.back();
    st.emplace_back(a,i);
  }
  //dumpc(left);

  int res=0;
  while(SZ(st)) st.pop_back();
  st.emplace_back(0,N);
  for(int i=N-1; i>=0; --i) {
    int a=A[i];
    while(st.back().first>=a) st.pop_back();
    int b=st.back().second-left[i].second-1;
    //dump(i,a,st.back().second,left[i].second,b);
    SMAX(res,a*b);
    st.emplace_back(a,i);
  }
  cout<<res<<endl;
}

void solve_square_n() {
  int res=0;
  REP(l,N) {
    int mina=A[l];
    FOR(r,l,N) {
      SMIN(mina,A[r]);
      SMAX(res,mina*(r-l+1));
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
