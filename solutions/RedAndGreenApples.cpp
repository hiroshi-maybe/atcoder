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

// $ cp-batch RedAndGreenApples | diff RedAndGreenApples.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RedAndGreenApples.cpp && ./a.out

/*
 
 3/28/2020
 
 5:57-6:50 TLE
 7:00 WA. Give up
 
 8:31-8:42 Bug fix and AC
 
 https://img.atcoder.jp/abc160/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2020/03/28/1000
 https://youtu.be/zG1L4vYuGrg?t=4944
 
 */

//const int MAX_N=1e6+1;
int X,Y;
int N[3];
vector<vector<LL>> A(3);

void solve() {
  REP(i,3) sort(ALL(A[i])),reverse(ALL(A[i]));
  LL cursum=0,csum=0,res=0;
  dumpC(N,N+3);
  REP(i,3) dumpc(A[i]);
  REP(i,X) cursum+=A[0][i];
  REP(i,Y) cursum+=A[1][i];
  int ii[2]={X-1,Y-1};
  res=cursum;
  dump(res,cursum,csum);
  REP(i,min(N[2],X+Y)) {
    csum+=A[2][i];
    int taken=0;
    if(ii[0]<0) taken=1;
    else if(ii[1]>=0&&A[0][ii[0]]>A[1][ii[1]]) taken=1;
    assert(ii[taken]>=0);
    LL x=A[taken][ii[taken]];
    cursum-=x;
    ii[taken]--;
    SMAX(res,cursum+csum);
    dump(i,res,csum,cursum,c,x);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>X>>Y;
  REP(i,3) {
    cin>>N[i];
    A[i].resize(N[i]);
  }
  REP(i,3)REP(j,N[i]) cin>>A[i][j];
  solve();
  
  return 0;
}
