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

// $ cp-batch TwinsGame | diff TwinsGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwinsGame.cpp && ./a.out

/*

 8/5/2020

 21:48-21:55 pause

 8/11/2020

 9:01-10:25 AC

 https://www.slideshare.net/chokudai/abc025

 */

const int MAX_N=3;
int B[MAX_N][MAX_N],C[MAX_N][MAX_N];

bool ith(int mask, int i) { return (mask>>i)&1; }
II g(int mask) {
  VI A(9,0);
  REP(i,9) if(ith(mask,i)) A[i]=1;

  II res={0,0};
  REP(i,2)REP(j,3) {
    (A[i*3+j]!=A[(i+1)*3+j]?res.first:res.second)+=B[i][j];
  }
  REP(i,3)REP(j,2) {
    (A[i*3+j]!=A[i*3+j+1]?res.first:res.second)+=C[i][j];
  }
  res.second=-res.second;
  assert(res.first>=0&&res.second<=0);
  //dump(mask,res.first,res.second);
  return res;
}

const int Inf=1e9;
map<VI,II> memo;
II f(VI &s) {
  if(memo.count(s)) return memo[s];
  if(SZ(s)==9) {
    int mask=0;
    REP(i,9) if(i%2==0) mask|=(1<<s[i]);
    return memo[s]=g(mask);
  }

  VI viz(9,0); FORR(p,s) viz[p]=1;

  II res={0,-Inf};
  REP(i,9) if(!viz[i]) {
    s.push_back(i);
    II x=f(s);
    //dumpc(s);
    //dump(x.first,x.second);
    II y={-x.second,-x.first};
    assert(y.second<=0);
    assert(y.first>=0);

    SMAX(res,y);
    s.pop_back();
  }

  return res;
}

void solve() {
  VI s={};
  II res=f(s);
  int sum=0;
  REP(i,3)REP(j,2) sum+=C[i][j];
  REP(i,2)REP(j,3) sum+=B[i][j];
  assert(res.first-res.second==sum);
  cout<<res.first<<endl;
  cout<<-res.second<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  REP(i,2)REP(j,3) cin>>B[i][j];
  REP(i,3)REP(j,2) cin>>C[i][j];
  solve();

  return 0;
}
