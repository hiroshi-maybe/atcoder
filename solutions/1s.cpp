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

// $ cp-batch 1s | diff 1s.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address 1s.cpp && ./a.out

/*
 
 5/9/2020
 
 8:31-8:58 pause
 16:32-17:15 AC
 
 https://www.slideshare.net/chokudai/abc029
 
 */

int N;

LL p10[14];
void solve() {
  N+=1;
  p10[0]=1;
  REP(i,12)p10[i+1]=p10[i]*10;
  LL res=0;
  REP(i,10) {
    int c=N/p10[i+1];
    res+=c*p10[i];
//    dump(i,c,p10[i]);
    LL r=N%p10[i+1];
    r-=p10[i];
    if(r<=0) continue;
//    dump(i,r,min(r,p10[i]));
    res+=min(r,p10[i]);
  }
  cout<<res<<endl;
 }

LL dp[11][12][2][2];
void solve_dp() {
  ZERO(dp);
  string s=to_string(N);
  int L=SZ(s);
  dp[0][0][0][1]=1;
  REP(i,L) {
    REP(cnt,12)REP(less,2)REP(islz,2) {
      int lb=islz?1:0;
      int hb=less?9:s[i]-'0';
      FORE(d,lb,hb) {
        dp[i+1][cnt+(d==1)][less|(d<(s[i]-'0'))][0]+=dp[i][cnt][less][islz];
      }
    }
    dp[i+1][0][1][1]++;
  }
  LL res=0;
  REP(cnt,12)REP(less,2) res+=(LL)cnt*dp[L][cnt][less][0];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
