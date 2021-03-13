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

// $ cp-batch Lucky7Battle | diff Lucky7Battle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Lucky7Battle.cpp && ./a.out

/*

 3/13/2021

 4:58-5:31 AC

 https://atcoder.jp/contests/abc195/editorial/886

 */

const int MAX_N=2e5+10;
int N;
string S,X;

int p10[MAX_N];
int memo[MAX_N][7];
int f(int i, int r) {
  if(i==N) {
    int res=-1;
    if(X[N-1]=='A') res=(r%7==0);
    else res=(r%7!=0);
    //dump(i,r,res);
    return res;
  }
  int &res=memo[i][r];
  if(res>=0) return res;
  int p=p10[N-i-1];
  int r1=f(i+1,r);
  int r2=f(i+1,(r+p*(S[i]-'0'))%7);

  if((i+1==N)||(X[i+1]!=X[i])) {
    if(r1==0||r2==0) res=1;
    else res=0;
  } else {
    res=r1||r2;
  }
  //dump(i,r,res);
  return res;
}

void solve() {
  p10[0]=1;
  REP(i,MAX_N-1) p10[i+1]=p10[i]*10%7;
  MINUS(memo);
  bool res=f(0,0);
  if(X[0]=='A') res^=1;
  cout<<(res?"Takahashi":"Aoki")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>S>>X;
  solve();

  return 0;
}
