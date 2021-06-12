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
const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};
// $ cp-batch ManyFormulae | diff ManyFormulae.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ManyFormulae.cpp && ./a.out

/*

 6/12/2021

 5:00-6:19 AC

 https://atcoder.jp/contests/arc122/editorial/2054
 https://twitter.com/laycrs/status/1403714162887331845
 https://twitter.com/togatoga_/status/1403714975181336581
 https://mobile.twitter.com/ngtkana/status/1403722411699097601

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

ModInt cnt[MAX_N][2];
ModInt W[MAX_N][2];
ModInt U[MAX_N][2];

void solve() {
  cnt[0][0]=1;
  REP(i,N) cnt[i+1][0]+=cnt[i][0]+cnt[i][1],cnt[i+1][1]=cnt[i][0];

  W[0][0]=cnt[N-1][0]+cnt[N-1][1];
  REP(j,2) W[N-1][j]=cnt[N-1][j];
  FOR(i,1,N-1) {
    W[i][0]=(cnt[i-1][0]+cnt[i-1][1])*(cnt[N-i-1][0]+cnt[N-i-1][1]);
    W[i][1]=cnt[i-1][0]*(cnt[N-i-2][0]+cnt[N-i-2][1]);
  }

  /*
  W[N-1][0]=cnt[N-1][0],W[N-1][1]=cnt[N-1][1];
  for(int i=N-1; i>=0; --i) {
    if(i<N-1) {
      W[i][0]=(U[i+1][0]+U[i+1][1])*cnt[i][0];
      W[i][1]=U[i+1][0]*cnt[i][1];
      assert(W[i][0]+W[i][1]==cnt[N-1][0]+cnt[N-1][1]);
    }
    if(i>0) REP(j,2)U[i][j]=W[i][j]/cnt[i][j];
    //dump(i,U[i][0],U[i][1],W[i][0],W[i][1],cnt[i][0],cnt[i][1]);
  }*/
  ModInt res=0;
  REP(i,N) res+=(W[i][0]-W[i][1])*A[i];
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
