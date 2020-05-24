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

// $ cp-batch Joker | diff Joker.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Joker.cpp && ./a.out

/*

 5/23/2020

 5:41-6:45,7:00-7:20 give up
 16:50-18:30, 19:30-19:46 read tweets and got AC

 https://twitter.com/hanseilimak/status/1264296651235065856
 https://img.atcoder.jp/agc044/editorial.pdf

 https://twitter.com/tempura_cpp/status/1264201997563002881
 https://twitter.com/ei1333/status/1264202318657884162
 https://twitter.com/laycrs/status/1264202212823072768
 https://twitter.com/torus711/status/1264202294087675904
 https://twitter.com/kzyKT_M/status/1264202091767017472
 https://twitter.com/maspy_stars/status/1264202956905213952
 https://twitter.com/satanic0258/status/1264203708222455810
 https://twitter.com/chokudai/status/1264204048720265218
 https://twitter.com/small_onions/status/1264204132610539520
 https://twitter.com/ngtkana/status/1264204467945091076
 https://twitter.com/yamerarenaku/status/1264237524420984833

 */

const int MAX_N=500*500+1;
int  P[MAX_N];
int N;
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int D[501][501],W[501][501];
void solve() {
  int res=0;
  REP(i,N)REP(j,N) {
    VI xs={i,j,N-1-i,N-1-j};
    D[i][j]=*min_element(ALL(xs));
    W[i][j]=1;
  }
  REP(ii,N*N) {
    int p=P[ii];
    int i=p/N,j=p%N;
    res+=D[i][j];
    W[i][j]--;
    queue<int> Q; Q.emplace(p);
    while(SZ(Q)) {
      int p=Q.front(); Q.pop();
      int i=p/N,j=p%N;
      int d=D[i][j]+W[i][j];
      for(auto m : moves) {
       int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=N||jj<0||jj>=N) continue;
        if(D[ii][jj]>d) Q.emplace(ii*N+jj),D[ii][jj]--;
      }
    }
    // dump(ii,i,j,res);
    // REP(i,N) dumpC(D[i],D[i]+N);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N*N) cin>>P[i],--P[i];
  solve();

  return 0;
}
